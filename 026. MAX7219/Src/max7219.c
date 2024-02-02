/*
 * max7219.c
 *
 *  Created on: Sep 13, 2019
 *      Author: Miradil Zeynalli
 */


#include "max7219.h"
#include "spi.h"

#define cs_set() HAL_GPIO_WritePin(SPI3, GPIO_PIN_0, GPIO_PIN_RESET)
#define cs_reset() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET)



