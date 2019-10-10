/**
 * @file:  ds3231.h
 * @brief: Library created for using DS3231 RTC module
 *
 * Created by: 		Miradil Zeynalli
 * Date Created: 	24.08.2019
 * Last Modified: 	24.08.2019
 */

#ifndef RTC_H
#define RTC_H

/* INCLUDES */
#include <stdlib.h>
#include "stm32f4xx.h"


/* DEFINES */
#define DS3231_WR_ADDRESS 0xD0  // address when writing to the device
#define DS3231_RD_ADDRESS 0xD1  // address when reading from the device

// Struct for storing time in easy format
// bit-fields are used for memory "gain"
typedef struct {

	uint32_t sec 	 : 6;
	uint32_t min 	 : 6;
	uint32_t hour 	 : 5;
	uint32_t day 	 : 5;
	uint32_t month 	 : 4;
	uint32_t _unused : 6;  // extra 6 bits are left unused

	uint16_t year;
	char *week_day;

} rtc_t;


/* PUBLIC FUNCTION PROTOTYES */
void ds3231_set_time (uint8_t day, uint8_t month, uint16_t year, uint8_t hour, uint8_t minute, uint8_t second, uint8_t weekday);
rtc_t ds3231_read_time ();


#endif /* RTC_H */

/*** end of file ***/
