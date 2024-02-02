/*
 * print.h
 *
 *  Created on: Oct 7, 2019
 *      Author: Miradil Zeynalli
 */

#ifndef PRINT_H
#define PRINT_H

#include <stdint.h>

//#define UART1_ENABLED
#define UART2_ENABLED
//#define UART3_ENABLED
//#define UART4_ENABLED
//#define UART5_ENABLED
//#define UART6_ENABLED


#ifdef UART1_ENABLED
uint8_t printf1(const char *fmt, ...);
#endif

#ifdef UART2_ENABLED
uint8_t printf2(const char *fmt, ...);
#endif

#ifdef UART3_ENABLED
uint8_t printf3(const char *fmt, ...);
#endif

#ifdef UART4_ENABLED
uint8_t printf4(const char *fmt, ...);
#endif

#ifdef UART5_ENABLED
uint8_t printf5(const char *fmt, ...);
#endif

#ifdef UART6_ENABLED
uint8_t printf1(const char *fmt, ...);
#endif

#endif /* PRINT_H */
