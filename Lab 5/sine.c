#include <lpc214x.h>
#include <stdint.h>
#include <math.h>  // Include math library for calculating sine values
#define PI 3.14159265
#define SINE_RESOLUTION 64  // Number of samples in one period of the sine wave
void delay_ms(uint16_t j) {
    uint16_t x, i;
    for (i = 0; i < j; i++) {
        for (x = 0; x < 6000; x++); /* loop to generate 1 millisecond delay with Cclk = 60MHz */
    }
}
int main(void) {
    uint16_t sine_table[SINE_RESOLUTION];
    uint8_t i;
    uint16_t value;
    // Generate sine lookup table
    for (i = 0; i < SINE_RESOLUTION; i++) {
        sine_table[i] = (uint16_t)((sin(i * 2 * PI / SINE_RESOLUTION) + 1) * 511.5);  // Scale to 0-1023 range
    }
    PINSEL1 = 0x00080000; /* P0.25 as DAC output */
    while (1) {
        // Output sine wave using lookup table
        for (i = 0; i < SINE_RESOLUTION; i++) {
            value = sine_table[i];  // Get the sine value from the lookup table
            DACR = (1 << 16) | (value << 6);  // Write value to DACR register
            delay_ms(1);  // Adjust delay for required frequency
        }
    }
}
