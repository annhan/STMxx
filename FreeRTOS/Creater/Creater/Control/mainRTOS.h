#ifndef __RTOS_MAIN_H
#define __RTOS_MAIN_H

// OS includes

#include <cmsis_os.h>
#include <main.h>


void BlinkLoop(void *argument);
void DataLoop(void *argument);
void mainRTOS();
#endif