/*
 * rele.h
 *
 *  Created on: 01/09/2019
 *      Author: erick
 */

#ifndef RELE_H_
#define RELE_H_

#include "includes.h"

#define RELAY_PIN   BIT3
#define LED_PIN     BIT0

void rele_init();
void rele_on();
void rele_off();
void rele_time(unsigned int tempo);

#endif /* RELE_H_ */
