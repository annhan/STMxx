// low level routines for programming flash memory.  Interrupts should be disabled when doing any of this.
#include <stdint.h>
#include "nvm.h"
#include "printEx.h"
#define BIT0 (1 << 0)
#define BIT1 (1 << 1)
#define BIT2 (1 << 2)
#define BIT3 (1 << 3)
#define BIT4 (1 << 4)
#define BIT5 (1 << 5)
#define BIT6 (1 << 6)
#define BIT7 (1 << 7)
#define BIT8 (1 << 8)
#define BIT9 (1 << 9)
#define BIT10 (1 << 10)
#define BIT11 (1 << 11)
#define BIT12 (1 << 12)
#define BIT13 (1 << 13)
#define BIT14 (1 << 14)
#define BIT15 (1 << 15)
#define BIT16 (1 << 16)
#define BIT17 (1 << 17)
#define BIT18 (1 << 18)
#define BIT19 (1 << 19)
#define BIT20 (1 << 20)
#define BIT21 (1 << 21)
#define BIT22 (1 << 22)
#define BIT23 (1 << 23)
#define BIT24 (1 << 24)
#define BIT25 (1 << 25)
#define BIT26 (1 << 26)
#define BIT27 (1 << 27)
#define BIT28 (1 << 28)
#define BIT29 (1 << 29)
#define BIT30 (1 << 30)
#define BIT31 (1 << 31)
int  writeSector(uint32_t Address,void * values, uint16_t size) //môi sextor của Blue Pill là 1Kbyte
{   
    eraseSector(Address);   // clean     
    uint16_t *AddressPtr;
    uint16_t *valuePtr;
    AddressPtr = (uint16_t *)Address;
    valuePtr=(uint16_t *)values;
    size = size / 2;  // incoming value is expressed in bytes, not 16 bit words
    while(size) {        
        // unlock the flash 
        // Key 1 : 0x45670123
        // Key 2 : 0xCDEF89AB
        FLASH->KEYR = 0x45670123;
        FLASH->KEYR = 0xCDEF89AB;
        FLASH->CR &= ~BIT1; // ensure PER is low
        FLASH->CR |= BIT0;  // set the PG bit        
        *(AddressPtr) = *(valuePtr);
        while(FLASH->SR & BIT0); // wait while busy
        if (FLASH->SR & BIT2)
            return -1; // flash not erased to begin with
        if (FLASH->SR & BIT4)
            return -2; // write protect error
        AddressPtr++;
        valuePtr++;
        size--;
    }    
    return 0;    
}
void eraseSector(uint32_t SectorStartAddress)
{
    FLASH->KEYR = 0x45670123;
    FLASH->KEYR = 0xCDEF89AB;
    FLASH->CR &= ~BIT0;  // Ensure PG bit is low
    FLASH->CR |= BIT1; // set the PER bit
    FLASH->AR = SectorStartAddress;
    FLASH->CR |= BIT6; // set the start bit 
    while(FLASH->SR & BIT0); // wait while busy
}
void readSector(uint32_t SectorStartAddress, void * values, uint16_t size)
{   
    uint16_t *AddressPtr;
    uint16_t *valuePtr;
    AddressPtr = (uint16_t *)SectorStartAddress;
    valuePtr=(uint16_t *)values;
    size = size/2; // incoming value is expressed in bytes, not 16 bit words
    while(size)
    {
        *(valuePtr)=*(AddressPtr); 
        //*((uint16_t *)valuePtr)=*((uint16_t *)AddressPtr); // Cái nào cũng được
        valuePtr++;
        AddressPtr++;
        size--;
    }
}