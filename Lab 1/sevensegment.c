#include <lpc214x.h>

unsigned int segments[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};

void delay(void) {
    for (int j = 0; j < 100000; j++){
			
		}
}

int main() {
	PINSEL0 = 0x00;
	PINSEL1 = 0x00;
	PINSEL2 = 0x00;
	
	IODIR1 = 0x00FF0000;	//P1.16 to P1.23
	IODIR0 = 0x00000C00;	//P0.10 and P0.11
	IOSET0 = 0x00000C00;
	
	IOCLR1 = 0x00FF0000;
	unsigned int m,n;
  while(1){
		for(int i=0; i<16; i++){
			/*if(i%2 == 0){
				IOSET0 = 0x00000800;
				IOCLR0 = 0X00000400;
			}else{
				IOSET0 = 0X00000400;
				IOCLR0 = 0X00000800;
			}*/
			IOSET0 = 0X00000400;
			m = segments[i] << 16;
			IOSET1 = m;
			delay();
			IOCLR1 = m;
		}
		IOCLR1 = 0x00FF0000;
	}
	
	return 0;
}