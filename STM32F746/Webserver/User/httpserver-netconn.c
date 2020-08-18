#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
//#include "fs.h"
#include "lwip/apps/fs.h"
#include "string.h"
#include <stdio.h>
#include "httpserver-netconn.h"
#include "cmsis_os.h"
#include "stm32f7xx.h"                  

#define WEBSERVER_THREAD_PRIO    ( tskIDLE_PRIORITY + 4 )
u32_t nPageHits = 0;

extern mySSIinit();
extern myCGIinit();


static void http_server_netconn_thread(void *arg)
{  

  httpd_init();
  mySSIinit();
  myCGIinit();
  
  while(1) {}
}

/**
  * @brief  Initialize the HTTP server (start its thread) 
  * @param  none
  * @retval None
  */
void http_server_netconn_init()
{
  sys_thread_new("HTTP", http_server_netconn_thread, NULL, DEFAULT_THREAD_STACKSIZE, WEBSERVER_THREAD_PRIO);
}

