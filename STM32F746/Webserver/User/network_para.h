#ifndef __NET_PARA
#define __NET_PARA

#include "stdint.h"

typedef struct{
    uint16_t firstRun;
    uint16_t IP_ADDRESS[4];
    uint16_t NETMASK_ADDRESS[4];
    uint16_t GATEWAY_ADDRESS[4];
}Net_conf;

extern Net_conf net_parameter;

#endif