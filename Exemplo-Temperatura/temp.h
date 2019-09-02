/*
 * temp.h
 *
 *  Created on: 01/09/2019
 *      Author: erickreis
 */

#ifndef TEMP_H_
#define TEMP_H_

#include "includes.h"

#define TEMP_ADDR 0x18

enum {                      // Resolucao:
	RESOLUTION_0 = 0,       //      0.5°C
	RESOLUTION_1 = 1,       //      0.25°C
	RESOLUTION_2 = 2,       //      0.125°C
	RESOLUTION_3 = 3        //      0.0625°C
};

void temp_init();
void temp_time(unsigned int tempo);
float read_temp();


#endif /* TEMP_H_ */
