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
#include "nvm.h"
 extern ip_addr_t ipHost;
 // [* SSI #2 *]
#define numSSItags 7

 // [* SSI #3 *]
char const *theSSItags[numSSItags] = { "ip", "sub","Gaway","sMQ" ,"pMQ","uMQ","paMQ" };


u16_t mySSIHandler(int iIndex, char *pcInsert, int iInsertLen) {
    my_printf("ssi Get %s\r\n",pcInsert);
    char myStr1[50];
   if (iIndex == 0) {
      sprintf(myStr1, "%d.%d.%d.%d", net_para.IP_ADDRESS[0], \
                                    net_para.IP_ADDRESS[1],  \
                                    net_para.IP_ADDRESS[2], \
                                    net_para.IP_ADDRESS[3]);
      /*sprintf(myStr1, "%i.%i.%i.%i",  (uint8_t)(((ipHost.addr) & (u32_t)0x000000ffUL)) ,\
                                      (uint8_t)(((ipHost.addr) & (u32_t)0x0000ff00UL) >>8) , \
                                      (uint8_t)(((ipHost.addr) & (u32_t)0x00ff0000UL) >> 16) , \
                                      (uint8_t)(((ipHost.addr) & (u32_t)0xff000000UL) >> 24));*/

      strcpy(pcInsert, myStr1);
      return strlen(myStr1);
    }
    else if (iIndex == 1){
      sprintf(myStr1, "%d.%d.%d.%d", net_para.NETMASK_ADDRESS[0], \
                                    net_para.NETMASK_ADDRESS[1],  \
                                    net_para.NETMASK_ADDRESS[2], \
                                    net_para.NETMASK_ADDRESS[3]);
      strcpy(pcInsert, myStr1);
      return strlen(myStr1);
    }
    else if (iIndex == 2){
      sprintf(myStr1, "%d.%d.%d.%d", net_para.GATEWAY_ADDRESS[0], \
                                    net_para.GATEWAY_ADDRESS[1],  \
                                    net_para.GATEWAY_ADDRESS[2], \
                                    net_para.GATEWAY_ADDRESS[3]);
      strcpy(pcInsert, myStr1);
      return strlen(myStr1);
    }
    else if (iIndex == 3){  //sMQ
      //sprintf(myStr1, "%s", net_para.serverMQTT);
      strcpy(pcInsert, &net_para.serverMQTT);
      return strlen(net_para.serverMQTT);
    }
    else if (iIndex == 4){ //pMQ
      sprintf(myStr1, "%d", net_para.mqttPort);
      strcpy(pcInsert, myStr1);
      return strlen(myStr1);
    }
    else if (iIndex == 5){ //uMQ
     // sprintf(myStr1, "%s", net_para.mqttUser);
      strcpy(pcInsert, &net_para.mqttUser);
      return strlen(net_para.mqttUser);
    }
    else if (iIndex == 6){ //pMQ
      sprintf(myStr1, "%s", net_para.mqttPass);
      strcpy(pcInsert, &net_para.mqttPass);
      return strlen(myStr1);
    }
    return 0;

}
void mySSIinit(void) {
   http_set_ssi_handler(mySSIHandler, (char const**) theSSItags,numSSItags);
}


// in our SHTML file <form method="get" action="/leds.cgi"> [= CGI #3 =]

                    
tCGI theCGItable[2];
void IP_PARSER(char* buf,uint16_t* Value)
{
	char* saveptr=NULL;
	char payload[15]="";
	memcpy(payload,&buf[0],15);
    Value[0]=(uint8_t)atoi(strtok_r(payload,".",&saveptr));
    Value[1]=(uint8_t)atoi(strtok_r(NULL,".",&saveptr));
    Value[2]=(uint8_t)atoi(strtok_r(NULL,".",&saveptr));
    Value[3]=(uint8_t)atoi(strtok_r(NULL,".",&saveptr));
}
// [= CGI #4 =]
const char* NetCGIhandler(int iIndex, int iNumParams, char *pcParam[],char *pcValue[]) {
    if (iIndex==0){ //Check cgi parameter : example GET /config.cgi?ip=2&gab=4 
        for (int i=0; i<iNumParams; i++){ 
            my_printf("NetCGIhandler %s\r\n", pcValue[i]);
            if (strcmp(pcParam[i] , "ip")==0){
                my_printf("new ip %s\r\n", pcValue[i]);
                IP_PARSER(pcValue[i],net_para.IP_ADDRESS);
            }
            if (strcmp(pcParam[i] , "sub")==0){
                my_printf("new sub %s\r\n", pcValue[i]);
                IP_PARSER(pcValue[i],net_para.NETMASK_ADDRESS);
            }
            if (strcmp(pcParam[i] , "gaway")==0){
                my_printf("new ip %s\r\n", pcValue[i]);
                IP_PARSER(pcValue[i],net_para.GATEWAY_ADDRESS);
            }
        }
    }
    
    flash_write(0x8000100,&net_para,sizeof(net_para));
    return "/index.shtml";
    
}

const char* MqttCGIhandler(int iIndex, int iNumParams, char *pcParam[],char *pcValue[]) {
    if (iIndex==1){ //Check cgi parameter : example GET /config.cgi?ip=2&gab=4 
        for (int i=0; i<iNumParams; i++){ 
            if (strcmp(pcParam[i] , "s")==0){
                strcpy(net_para.serverMQTT, pcValue[i]);
            }
            if (strcmp(pcParam[i] , "p")==0){
                net_para.mqttPort = (uint16_t)atoi(pcValue[i]);
                //my_printf("new sub %s\r\n", pcValue[i]);
            }
            if (strcmp(pcParam[i] , "u")==0){
                strcpy(net_para.mqttUser, pcValue[i]);
                
            }
            if (strcmp(pcParam[i] , "pa")==0){
                strcpy(net_para.mqttPass, pcValue[i]);
            }
        }
        flash_write(0x8000100,&net_para,sizeof(net_para));
    }

    return "/index.shtml";
} 
const tCGI networkCGI = { "/config.cgi", NetCGIhandler };
const tCGI mqttCGI = { "/configmqtt.cgi", MqttCGIhandler };
void myCGIinit(void) {
    theCGItable[0] = networkCGI;
    theCGItable[1] = mqttCGI;
    http_set_cgi_handlers(theCGItable, 2);
} 


