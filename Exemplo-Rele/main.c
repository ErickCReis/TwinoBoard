#include "includes.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	clock_init();               // Configurando clocks
	rele_init();                // Inicializando rele
	rele_time(10);              // Configurando tempo de ativacao
	LPM0;                       // Entrando em Low Power Mode 0

	return 0;
}
