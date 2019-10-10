/*
 * 74hc595.h
 *
 *  Created on: Sep 3, 2019
 *      Author: User
 */

#ifndef SEG7_DISPLAY_H
#define SEG7_DISPLAY_H

#include <stdint.h>
#include <stdbool.h>

#define cs_set() 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET)
#define cs_reset() 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET)
#define cs_tick() 	cs_reset(); cs_set()

#define common_anode 	1
#define common_cathode  0

void segdisp_init(bool is_common_anode, bool seg_a_is_connected_to_q0);
void segdisp_show_digit(uint8_t digit);

#endif /* SEG7_DISPLAY_H */
