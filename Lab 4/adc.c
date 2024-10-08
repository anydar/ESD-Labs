#include <LPC214x.h>  

// Function to create a delay
void delay(unsigned int count) {
    unsigned int i;
    for (i = 0; i < count; i++);  
}

// Function to initialize the ADC (Analog-to-Digital Converter)
void ADC_init() {
    PINSEL1 |= (1 << 24);  // Configure P0.28 as AD0.1 (ADC channel 1)
    
    // Configure the ADC
    // (1 << 1): Select ADC channel 1 (AD0.1)
    // (4 << 8): Set ADC clock division factor to 5 (ADC clock = PCLK/5)
    // (1 << 21): Enable the ADC
    AD0CR = (1 << 1) | (4 << 8) | (1 << 21);
}

// Function to read the value from the ADC
unsigned int ADC_read() {
    AD0CR |= (1 << 24);  // Start ADC conversion
    
    // Wait for the conversion to complete
    // The 31st bit of AD0GDR (ADC Global Data Register) becomes 1 when the conversion is done
    while (!(AD0GDR & (1 << 31)));
    
    // Extract the 10-bit result (bits 6 to 15) and return the value
    return (AD0GDR >> 6) & 0x3FF;  // 0x3FF is a mask to keep only the lower 10 bits (10-bit ADC result)
}

// Function to initialize the GPIO pins for LEDs
void GPIO_init() {
    // Set P0.0, P0.1, and P0.2 as output pins for the LEDs
    IO0DIR |= (1 << 0) | (1 << 1) | (1 << 2);
}

// Function to display the ADC value on the LEDs
void display_on_leds(unsigned int adc_value) {
    // First, turn off all LEDs by clearing P0.0, P0.1, and P0.2
    IO0CLR = (1 << 0) | (1 << 1) | (1 << 2);
    
    // Light up one of the three LEDs based on the ADC value
    if (adc_value < 375) {
        IO0SET = (1 << 0);  // Light up LED connected to P0.0 (Low ADC value)
    } else if (adc_value >= 375 && adc_value <= 800) {
        IO0SET = (1 << 1);  // Light up LED connected to P0.1 (Medium ADC value)
    } else {
        IO0SET = (1 << 2);  // Light up LED connected to P0.2 (High ADC value)
    }
}

int main() {
    unsigned int adc_value;

    ADC_init();   // Initialize ADC
    GPIO_init();  // Initialize GPIO for LEDs

    // Main loop
    while (1) {
        adc_value = ADC_read();  // Read the ADC value
        display_on_leds(adc_value);  // Display the ADC value on the LEDs
        delay(10000);  
    }
}