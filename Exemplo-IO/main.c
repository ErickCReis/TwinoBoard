#include "includes.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	clock_init();

    P1DIR |= BIT0 | BIT1 | BIT2;    // Inicializacao do display
    P1OUT &= ~(BIT0 | BIT1 | BIT2);

	io_enable(IO_0, Input);
	io_interrupt(IO_0, Rising_Edge);

	__enable_interrupt();

	LPM0;

	return 0;
}
