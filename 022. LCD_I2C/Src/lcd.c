/*
 * @file:  lcd.c
 * @brief: Library created for LCD (both 20x4 and 16x2) with PCF8574T
 * module using I2C peripheral
 *
 * Created by: 		Miradil Zeynalli
 * Date Created: 	02.09.2019
 * Last Modified: 	02.09.2019
 */

/* INCLUDES */
#include "lcd.h"
#include "i2c.h"

/* DEFINES */
#define LCD_CLEAR_DISPLAY 					0x01
#define LCD_CURSOR_RETURN_HOME 				0x02
#define LCD_WRITE_DIR	 					0x04
#define LCD_DISPLAY_SETTINGS			 	0x08
#define LCD_CURSOR_SHIFT					0x10
#define LCD_FUNCTION_SET	 				0x20

// on falling edge, display reads data of pins
#define e_set()   			i2c_send_byte(lcd_state |= 0x04)
#define e_reset()   		i2c_send_byte(lcd_state &= ~0x04)

// Mode: Command (0) or Data (1)
#define rs_set()    		i2c_send_byte(lcd_state |= 0x01)
#define rs_reset()  		i2c_send_byte(lcd_state &= ~0x01)

// Background light
#define set_backg_light()   i2c_send_byte(lcd_state |= 0x08)

// set to write mode
#define set_write()  		i2c_send_byte(lcd_state &= ~0x02)

/* STATIC VARIABLES */
static uint8_t lcd_state = 0;
const static uint8_t pos[] = {0x00, 0x40, 0x14, 0x54};

/* PROTOTYPES */
static void lcd_print_char(char ch);
static void write_half_byte(uint8_t bt);
static void write_full_byte(uint8_t bt, uint8_t mode);
static void i2c_send_byte(uint8_t bt);
__STATIC_INLINE void micros_delay(__IO uint32_t micros);


/* PUBLIC FUNCTIONS */
void lcd_init(lcd_conf_t *settings)
{
	if (NULL == settings)
		settings = &(lcd_conf_t) {.write_to_right = 1, .display_on = 1, .cursor_on = 1, \
									.cursor_blink = 0,.bits_8 = 0, .lines_2 = 1, .fonts_5x11 = 0};

	// According to datasheet, repeat this command three times
	HAL_Delay(15);
	write_half_byte(0x03);
	HAL_Delay(4);

	write_half_byte(0x03);
	micros_delay(100);

	write_half_byte(0x03);
	HAL_Delay(1);

	// return home
	write_half_byte(LCD_CURSOR_RETURN_HOME);
	HAL_Delay(1);


	uint8_t cmd;
	// set functions
	cmd = LCD_FUNCTION_SET | (settings->bits_8 << 4) | (settings->lines_2 << 3) | (settings->fonts_5x11 << 2);
	write_full_byte(cmd, 0);
	HAL_Delay(1);

	// set screen settings
	cmd = LCD_DISPLAY_SETTINGS | (settings->display_on << 2) | (settings->cursor_on << 1) | settings->cursor_blink;
	write_full_byte(cmd, 0);
	HAL_Delay(1);

	//
	write_full_byte(LCD_CLEAR_DISPLAY, 0);
	HAL_Delay(2);

	// cursor settings
	cmd = LCD_WRITE_DIR | (settings->write_to_right << 1);
	write_full_byte(cmd, 0);
	HAL_Delay(1);

	set_backg_light();
	set_write();
}

void lcd_set_cursor_pos(uint8_t x, uint8_t y)
{
	write_full_byte((x + pos[y]) | 0x80, 0);
	HAL_Delay(1);
}

void lcd_print(char *s)
{
	while(*s)
		lcd_print_char(*s++);
}

void lcd_clear()
{
	write_full_byte(LCD_CLEAR_DISPLAY, 0);
    micros_delay(1500);
}


/* PRIVATE FUNCTIONS */
static void lcd_print_char(char ch)
{
	write_full_byte(ch, 1);
}

static void write_half_byte(uint8_t bt)
{
	bt <<= 4;

	e_set();
	micros_delay(50);

	i2c_send_byte(lcd_state | bt);

	e_reset();
	micros_delay(50);

}

static void write_full_byte(uint8_t bt, uint8_t mode)
{
	(mode) ? rs_set() : rs_reset();

	write_half_byte(bt >> 4);
	write_half_byte(bt);
}

static void i2c_send_byte(uint8_t bt)
{
	uint8_t buff[] = {bt};
	i2c_write(&hi2c1, PCF8574_WR_ADDRESS, buff, 1);
}

__STATIC_INLINE void micros_delay(__IO uint32_t micros)
{

	micros *= (SystemCoreClock / 1000000) / 5;

	/* Wait till done */
	while (micros--)
	{
	}

}
