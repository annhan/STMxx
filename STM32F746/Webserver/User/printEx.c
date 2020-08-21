#include "printEx.h"
#include "freertos_var.h"
/**
 * Print
 */
constexpr uint32_t PROTOCOL_SERVER_TIMEOUT_MS = 10;
void vprint(const char *fmt, va_list argp)
{
    char string[200];
    if(0 < vsprintf(string,fmt,argp)) // build string
    {
        HAL_UART_Transmit(&huart6, (uint8_t*)string, strlen(string), 100); // send message via UART HAL_UART_Transmit
    }
}
void my_printf(const char *fmt, ...) // custom printf() function
{  if (osMutexWait(osMu_Printhandle, PROTOCOL_SERVER_TIMEOUT_MS) != osOK)
    return ;
        va_list argp;
        va_start(argp, fmt); //lấy các tham số sau tham số fmt
        vprint(fmt, argp);
        va_end(argp);
    osMutexRelease(osMu_Printhandle);
}