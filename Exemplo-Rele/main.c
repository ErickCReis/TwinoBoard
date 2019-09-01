#include "includes.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	clock_init();
	rele_init();
	rele_time(10);
	//rele_on();

	LPM0;

	return 0;
}
