/*
 * gpio1.h
 *
 *  Created on: Nov 20, 2017
 *      Author: Brandon
 */

#ifndef GPIO1_H_
#define GPIO1_H_

#include <stdint.h>
#include "msp.h"

void gpio_config();
void gpio_pwmconfig();
void gpio_LEDconfig();
void gpio_LEDout();

#endif /* GPIO1_H_ */
