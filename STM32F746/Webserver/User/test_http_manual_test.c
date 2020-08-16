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
/**
  * @brief serve tcp connection  
  * @param conn: pointer on connection structure 
  * @retval None
  */
void http_server_serve(struct netconn *conn) 
{
  struct netbuf *inbuf;
  err_t recv_err;
  char* buf;
  u16_t buflen;
  struct fs_file file;
  
  /* Read the data from the port, blocking if nothing yet there. 
   We assume the request (the part we care about) is in one netbuf */
  recv_err = netconn_recv(conn, &inbuf);
  
  if (recv_err == ERR_OK)
  {
    if (netconn_err(conn) == ERR_OK) 
    {
      netbuf_data(inbuf, (void**)&buf, &buflen);
      /* Is this an HTTP GET command? (only check the first 5 chars, since
      there are other formats for GET, and we're keeping it very simple )*/
       if ((buflen >=5) && (strncmp(buf, "GET /", 5) == 0)){
          if ((buflen >=5) && (strncmp(buf, "GET / HTTP", 10) == 0))
          {   
            fs_open(&file, "/1.html");
            netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
            fs_close(&file);
          }  
        if ((buflen >=5) && (strncmp(buf, "GET /ssi", 8) == 0))
          {   
            fs_open(&file, "/2.shtml");
            netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
            fs_close(&file);
          }     
       }
    }
  }
  /* Close the connection (server closes in HTTP) */
  netconn_close(conn);
  
  /* Delete the buffer (netconn_recv gives us ownership,
   so we have to make sure to deallocate the buffer) */
  netbuf_delete(inbuf);
}
}


/**
  * @brief  http server thread 
  * @param arg: pointer on argument(not used here) 
  * @retval None
  */
static void http_server_netconn_thread(void *arg)
{  
  struct netconn *conn, *newconn;
  err_t err, accept_err;

  /* Create a new TCP connection handle */
  conn = netconn_new(NETCONN_TCP);
  
  if (conn!= NULL)
  {
    
    err = netconn_bind(conn, NULL, 80);
    
    if (err == ERR_OK)
    {
  
      netconn_listen(conn);
  
      while(1) 
      {
       
        accept_err = netconn_accept(conn, &newconn);
        if(accept_err == ERR_OK)
        {
        
          http_server_serve(newconn);

        
          netconn_delete(newconn);
        }
      }
    }
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

/**
  * @brief  Create and send a dynamic Web Page. This page contains the list of 
  *         running tasks and the number of page hits. 
  * @param  conn pointer on connection structure 
  * @retval None
  */
