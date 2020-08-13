// low level routines for programming flash memory.  Interrupts should be disabled when doing any of this.
#include <stdint.h>
#include "nvm.h"
#include "printEx.h"

void readSector(uint32_t SectorStartAddress, void * values, uint16_t size)
{   
    uint16_t *AddressPtr;
    uint16_t *valuePtr;
    AddressPtr = (uint16_t *)SectorStartAddress;
    valuePtr=(uint16_t *)values;
    size = size/2; 
    while(size)
    {
        *(valuePtr)=*(AddressPtr); 
        valuePtr++;
        AddressPtr++;
        size--;
    }
}
void flash_erase()
{

  uint32_t SECTORError = 0;
  FLASH_EraseInitTypeDef EraseInitStruct;
  EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
  EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
  EraseInitStruct.Sector        = 0;
  EraseInitStruct.NbSectors     = 1;
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR |
                FLASH_FLAG_WRPERR );
 if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
  { return;
  }
}

uint8_t flash_write(uint32_t address, void *data, uint16_t size)
{   HAL_FLASH_Unlock();
    flash_erase();
    HAL_FLASH_Lock();
    HAL_FLASH_Unlock();
    uint16_t *valuePtr;
    uint16_t *AddressPtr;
    valuePtr=(uint16_t *)data;
    AddressPtr = (uint16_t *)address;
    size = size/2; // incoming value is expressed in bytes, not 16 bit words
    for (int i = 0; i < size/2; i++){
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (address)+(i*2), valuePtr[i]) ;
    }
    HAL_FLASH_Lock();
    return 0;
}