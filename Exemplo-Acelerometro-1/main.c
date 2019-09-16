#include "includes.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	    // stop watchdog timer

	clock_init();

	__enable_interrupt();
    accel_init(Orientation);

    P1DIR |= BIT0 | BIT1 | BIT2;    // Inicializacao do display
    P1OUT &= ~(BIT0 | BIT1 | BIT2);

    volatile unsigned char status;

    while (1){
        status = accel_status();                                    // Atualizando posição
        if((status&0x01)==0x00){                                    // Para cima
            if((status&0x06)==0x00 || (status&0x06)==0x02){         // Vertical: LED azul
                P1OUT &= ~(BIT1 | BIT2);
                P1OUT |= BIT0;
            }
            else if((status&0x06)==0x04 || (status&0x06)==0x06){    // Horizontal: LED verde
                P1OUT &= ~(BIT0 | BIT2);
                P1OUT |= BIT1;
            }
        }
        else if((status&0x01)==0x01){                               // Para baixo: LED vermelho
            P1OUT &=~(BIT0 | BIT1);
            P1OUT |= BIT2;
        }
        else P1OUT &= ~(BIT0 | BIT1 | BIT2);

        LPM0;                                                       // Entrando em modo de baixo consumo
    }
	return 0;
}
