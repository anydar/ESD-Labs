#include <lpc214x.h>
// Define control pins for the LCD
#define RS (1 << 11)  // RS connected to P0.11
#define E  (1 << 10)  // Enable connected to P0.10
// Simple delay function
void delay()
{
    int i, j;
    for(i = 0; i < 10; i++)      // Increase delay for simulation timing
        for(j = 0; j < 6000; j++);
}

// Function to send a command to the LCD
void LCD_cmd(unsigned char cmd)
{
  IOCLR1 = 0x00FF0000;                   // Clear data lines (P1.16 to P1.23)
    IOSET1 = (cmd << 16) & 0x00FF0000;     // Send command to P1.16 to P1.23
    
    IOCLR0 = RS;                           // RS = 0 (Command mode)            // RW = 0 (Write mode)
    delay();
    
    IOSET0 = E;                            // Enable high
    delay();
    IOCLR0 = E;                            // Enable low
    delay();
}

// Function to send data to the LCD
void LCD_data(unsigned char data)
{
    IOCLR1 = 0x00FF0000;                    // Clear data lines (P1.16 to P1.23)
    IOSET1 = (data << 16) & 0x00FF0000;     // Send data to P1.16 to P1.23
    
    IOSET0 = RS;                            // RS = 1 (Data mode)          // RW = 0 (Write mode)
    delay();
    
    IOSET0 = E;                             // Enable high
    delay();
    IOCLR0 = E;                             // Enable low
    delay();
}

// Function to initialize the LCD
void LCD_init()
{
    PINSEL0 = 0x00000000;  // Set P0 as GPIO
    PINSEL1 = 0x00000000;  // Set P1 as GPIO
    PINSEL2 = 0x00000000;  // Set all as GPIO
    IODIR1 = 0x00FF0000;   // Set P1.16 to P1.23 as outputs (Data lines)
    IODIR0 = 0x00140C00;   // Set P0.10 (E), P0.11 (RS), and P0.20 (RW) as outputs
    delay();               // Add a delay for power-on stabilization
	
    LCD_cmd(0x38);         // Function set: 8-bit, 2 lines, 5x7 font
    delay();               // Add some delay after commands
    
    LCD_cmd(0x01);         // Clear display
    delay();
    
    LCD_cmd(0x0F);         // Display on, cursor blinking
    delay();
    
    LCD_cmd(0x06);         // Entry mode set, cursor right
    delay();
}
// Main function to display "VIT" on the first line and "PUNE" on the second line
int main()
{
    LCD_init();            // Initialize the LCD
    
    LCD_cmd(0x80);         // Move cursor to first line
    LCD_data('V');         // Display 'V'
    LCD_data('I');         // Display 'I'
    LCD_data('T');         // Display 'T'
    
    LCD_cmd(0xC0);         // Move cursor to second line
    LCD_data('P');         // Display 'P'
    LCD_data('U');         // Display 'U'
    LCD_data('N');         // Display 'N'
    LCD_data('E'); 
    while(1);              // Infinite loop to keep the program running
}