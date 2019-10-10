/*
 * 74hc595.c
 *
 *  Created on: Sep 3, 2019
 *      Author: User
 */

#include <seg7_display.h>
#include "spi.h"

static uint8_t reverse_bits(uint8_t num);

// hex representation of segments. lsb -> A, msb -> DP
static uint8_t digits[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

bool disp_logic;
bool q0_to_seg_a;


void segdisp_init(bool is_common_anode, bool seg_a_is_connected_to_q0)
{
	disp_logic = is_common_anode;
	q0_to_seg_a = seg_a_is_connected_to_q0;

	cs_set();
}

void segdisp_show_digit(uint8_t digit)
{

	uint8_t dt = digits[digit];

	if (disp_logic == common_anode)
		dt = ~dt;

	if (q0_to_seg_a != true)
		dt = reverse_bits(dt);

	uint8_t tx_buff[] = {dt};
	HAL_SPI_Transmit(&hspi3, (uint8_t *) tx_buff, 1, 1000);
	cs_tick();
}

static uint8_t reverse_bits(uint8_t num)
{
    uint8_t NO_OF_BITS = sizeof(num) * 8;
    uint8_t reverse_num = 0;

    uint8_t i;

    for (i = 0; i < NO_OF_BITS; i++)
        if((num & (1 << i)))
           reverse_num |= 1 << ((NO_OF_BITS - 1) - i);

    return reverse_num;
}

