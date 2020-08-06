#ifndef __printEx_H
#define __printEx_H
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "stm32f1xx_hal.h"
extern UART_HandleTypeDef huart1;
void vprint(const char *fmt, va_list argp);
void my_printf(const char *fmt, ...) ;
#endif