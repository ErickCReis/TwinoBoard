/*
 * display.c
 *
 *  Created on: 01/09/2019
 *      Author: erick
 */

#include "display.h"

unsigned int interrupt_count = 0;

void display_init()             //Inicializa portas
{
    P1DIR |= LEDS;      //Definindo potas como saida
    P1OUT &= ~LEDS;     //Desligando display
}

void display_time(unsigned int tempo_ms)     // Configura interrupcao do timer
{
    __disable_interrupt();

    TB2CCTL0 |= CCIE;                   // Ativando interrupcao
    TB2CTL = TBSSEL_2 | MC_1 | TBCLR;   // Configuração: Clock -> SMCLK(8MHZ)
                                        //              Divisor -> 1 (sem divisor)
                                        //              Modo -> UP

    TB2CCR0 = 8 * tempo_ms;                     // Define o tempo de ativacao

    __enable_interrupt();
}

/*
* Rotina de interrupcao do timer B2 ativada a cada 1,9ms.
* A interrupcao alterna rapidamente os leds acesos, passando
* a impressao que todos estao acesos ao mesmo tempo.
* Depois de 1,9s, a cor dos leds e alterada.
*/
#pragma vector=TIMER2_B0_VECTOR
__interrupt void TIMERB2_ISR0(void) {
    interrupt_count++;
    if (interrupt_count == INTERRUPT_LIMIT){
        P1OUT ^= LEDS;
        interrupt_count=0;
    }
}
