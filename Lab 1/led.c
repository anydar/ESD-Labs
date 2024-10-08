#include <LPC214x.h>
void delay() {
for (int j = 0; j < 1500000; j++);
}

int main() {
PINSEL0=0x00;
PINSEL1=0x00;
PINSEL2=0x00;
IODIR1 = 0xFF000000;
IOCLR1 = 0xFF000000;
while (1) {
IOSET1 = 0xFF000000;
delay();
IOCLR1 = 0xFF000000;
delay();
}
return 0;
}