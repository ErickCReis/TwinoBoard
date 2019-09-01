/*
 * clock.c
 *
 *  Created on: 01/09/2019
 *      Author: erickreis
 */

#include "clock.h"

/*
 * Configuracao dos Clocks principais e auxiliares
 */
void clock_init(){
	PJSEL0 |= (BIT4);	        // pinos PJ.4 e PJ.5 sao configurados como pinos de
	PJSEL1 &= ~(BIT4);	        // cristal. PJSEL0.5 e PJSEL1.5 sao "Don't Care"

	CSCTL0 = 0xA500;	        // senha de acesso aos registradores do Clock System
	do {
		CSCTL5 &= ~XT1OFFG;	    // limpar flag de operacao defeituosa do cristal
		SFRIFG1 &= ~OFIFG;	    // limpar flag de interrupcao de operacao defeituosa
	} while (SFRIFG1 & OFIFG);	// teste de operacao do cristal. Se falhar, o programa trava aqui

	CSCTL1 |= DCOFSEL_3;	                                        // configura frequencia de DCOCLK como 8MHz
	CSCTL2 |= SELA_0 | SELS_3 | SELM_3;	                            // configura frequencias de clocks: ACLK=32768Hz, SMCLK=MCLK=DCOCLK=8MHz
	CSCTL3 &= ~(DIVS0 | DIVS1 | DIVS2 | DIVM0 | DIVM1 | DIVM2);	    // tira divisor de frequencia dos clocks
	CSCTL4 &= ~(XTS | XT1OFF);	                                    // configura pinos de cristal para baixa frequencia (32768Hz)
	CSCTL6 &=~ SMCLKREQEN;	                                        // desativa operacao de SMCLK em LPM
	CSCTL0_H = 0x00;	                                            // trava registradores do Clock System novamente
}
