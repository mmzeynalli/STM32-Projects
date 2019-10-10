/*
 * hmc5883l.c
 *
 *  Created on: Sep 6, 2019
 *      Author: Huseyn Gambarov
 */

#include <qmc5883l.h>
#include "i2c.h"
#include <stdio.h>

#ifdef i2c1
#define QMC5883L_I2C &hi2c1
#endif

#ifdef i2c2
#define QMC5883L_I2C &hi2c2
#endif

/* Register numbers */
#define QMC5883L_X_LSB 0
#define QMC5883L_X_MSB 1
#define QMC5883L_Y_LSB 2
#define QMC5883L_Y_MSB 3
#define QMC5883L_Z_LSB 4
#define QMC5883L_Z_MSB 5
#define QMC5883L_STATUS 6
#define QMC5883L_TEMP_LSB 7
#define QMC5883L_TEMP_MSB 8
#define QMC5883L_CONFIG 9
#define QMC5883L_CONFIG2 10
#define QMC5883L_RESET 11
#define QMC5883L_RESERVED 12
#define QMC5883L_CHIP_ID 13

static void i2c_read (I2C_HandleTypeDef *hi, uint8_t dev_addr, uint8_t *buffer, uint16_t buff_size);
static void i2c_write (I2C_HandleTypeDef *hi, uint8_t dev_addr, uint8_t *buffer, uint16_t buff_size);

void qmc5883l_init()
{

	uint8_t data[] = {QMC5883L_RESET, 0x01};
	i2c_write(QMC5883L_I2C, QMC5883L_WRITE_ADDRESS, data, 2); // reset sensor

	data[0] = QMC5883L_CONFIG;
	data[1] = 0x05; // OS512, 2GAUSS, 50 HZ, Continuous mode

	i2c_write(QMC5883L_I2C, QMC5883L_WRITE_ADDRESS, data, 2);

}

uint8_t qmc5883l_is_ready()
{
	uint8_t status[1];

	i2c_read(QMC5883L_I2C, QMC5883L_READ_ADDRESS, status, 1);

	return *status & 1;
}

void qmc5883l_read_data(uint16_t *x, uint16_t *y, uint16_t *z)
{

	while(!qmc5883l_is_ready()) {
		//printf("Device is not ready yet!\r\n");
	}

	uint8_t rx_buff[6];

	i2c_read(QMC5883L_I2C, QMC5883L_READ_ADDRESS, rx_buff, 6);


	*x = rx_buff[1];
	*x = ((*x) << 8) | rx_buff[0];

	*y = rx_buff[3];
	*y = ((*y) << 8) | rx_buff[2];

	*z = rx_buff[4];
	*z = ((*z) << 8) | rx_buff[4];

	printf("%u, %u, %u\r\n", *x, *y, *z);
}


static void i2c_write (I2C_HandleTypeDef *hi, uint8_t dev_addr, uint8_t *buffer, uint16_t buff_size)
{

	while (HAL_I2C_Master_Transmit(hi, dev_addr, buffer, buff_size, 0xFFFF) != HAL_OK)
	{
		printf("Error occurred in writing to device\r\n");
	}

}


static void i2c_read (I2C_HandleTypeDef *hi, uint8_t dev_addr, uint8_t *buffer, uint16_t buff_size)
{
	while (HAL_I2C_Master_Receive(hi, dev_addr, buffer, buff_size, 0xFFFF) != HAL_OK)
	{
		printf("Error occurred in reading from device\r\n");
	}
}
