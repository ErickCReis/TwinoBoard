#include <msp430fr5729.h>
//#include <clock.h>

#define LED_BLUE     BIT0
#define LED_GREEN   BIT1
#define LED_RED    BIT2

#define LEDS LED_RED+LED_GREEN+LED_BLUE

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR |= LEDS;
	P1OUT &= ~LEDS;

	long int i=0;

	while(1)
	{
	    P1OUT |= LED_RED;
	    for(i=200000; i>0; i--);     // delay
	    P1OUT &= ~LED_RED;
	    P1OUT |= LED_GREEN;
	    for(i=200000; i>0; i--);     // delay
	    P1OUT &= ~LED_GREEN;
	    P1OUT |= LED_BLUE;
	    for(i=200000; i>0; i--);     // delay
	    P1OUT &= ~LED_BLUE;
	}
	return 0;
}
