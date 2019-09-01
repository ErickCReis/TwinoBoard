/*
 * display.h
 *
 *  Created on: 1 de set de 2019
 *      Author: erick
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "includes.h"

#define INTERRUPT_LIMIT 1000

#define LED_BLUE    BIT0
#define LED_GREEN   BIT1
#define LED_RED     BIT2

#define LEDS LED_RED+LED_GREEN+LED_BLUE

void display_init();
void display_time(unsigned int tempo_ms);

#endif /* DISPLAY_H_ */
