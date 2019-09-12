/*
 * accel.c
 *
 *  Created on: 12/09/2019
 *      Author: Erick Reis
 */

#include "accel.h"

void accel_init(char mode){
    wait_for_i2c_bus();
    TI_USCI_I2C_transmitinit(ACCEL_ADDR, 20);     // iniciar I2C 400kHz
    wait_for_i2c_bus();

    if(mode==Orientation)
    {
        TI_USCI_I2C_transmit(2, (unsigned char[] ) { 0x0E, RANGE_2 }, 0);       // configurando valor da escala
        wait_for_i2c_bus();
        TI_USCI_I2C_transmit(2, (unsigned char[] ) { 0x11, 0b11000000 }, 0);    // modo de detecção de orientação
        wait_for_i2c_bus();
        TI_USCI_I2C_transmit(2, (unsigned char[] ) { 0x2D, 0b00010000 }, 0);    // habilitando interrupção na mudança de orientação
    }
    else
    {

    }

    wait_for_i2c_bus();
    TI_USCI_I2C_transmit(2, (unsigned char[] ) { 0x2A, 0b00000001 }, 0);    // habilitando modo ativo
    wait_for_i2c_bus();

    //Configurando pino de alerta
    P3DIR &=~ACCEL_INT;
    P3OUT |= ACCEL_INT;  // resistor de pull-up selecionado
    P3REN |= ACCEL_INT;  // resistor habilitado
    P3IES |= ACCEL_INT;  // seleciona borda de descida como gatilho para alerta
    P3IE  |= ACCEL_INT;
}

unsigned char accel_orientation(){
    read_register(ACCEL_ADDR, 0x10, 1, 20);     // lendo registrado de status de orientação
    return read_reg[0];
}

/*
* Rotina de interrupcao da porta 3, onde o acelerometro esta conectado
* Simplesmente tira o processador do LPM, fazendo com que o programa continue
*/
#pragma vector = PORT3_VECTOR
__interrupt void p3_isr(){
    switch (P3IV){
    case P3IV_P3IFG4:           // interrupcao de acelerometro
        __delay_cycles(500);    // debouncing
        LPM0_EXIT;
        P3IFG &=~ACCEL_INT;
        break;
    }
}
