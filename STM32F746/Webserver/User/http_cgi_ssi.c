#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "string.h"
#include <stdio.h>
#include <Stdbool.h> //need for ssi
#include "lwip/apps/httpd.h"
 #include "lwip.h"
 #include "printEx.h"
 #include "network_para.h"
 // [* SSI #2 *]
#define numSSItags 3

                    // [* SSI #3 *]
char const *theSSItags[numSSItags] = { "ip", "sub","Gaway" };


u16_t mySSIHandler(int iIndex, char *pcInsert, int iInsertLen) {
    my_printf("ssi Get %s\r\n",pcInsert);
    //char myStr1[]=NULL;
    char myStr1[50];
   if (iIndex == 0) {
      sprintf(myStr1, "%d.%d.%d.%d", net_parameter.IP_ADDRESS[0], \
                                    net_parameter.IP_ADDRESS[1],  \
                                    net_parameter.IP_ADDRESS[2], \
                                    net_parameter.IP_ADDRESS[3]);
      strcpy(pcInsert, myStr1);
      return strlen(myStr1);
    }
    else if (iIndex == 1){
      sprintf(myStr1, "%d.%d.%d.%d", net_parameter.NETMASK_ADDRESS[0], \
                                    net_parameter.NETMASK_ADDRESS[1],  \
                                    net_parameter.NETMASK_ADDRESS[2], \
                                    net_parameter.NETMASK_ADDRESS[3]);
      strcpy(pcInsert, myStr1);
      return strlen(myStr1);
    }
    else if (iIndex == 2){
      sprintf(myStr1, "%d.%d.%d.%d", net_parameter.GATEWAY_ADDRESS[0], \
                                    net_parameter.GATEWAY_ADDRESS[1],  \
                                    net_parameter.GATEWAY_ADDRESS[2], \
                                    net_parameter.GATEWAY_ADDRESS[3]);
      strcpy(pcInsert, myStr1);
      return strlen(myStr1);
    }
    return 0;

}
void mySSIinit(void) {
   http_set_ssi_handler(mySSIHandler, (char const**) theSSItags,numSSItags);
}


// in our SHTML file <form method="get" action="/leds.cgi"> [= CGI #3 =]

                    // [= CGI #4 =]
tCGI theCGItable[1];

const char* LedCGIhandler(int iIndex, int iNumParams, char *pcParam[],char *pcValue[]) {
    return "/2.shtml";
 } // END [= CGI #5 =]
const tCGI LedCGI = { "/config.cgi", LedCGIhandler };
void myCGIinit(void) {
    theCGItable[0] = LedCGI;
    http_set_cgi_handlers(theCGItable, 1);
} 


/*
const char * LEDS_CGI_Handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
  uint32_t i=0;
  
   We have only one SSI handler iIndex = 0 
  if (iIndex==0)
  {
    // All leds off 
    BSP_LED_Off(LED1);
    BSP_LED_Off(LED2);
    BSP_LED_Off(LED3);
    BSP_LED_Off(LED4);
    
    // Check cgi parameter : example GET /leds.cgi?led=2&led=4 
    for (i=0; i<iNumParams; i++)
    {
      // check parameter "led" 
      if (strcmp(pcParam[i] , "led")==0)   
      {
        // switch led1 ON if 1 
        if(strcmp(pcValue[i], "1") ==0) 
          BSP_LED_On(LED1);
          
        // switch led2 ON if 2 
        else if(strcmp(pcValue[i], "2") ==0) 
          BSP_LED_On(LED2);
        
        // switch led3 ON if 3 
        else if(strcmp(pcValue[i], "3") ==0) 
          BSP_LED_On(LED3);
        
        // switch led4 ON if 4 
        else if(strcmp(pcValue[i], "4") ==0) 
          BSP_LED_On(LED4);
      }
    }
  }
  // uri to send after cgi call
  return "/STM32F4xxLED.html";  
}
*/