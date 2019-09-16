#include "includes.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	    // stop watchdog timer

	clock_init();

	__enable_interrupt();
    accel_init(Motion);

    P1DIR |= BIT0 | BIT1 | BIT2;    // Inicializacao do display
    P1OUT &= ~(BIT0 | BIT1 | BIT2);

    P1OUT |= BIT1;
    __delay_cycles(1000000);    // led acende por 0.5s
    P1OUT &=~ BIT1;

    volatile unsigned char status;

    while(1){
        status = accel_status();            // Verificando movimento
        if((status&0x30)==0x20){            // eixo Z: LED azul
            P1OUT &= ~(BIT1 | BIT2);
            P1OUT |= BIT0;
            __delay_cycles(4000000);        // led acende por 0.5s
        }
        else if((status&0x0C)==0x08){       // eixo Y: LED verde
            P1OUT &= ~(BIT0 | BIT2);
            P1OUT |= BIT1;
            __delay_cycles(4000000);        // led acende por 0.5s
        }
        else if((status&0x03)==0x02){       // eixo X: LED vermelho
            P1OUT &=~(BIT0 | BIT1);
            P1OUT |= BIT2;
            __delay_cycles(4000000);        // led acende por 0.5s
        }
        P1OUT &= ~(BIT0 | BIT1 | BIT2);

        LPM0;                               // entrando no modo de baixo consumo
    }
	return 0;
}
