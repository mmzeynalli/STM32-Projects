/*
 * print.c
 *
 *  Created on: Oct 7, 2019
 *      Author: Miradil Zeynalli
 */

#include "print.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "usart.h"

static uint8_t vprint(UART_HandleTypeDef *huart, const char *fmt, va_list argp);

#ifdef UART1_ENABLED

extern UART_HandleTypeDef huart1;

uint8_t printf1(const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);

	uint8_t len = vprint(&huart1, fmt, argp);
	va_end(argp);

	return len;
}

#endif

#ifdef UART2_ENABLED

extern UART_HandleTypeDef huart2;

uint8_t printf2(const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);

	uint8_t len = vprint(&huart2, fmt, argp);
	va_end(argp);

	return len;
}

#endif


#ifdef UART3_ENABLED

extern UART_HandleTypeDef huart3;

uint8_t printf3(const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);

	uint8_t len = vprint(&huart3, fmt, argp);
	va_end(argp);

	return len;
}

#endif

#ifdef UART4_ENABLED

extern UART_HandleTypeDef huart4;

uint8_t printf4(const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);

	uint8_t len = vprint(&huart4, fmt, argp);
	va_end(argp);

	return len;
}

#endif

#ifdef UART5_ENABLED

extern UART_HandleTypeDef huart5;

uint8_t printf4(const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);

	uint8_t len = vprint(&huart5, fmt, argp);
	va_end(argp);

	return len;
}

#endif

#ifdef UART6_ENABLED

extern UART_HandleTypeDef huart6;

uint8_t printf6(const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);

	uint8_t len = vprint(&huart6, fmt, argp);
	va_end(argp);

	return len;
}

#endif


static uint8_t vprint(UART_HandleTypeDef *huart, const char *fmt, va_list argp)
{
	char str[50];

	uint8_t len = vsprintf(str, fmt, argp);

	if(0 < len) // build string
		HAL_UART_Transmit(huart, (uint8_t*) str, strlen(str), 0xFFFFFF); // send message via UART

	return len;
}
