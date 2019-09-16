/*
 * accel.c
 *
 *  Created on: 12/09/2019
 *      Author: Erick Reis
 */

#include "accel.h"

void accel_init(char mode){
    wait_for_i2c_bus();
    TI_USCI_I2C_transmitinit(ACCEL_ADDR, 0x14);     // iniciar I2C 400kHz
    wait_for_i2c_bus();

    if(mode==Orientation)
    {
        TI_USCI_I2C_transmit(2, (unsigned char[] ) { 0x11, 0xC0 }, 0);    // modo de deteccao de orientacao
        wait_for_i2c_bus();
        TI_USCI_I2C_transmit(2, (unsigned char[] ) { 0x2D, 0x10 }, 0);    // habilitando interrupcao na mudança de orientacao
        Status_Addr = Orientation_Status;
    }
    else if(mode==Motion)
    {
        TI_USCI_I2C_transmit(2, (unsigned char[] ) { 0x0E, RANGE_2 }, 0);       // configurando valor do alcance
        wait_for_i2c_bus();
        TI_USCI_I2C_transmit(2, (unsigned char[] ) { 0x15, 0xF8 }, 0);          // modo de deteccao de movimento
        wait_for_i2c_bus();
        TI_USCI_I2C_transmit(3, (unsigned char[] ) { 0x17, 0x18, 0x02 }, 0);    // configuracao de limiar para deteccao de movimento. Esses valores podem ser modificados para alterar a sensibilidade do acelerometro
        wait_for_i2c_bus();
        TI_USCI_I2C_transmit(2, (unsigned char[] ) { 0x2D, 0x04 }, 0);          // habilita interrupcao quando detecta movimento
        Status_Addr = Motion_Status;
    }

    wait_for_i2c_bus();
    TI_USCI_I2C_transmit(2, (unsigned char[] ) { 0x2A, 0x01 }, 0);    // habilitando modo ativo
    wait_for_i2c_bus();

    //Configurando pino de alerta
    P3DIR &=~ACCEL_INT;
    P3OUT |= ACCEL_INT;  // resistor de pull-up selecionado
    P3REN |= ACCEL_INT;  // resistor habilitado
    P3IES |= ACCEL_INT;  // seleciona borda de descida como gatilho para alerta
    P3IE  |= ACCEL_INT;
}

unsigned char accel_status(){
    read_register(ACCEL_ADDR, Status_Addr, 1, 0x14);     // lendo registrador de status de orientação
    return read_reg[0];
}

/*
* Rotina de interrupcao da porta 3, onde o acelerometro esta conectado
* Simplesmente tira o processador do LPM, fazendo com que o programa continue
*/
#pragma vector=PORT3_VECTOR
__interrupt void p3_isr(){
    switch (P3IV){
    case P3IV_P3IFG7:                   // interrupcao de acelerometro
        __delay_cycles(500);            // debouncing
        LPM0_EXIT;                      // retirando do modo de baixo consumo
        P3IFG &=~ACCEL_INT;             // desativando flag de interrupcao
        break;
    }
}
