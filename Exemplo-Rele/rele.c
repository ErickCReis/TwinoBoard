/*
 * rele.c
 *
 *  Created on: 1 de set de 2019
 *      Author: erick
 */

#include "rele.h"

// Inicializa os pinos
void rele_init()
{
    P3DIR |= RELAY_PIN;
    P3OUT &= ~RELAY_PIN;

    P1DIR |= LED_PIN;
    P1OUT &= ~LED_PIN;
}

// Liga rele
void rele_on()
{
    P3OUT |= RELAY_PIN;
    P1OUT |= LED_PIN;
}

// Desliga rele
void rele_off()
{
    P3OUT &= ~RELAY_PIN;
    P1OUT &= ~LED_PIN;
}

// Configura interrupcao do timer B1 em segundos
void rele_time(unsigned int tempo)
{
    __disable_interrupt();
    TB1CCTL0 |=  CCIE;                          // Ativando interrupcao do timer
    TB1CTL = TBSSEL_1 | ID_3 | MC_1 | TACLR;    // Configuracao: Clock -> ACLK (32768Hz)
                                                //               Divisor -> 8
                                                //               Modo -> UP

    TB1CCR0 = 4096 * tempo;
    __enable_interrupt();
}

// Rotina de interrupcao do timer B1, ativada de acordo com o tempo configurado.
#pragma vector=TIMER1_B0_VECTOR
__interrupt void TIMERB2_ISR0(void)
{
    P3OUT ^= RELAY_PIN;
    P1OUT ^= LED_PIN;
}
