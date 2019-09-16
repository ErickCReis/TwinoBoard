
#ifndef USCI_LIB_
#define USCI_LIB_

#include "includes.h"

#define SDA_PIN BIT6
#define SCL_PIN BIT7

void TI_USCI_I2C_receiveinit(unsigned char slave_address, unsigned char prescale);
void TI_USCI_I2C_transmitinit(unsigned char slave_address, unsigned char prescale);

void TI_USCI_I2C_receive(unsigned int byteCount, unsigned char *field);
void TI_USCI_I2C_transmit(unsigned int byteCount, unsigned char *field, int tempRead);

void wait_for_i2c_bus();
char is_i2c_busy();

//void fix_i2c();

void read_register(unsigned char, unsigned char, unsigned char, char);
extern unsigned char read_reg[2];

#endif
