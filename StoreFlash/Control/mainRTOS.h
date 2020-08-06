#ifndef __RTOS_MAIN_H
#define __RTOS_MAIN_H

// OS includes

#include <cmsis_os.h>
#include <main.h>
#include <FreeRTOS_VarTest.h>

extern UART_HandleTypeDef huart1;
void BlinkLoop(void *argument);
void DataLoop(void *argument);
void mainRTOS();
#endif