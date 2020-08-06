#include "mainRTOS.h"
#include "FreeRTOS.h"
#include "stm32f1xx_hal.h"
#include "nvm.h"
#include "printEx.h"
/**
 * Khai bao Task 
*/
osThreadId_t BlinkID;
const osThreadAttr_t BlinkTask_attributes = {
  .name = "Blink",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};

/**
 * Khai bao Task 
*/
osThreadId_t SendDataID;
const osThreadAttr_t SendDataTask_attributes = {
  .name = "SenData",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 4
};


typedef struct{
      char Parameter1; // 1 byte
      uint8_t Parameter2; // 1 byte
      uint16_t Parameter3; // 2 byte
      uint32_t Parameter4; // 4 byte
      uint32_t Parameter5; // 4 byte
} tpSettings;

tpSettings settings;

void tangdata(){
  osMutexWait(osMu_ExHandle,osWaitForever);
  settings.Parameter1++;
  settings.Parameter2=settings.Parameter2 + 2;
  settings.Parameter3++;
  settings.Parameter4=settings.Parameter4 + 3;
  osMutexRelease(osMu_ExHandle);
}
/**
 * main Thread
 */
void mainRTOS(){

    BlinkID = osThreadNew(BlinkLoop, NULL, &BlinkTask_attributes);
    SendDataID = osThreadNew(DataLoop, NULL, &SendDataTask_attributes);
}

void BlinkLoop(void * argument){
    for(;;){
        HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
        osDelay(1000);
    }
}

/**
 * main
 */
void DataLoop(void * argument){
    readSector(0x8007f00,&settings,sizeof(tpSettings));
    my_printf("Size %d\r\n", sizeof(tpSettings));
    tangdata();
    writeSector(0x8007f00,&settings,sizeof(tpSettings));
    for(;;){
      my_printf("Today's %s: %d-%d-%d\r\n", settings.Parameter1, settings.Parameter2, settings.Parameter3, settings.Parameter4);
      osDelay(1000);
    }
}