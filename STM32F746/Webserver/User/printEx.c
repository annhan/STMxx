#include "printEx.h"

/**
 * Print
 */
void vprint(const char *fmt, va_list argp)
{
    char string[200];
    if(0 < vsprintf(string,fmt,argp)) // build string
    {
        HAL_UART_Transmit(&huart6, (uint8_t*)string, strlen(string), 100); // send message via UART HAL_UART_Transmit
    }
}
void my_printf(const char *fmt, ...) // custom printf() function
{
    va_list argp;
    va_start(argp, fmt); //lấy các tham số sau tham số fmt
    vprint(fmt, argp);
    va_end(argp);
}