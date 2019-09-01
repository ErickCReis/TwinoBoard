#include "includes.h"

#define LED_BLUE    BIT0
#define LED_GREEN   BIT1
#define LED_RED     BIT2

#define LEDS LED_RED+LED_GREEN+LED_BLUE

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	clock_init();
	display_init();
	display_time(1000);

	return 0;
}

