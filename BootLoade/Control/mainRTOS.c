#include "mainRTOS.h"
#include "FreeRTOS.h"
#include "stm32f1xx_hal.h"
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
  .stack_size = 128 * 4
};
/**
 * Main
*/
void mainRTOS(){
    /*osThreadDef(BlinkLoop, osPriorityNormal, 0, 128 * 4);
    osThreadDef(DataLoop,osPriorityNormal, 0, 128 * 4);
    BlinkID = osThreadCreate(osThread(BlinkLoop), this);
    SendDataID = osThreadCreate(osThread(DataLoop), this);*/
    BlinkID = osThreadNew(BlinkLoop, NULL, &BlinkTask_attributes);
    SendDataID = osThreadNew(DataLoop, NULL, &SendDataTask_attributes);
}
void BlinkLoop(void * argument){
    for(;;){
        HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
        osDelay(2000);
    }
}
void DataLoop(void * argument){
  uint16_t tam = 0;
    for(;;){
      tam ++ ;
      HAL_UART_Transmit(&huart1,&tam,1,100);
      osDelay(100);
    }
}