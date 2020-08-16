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
    if (iIndex==0){ //Check cgi parameter : example GET /config.cgi?ip=2&gab=4 
        for (int i=0; i<iNumParams; i++){ 
            if (strcmp(pcParam[i] , "ip")==0){
                my_printf("new ip %s\r\n", pcValue[i]);
            }
            if (strcmp(pcParam[i] , "sub")==0){
                my_printf("new sub %s\r\n", pcValue[i]);
            }
            if (strcmp(pcParam[i] , "gaway")==0){
                my_printf("new ip %s\r\n", pcValue[i]);
            }
        }
    return "/2.shtml";
    }
 } // END [= CGI #5 =]
const tCGI LedCGI = { "/config.cgi", LedCGIhandler };
void myCGIinit(void) {
    theCGItable[0] = LedCGI;
    http_set_cgi_handlers(theCGItable, 1);
} 


