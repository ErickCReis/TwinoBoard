#include "includes.h"

#define TARGET_TEMP 30

int main(void){
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    clock_init();               // Configurando clocks
    temp_time(10);              // Definindo tempo de atualizacao

    __enable_interrupt();       // Habilitando interrupcoes
    temp_init();                // Iniializando sensor de temperatura

    P1DIR |= BIT0 | BIT1 | BIT2;    // Inicializacao do display
    P1OUT &= ~(BIT0 | BIT1 | BIT2);

    volatile float temp;

    while(1)
    {
        temp = read_temp();         // Realiza a leitura
        P1OUT &= ~(BIT1 | BIT2);
        P1OUT |= BIT0;              // Acende um LED azul por 0.1 s
        __delay_cycles(800000);
        P1OUT &= ~BIT0;

        if (temp<TARGET_TEMP){
            P1OUT &= ~BIT2;
            P1OUT |= BIT1;          // Acende um LED verde
        }
        else {
            P1OUT &= ~BIT1;
            P1OUT |= BIT2;          // Acende um LED vermelho
        }
        LPM0;
    }
    return 0;
}
