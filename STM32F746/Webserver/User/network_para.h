#ifndef __NET_PARA
#define __NET_PARA

#include "stdint.h"

typedef struct{
    uint16_t firstRun[2];
    uint16_t IP_ADDRESS[4];
    uint16_t NETMASK_ADDRESS[4];
    uint16_t GATEWAY_ADDRESS[4];
    char serverMQTT[32];
    uint16_t mqttPort;
    char mqttUser[32];
    char mqttPass[32];
}Net_conf;

extern Net_conf net_para;

#endif