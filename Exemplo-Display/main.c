#include "includes.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	clock_init();               // Configurando clocks

	display_init();             // Inicializando display
	display_time(2000);         // Configurando tempo do display
	display_enable_rand();      // Habilitando cores sequenciais
	LPM0;                       // Entrando em Low Power Mode 0

	return 0;
}

