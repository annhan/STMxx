#ifndef __NVM_H
#define __NVM_H
#include "stm32f7xx_hal.h"
#include "stdint.h"
#include "string.h"
//F746 1024Kb Flash -> 0x0800000 to 0x08100000
int writeSector(uint32_t Address,void * valuePtr, uint16_t Count);
void eraseSector(uint32_t SectorStartAddress);
void readSector(uint32_t SectorStartAddress, void * valuePtr, uint16_t Count);
#endif