/*
 * accel.h
 *
 *  Created on: 12/09/2019
 *      Author: Erick Reis
 */

#ifndef ACCEL_H_
#define ACCEL_H_

#include "includes.h"

#define ACCEL_ADDR      0x1D            // Endereço do modulo acelerometro
#define ACCEL_INT       BIT7            // Pino de interrupcao

enum {                 // Alcance de leitura:
    RANGE_2 = 0x00,    //      ±2 g
    RANGE_4 = 0x01,    //      ±4 g
    RANGE_8 = 0x02,    //      ±8 g
};

enum {                      // Modo:
    Orientation = 0x00,     //      Orientacao
    Motion = 0x01,          //      Deteccao de movimento
};

void accel_init(char mode);
unsigned char accel_orientation();

#endif /* ACCEL_H_ */
