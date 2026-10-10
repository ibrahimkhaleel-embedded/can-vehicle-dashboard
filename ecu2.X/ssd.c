#include<xc.h>
#include "ssd_display.h"

void init_ssd_control(void)
{
	/* Setting PORTB as output for Data Lines */
	TRISD = 0x00;
	/* Setting SSD Enable lines as output */
	TRISA = TRISA & 0xF0;

	/* Switching OFF all the SSDs to start with */
	SSD_CNT_PORT = SSD_CNT_PORT & 0xF0;
}

void display(unsigned char Data[])
{
    volatile unsigned int i, wait;
    for(i = 0; i < 4; i++)
    {
        PORTD = Data[i];
        PORTA = (PORTA & 0xF0) | (1 << i);
        for(wait = 1000; wait--; );
    }
}

void init_led(void)
{
    TRISB = 0x00;
    PORTB = 0x00;
}