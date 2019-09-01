/*
 * display.c
 *
 *  Created on: 01/09/2019
 *      Author: erick
 */

#include "display.h"

// Variavel auxiliar para contagem de tempo
unsigned int interrupt_count = 0;

// Cor que um led especifico deve exibir
led_color chosen_color = WHITE;     // Inicializa como branco

// Flag para mudanca automatica de cores
unsigned randon_color = 0;

// Inicializa os pinos
void display_init()
{
    P1DIR |= 0x7;      // Definindo pinos como saida
    P1OUT &= ~0x7;     // Desligando display
}

// Desativa timer e liga display com uma cor predeterminada
void display_on(led_color cor)
{
    TB2CTL = TBCLR | MC0;   // Limpando contador e parando timer
    P1OUT |= cor;
}

// Desliga o display e desativa timer
void display_off()
{
    P1OUT &= ~0x7;          // Desligando display
    TB2CTL = TBCLR | MC0;   // Limpando contador e parando timer
}

// Configura interrupcao do timer B2 em milissegundos
void display_time(unsigned int tempo_ms)
{
    __disable_interrupt();
    TB2CCTL0 |= CCIE;                   // Ativando interrupcao do timer
    TB2CTL = TBSSEL_2 | MC_1 | TBCLR;   // Configuracao: Clock -> SMCLK(8MHZ)
                                        //               Divisor -> 1 (sem divisor)
                                        //               Modo -> UP

    TB2CCR0 = 8 * (tempo_ms/10);        // Define o tempo de ativacao
                                        // A divisao por 10 permite um alcance maior da contagem
    __enable_interrupt();
}

// Seleciona um cor especifica e desativa a mudanca automatica de cores
void display_set_color(led_color cor)
{
    chosen_color = cor;
    randon_color = 0;
}

// Altera a cor para a proxima da sequencia
void display_next_color()
{
    chosen_color++;
    if (chosen_color>WHITE) chosen_color=BLUE;
}

// Ativa a mudanca automatica de cores
void display_enable_rand()
{
    randon_color = 1;
}

// Desativa a mudanca automatica de cores
void display_disable_rand()
{
    randon_color = 0;
}

/*
* Rotina de interrupcao do timer B2, ativada de acordo com o tempo configurado.
* A interrupcao altera o estado do display a cada meio periodo predefinido.
* Identifica se a opcao de mudanca de cores automatica foi ativada.
*/
#pragma vector=TIMER2_B0_VECTOR
__interrupt void TIMERB2_ISR0(void)
{
    interrupt_count++;                          //
    if (interrupt_count == INTERRUPT_LIMIT/2)
    {
        P1OUT |= chosen_color;
    }
    else if(interrupt_count == INTERRUPT_LIMIT)
    {
        P1OUT &= ~chosen_color;
        if(randon_color) display_next_color();
        interrupt_count = 0;
    }
}
