#include <lpc214x.h>
#include <stdint.h>
void delay_ms(uint16_t j){
	uint16_t x,i;
	for(i=0;i<j;i++)
	{
		for(x=0; x<6000; x++); /* loop to generate 1 milisecond delay with Cclk = 60MHz */
	}
}
int main (void)
	{
		uint16_t value;
		uint8_t i;
		i = 0;
		PINSEL1 = 0x00080000; /* P0.25 as DAC output */
		while(1){ 
			value = 1023;
			DACR = ( (1<<16) | (value<<6) );
	delay_ms(100);
	value = 0;
	DACR = ( (1<<16) | (value<<6) );
	delay_ms(100);
	}
	}
