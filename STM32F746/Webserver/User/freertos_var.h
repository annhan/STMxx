#ifndef __FREERTOS_H
#define __FREERTOS_H
#include "cmsis_os.h"

extern osMutexId_t osMu_Printhandle;


extern osThreadId_t defaultTaskHandle;
extern osThreadId_t lwip_set_link;
extern osThreadId_t task_mqtt;
extern osThreadId_t task_web_server;
#endif /* __FREERTOS_H */

/*
osThreadNew return osThreadId_t
*/