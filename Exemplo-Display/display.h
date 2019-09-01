/*
 * display.h
 *
 *  Created on: 01/09/2019
 *      Author: erick
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "includes.h"

#define INTERRUPT_LIMIT 10000

// Cores predefinidas
typedef enum {BLUE=1, GREEN=2, CIAN=3, RED=4, PINK=5, YELLOW=6, WHITE=7} led_color;

void display_init();
void display_on(led_color cor);
void display_off();
void display_time(unsigned int tempo_ms);
void display_set_color(led_color cor);
void display_next_color();
void display_enable_rand();
void display_disable_rand();

#endif /* DISPLAY_H_ */
