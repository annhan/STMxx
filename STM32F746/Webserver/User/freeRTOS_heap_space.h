#ifndef __USER_FREE_RTOS_H
#define __USER_FREE_RTOS_H
#include "stdint.h"
#include <Stdbool.h>
typedef struct {
    bool is_Ready;
    uint32_t uptime; // [ms]
    uint32_t min_heap_space; // FreeRTOS heap [Bytes]
    uint32_t min_stack_space_default; // minimum remaining space since startup [Bytes]
    uint32_t min_stack_space_usb;
    uint32_t stack_usage_default;
} SystemStats_t;

extern SystemStats_t SystemStats_;

#endif