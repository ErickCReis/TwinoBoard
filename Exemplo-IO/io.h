/*
 * io.h
 *
 *  Created on: 16/09/2019
 *      Author: Erick Reis
 */

#ifndef IO_H_
#define IO_H_

#include "includes.h"

#define IO_0    BIT0
#define IO_1    BIT1
#define IO_2    BIT2

enum {
    Input = (unsigned char)0,
    Output = (unsigned char)1,
};

enum {
    Low = (unsigned char)0,
    High = (unsigned char)1,
};

enum {
    Falling_Edge = (unsigned char)0,
    Rising_Edge = (unsigned char)1,
};

void io_enable(unsigned char pin, unsigned char op);
void io_set(unsigned char pin, unsigned char state);
void io_interrupt(unsigned char pin, unsigned char edge);

#endif /* IO_H_ */
