/*
 * temp.c
 *
 *  Created on: 01/09/2019
 *      Author: erickreis
 */

#include "temp.h"

/*
* Configuracao inicial do sensor de temperatura
*/
void temp_init(){
	wait_for_i2c_bus();
	TI_USCI_I2C_transmitinit(TEMP_ADDR, 0x14);
	wait_for_i2c_bus();
	TI_USCI_I2C_transmit(2,(unsigned char[]) { 0x08, RESOLUTION_0}, 0);     // Definindo resolucao da temperatura
	wait_for_i2c_bus();
}

// Configura interrupcao do timer B0 em segundos
void temp_time(unsigned int tempo)
{
    __disable_interrupt();
    TB0CCTL0 |=  CCIE;                          // Ativando interrupcao do timer
    TB0CTL = TBSSEL_1 | ID_3 | MC_1 | TACLR;    // Configuracao: Clock -> ACLK (32768Hz)
                                                //               Divisor -> 8
                                                //               Modo -> UP

    TB0CCR0 = 4096 * tempo;
    __enable_interrupt();
}

/*
* Requisita a ultima leitura do sensor de temperatura e faz a transformacao de valores
*/
float read_temp(){
	read_register(TEMP_ADDR, 0x05, 2, 0x14);	// le valor da temperatura no registrador 0x05

	float temp;
	// Transformacoes de temperatura (ver documentacao do sensor de temperatura):
	temp = ((read_reg[0] & 0x0F) * 16) + ((read_reg[1]) / 16.0f);

	if (read_reg[0] & 0x10)	// temperatura negativa
		temp=256-((read_reg[0] & 0x0F) * 16) + ((read_reg[1]) / 16.0f);

	return temp;
}

// Rotina de interrupcao do timer B0, ativada de acordo com o tempo configurado
#pragma vector=TIMER0_B0_VECTOR
__interrupt void TIMERB2_ISR0(void)
{
    LPM0_EXIT;      // Retira do LPM para que o programa volte a ser executado
}
