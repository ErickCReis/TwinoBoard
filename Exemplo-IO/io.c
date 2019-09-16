/*
 * io.c
 *
 *  Created on: 16/09/2019
 *      Author: Erick Reis
 */

#include "io.h"

void io_enable(unsigned char pin, unsigned char op){
    if(op==Output){
        P3DIR |= pin;
        P3DIR &=~pin;
    }
    else if(op==Input){
        P3DIR &=~pin;
        P3OUT |= pin;  // resistor de pull-up selecionado
        P3REN |= pin;  // resistor habilitado
    }
}

void io_set(unsigned char pin, unsigned char state){
    if(state==High) P3DIR |= pin;
    else if(state==Low) P3DIR &=~pin;
}

void io_interrupt(unsigned char pin, unsigned char edge){
    if(edge==Falling_Edge){
        P3IES |= pin;  // seleciona borda de descida como gatilho para alerta
        P3IE  |= pin;
    }
    else if(edge==Rising_Edge){
        P3IES &=~pin;  // seleciona borda de subida como gatilho para alerta
        P3IE  |= pin;
    }
}

/*
* Rotina de interrupcao da porta 3, onde o acelerometro esta conectado
* Simplesmente tira o processador do LPM, fazendo com que o programa continue
*/
#pragma vector=PORT3_VECTOR
__interrupt void p3_isr(){
    switch (P3IV){
    case P3IV_P3IFG0:                   // interrupcao de IO_0
        P1OUT |= BIT0;
        __delay_cycles(4000000);
        P1OUT &=~BIT0;
        P3IFG &= ~IO_0;                 // desativando flag de interrupcao
        break;
    case P3IV_P3IFG1:                   // interrupcao de IO_1
        P1OUT |= BIT1;
        __delay_cycles(4000000);
        P1OUT &=~BIT1;
        P3IFG &= ~IO_1;                 // desativando flag de interrupcao
        break;
    case P3IV_P3IFG2:                   // interrupcao de IO_2
        P1OUT |= BIT2;
        __delay_cycles(4000000);
        P1OUT &=~BIT2;
        P3IFG &= ~IO_2;                 // desativando flag de interrupcao
        break;
    }
}
