/*
 * @file:  lcd.h
 * @brief: Library created for LCD (both 20x4 and 16x2) with PCF8574T
 * module using I2C peripheral
 *
 * Created by: 		Miradil Zeynalli
 * Date Created: 	02.09.2019
 * Last Modified: 	02.09.2019
 */

#ifndef LCD_H
#define LCD_H

/* INCLUDES */
#include <stdint.h>
#include <stdbool.h>

/* DEFINES */
#define PCF8574_ADDRESS 	0x27U  // all pins are connected to Vdd (all Vss = 0x20)
#define PCF8574_WR_ADDRESS 	0x4EU
#define PCF8574_RD_ADDRESS 	0x4FU


// Struct for LCD configurations
typedef struct
{
	uint8_t write_to_right;

	uint8_t display_on;
	uint8_t cursor_on;
	uint8_t cursor_blink;

	uint8_t bits_8;
	uint8_t lines_2;
	uint8_t fonts_5x11;

} lcd_conf_t;

/* PROTOTYPES */
void lcd_init(lcd_conf_t *settings);
void lcd_set_cursor_pos(uint8_t x, uint8_t y);
void lcd_print(char *s);
void lcd_clear();

#endif /* LCD_H */
