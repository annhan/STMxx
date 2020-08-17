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
#include "lwip/dns.h"
 #include "network_para.h"
#include "printEx.h"
#define WEBSERVER_THREAD_PRIO    ( tskIDLE_PRIORITY + 4 )
u32_t nPageHits = 0;
ip_addr_t ipHost;
ip_addr_t primaryDnsServer;
extern mySSIinit();
extern myCGIinit();
/*

((((x) & (u32_t)0x000000ffUL) << 24) | (((x) & (u32_t)0x0000ff00UL) << 8) | (((x) & (u32_t)0x00ff0000UL) >> 8) | (((x) & (u32_t)0xff000000UL) >> 24))
*/
void connectOK(const char *name, const ip_addr_t *ipaddr, void *callback_arg){
  ipHost = *ipaddr;
 // my_printf("Host Ip %s\r\n",ipaddr->addr);                                 
}
char Host[]="api.thingspeak.com";
static void http_server_netconn_thread(void *arg)
{  
 // struct netconn *conn, *newconn;
//  err_t err, accept_err;
dns_init();
  httpd_init();
  mySSIinit();
  myCGIinit();
  
  ip4_addr_set_u32(&primaryDnsServer, ipaddr_addr("8.8.8.8"));
  dns_setserver(0,&primaryDnsServer);
  dns_gethostbyname(Host,&ipHost,connectOK,NULL);
  while(1) {


  }
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

