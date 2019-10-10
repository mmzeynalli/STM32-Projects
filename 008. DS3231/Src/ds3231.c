/**
 * @file:  ds3231.c
 * @brief: Library created for using DS3231 RTC module
 *
 * Created by: 		Miradil Zeynalli
 * Date Created: 	24.08.2019
 * Last Modified: 	24.08.2019
 */

/* INCLUDES */
#include "ds3231.h"
#include "i2c.h"

/* VARIABLES */
extern I2C_HandleTypeDef hi2c1;

/* PRIVATE FUNCTION PROTOTYPES */
static rtc_t array_to_struct (uint8_t buff[7]);
static uint8_t _decode (uint8_t val);
static uint8_t _encode (uint8_t val);


/* PUBLIC FUNCTIONS */

/*!
 * @brief: Set clock of DS3231
 *
 * @param[in] day: 		Day of the month
 * @param[in] month: 	Number of month (Jan = 1)
 * @param[in] year: 	Year
 * @param[in] hour: 	Hour in 24h format
 * @param[in] hour: 	Hour in 24h format
 * @param[in] minute: 	Minutes
 * @param[in] second: 	Seconds
 * @param[in] weekday:	Number of weekday (Mon = 1)
 *
 * @return: void
 */
void ds3231_set_time (uint8_t day, uint8_t month, uint16_t year, uint8_t hour, uint8_t minute, uint8_t second, uint8_t weekday)
{
	uint8_t buff[8];
	buff[0] = 0x00;
	buff[1] = _encode(second);
	buff[2] = _encode(minute);
	buff[3] = _encode(hour);
	buff[4] = _encode(weekday);
	buff[5] = _encode(day);
	buff[6] = _encode(month);
	buff[7] = _encode((uint8_t) (year - 2000));

	// write 8 bytes to the device (1st byte is the address of the register to start write)
	i2c_write(&hi2c1, (uint8_t) DS3231_WR_ADDRESS, (uint8_t *) buff, 7 + 1);
}

/*!
 * @brief: Read current time from module
 *
 * @param: No parameters
 *
 * @return: Time data collected rtc_t struct
 *
 */
rtc_t ds3231_read_time ()
{
	uint8_t buff[7] = {0x00};

	i2c_write(&hi2c1, (uint8_t) DS3231_WR_ADDRESS, buff, 1);  // send address

	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
	{
		// wait for it to be ready
	}

	i2c_read(&hi2c1, (uint8_t) DS3231_RD_ADDRESS, (uint8_t *) buff, 7);  // send address

	return array_to_struct(buff);

}


/* PRIVATE FUNCTIONS */
/*!
 * @brief: Collecting time data into rtc_t struct
 *
 * @param: Array of time data (read from module)
 *
 * @return: Time data collected rtc_t struct
 *
 */
static rtc_t array_to_struct (uint8_t buff[7])
{
	rtc_t rtc;
	char *weekday_name [] = {"", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

	rtc.sec   		= _decode(buff[0]);
	rtc.min   		= _decode(buff[1]);
	rtc.hour  		= _decode(buff[2]);
	rtc.week_day	= weekday_name[_decode(buff[3])];
	rtc.day			= _decode(buff[4]);
	rtc.month 		= _decode(buff[5]);
	rtc.year  		= _decode(buff[6]) + 2000;

	return rtc;
}

/*!
 * @brief: Decoding data into human-readable numbers
 *
 * @param: Value read from registers
 *
 * @return: Decoded human-readable number
 *
 */
static uint8_t _decode (uint8_t val)
{
	uint8_t decoded = ((val >> 4) * 10 + (0x0F & val));
    return decoded;
}

/*!
 * @brief: Encoding data into "register-readable" format
 *
 * @param: Value needed to be encoded
 *
 * @return: Encoded number in register-understandable format
 *
 */
static uint8_t _encode (uint8_t val)
{
	uint8_t encoded = ((val / 10) << 4) + (val % 10);
	return encoded;
}

/*** end of file ***/

