#include "user_spi.h"
#include <stdlib.h>
#define SS2_Pin GPIO_PIN_0
#define SS2_GPIO_Port GPIOB
#define SS1_Pin GPIO_PIN_1
#define SS1_GPIO_Port GPIOB


void user_init_ss_pin(SPIConf* self)
{ 
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  HAL_GPIO_DeInit(GPIOB, self->ssPin2);
  HAL_GPIO_DeInit(GPIOB, self->ssPin1);
  HAL_GPIO_WritePin(GPIOB, self->ssPin1|self->ssPin2, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = self->ssPin1|self->ssPin2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
 
}
void user_spi_init(SPIConf* self,SPI_HandleTypeDef* spihandle){
    self->spi = spihandle ; 
    self->spi->Instance = SPI1;
    self->spi->Init.Mode = SPI_MODE_MASTER;
    self->spi->Init.Direction = SPI_DIRECTION_2LINES;
    self->spi->Init.DataSize = SPI_DATASIZE_16BIT;
    self->spi->Init.CLKPolarity = SPI_POLARITY_LOW;
    self->spi->Init.CLKPhase = SPI_PHASE_2EDGE;
    self->spi->Init.NSS = SPI_NSS_SOFT;
    self->spi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
    self->spi->Init.FirstBit = SPI_FIRSTBIT_MSB;
    self->spi->Init.TIMode = SPI_TIMODE_DISABLE;
    self->spi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    self->spi->Init.CRCPolynomial = 10;
    HAL_SPI_DeInit(self->spi);
    HAL_SPI_Init(self->spi);
    self->spiSendDevice1[0] = 0xFFFF;
    self->spiGetDevice1[0] = 0xFFFF;
    self->spiSendDevice2[0] = 0xFFFF;
    self->spiGetDevice2[0] = 0xFFFF;
    self->ssPin1 = SS1_Pin;
    self->ssPin2 = SS2_Pin;
    
}
SPIConf* user_spi_creat(SPI_HandleTypeDef* spi){
   SPIConf* result = (SPIConf*)malloc(sizeof(SPIConf));
   user_spi_init(result,spi);
   user_init_ss_pin(result);
   return result;
}

void user_spi_delete(SPIConf* self) {
  if (self) {
     free(self);
  }
}
void spi_callback(SPIConf* self)
{   
    if(self->spi->pRxBuffPtr == (uint8_t*)self->spiGetDevice1)
        spi_device1_cb(self);
    else if (self->spi->pRxBuffPtr == (uint8_t*)self->spiGetDevice2)
        spi_device2_cb(self);
}

//Ngat nhan SPI cua device 1
void spi_device1_cb(SPIConf* self){
  HAL_GPIO_WritePin(SS1_GPIO_Port, self->ssPin1, GPIO_PIN_SET);
  uint16_t dataGet = self->spiGetDevice1[0];
}

//Ngat nhan SPI cua device 
void spi_device2_cb(SPIConf* self){
  HAL_GPIO_WritePin(SS2_GPIO_Port, self->ssPin2, GPIO_PIN_SET);
  uint16_t dataGet = self->spiGetDevice2[0];
}
void spi_user_send_data(SPIConf* self){
    if (self->spi->pTxBuffPtr == (uint8_t*)self->spiSendDevice2) { //check nê�?u lần trươ�?c send device1 thì lần này send device2
      HAL_GPIO_WritePin(SS1_GPIO_Port,self->ssPin1,GPIO_PIN_RESET);
      HAL_SPI_TransmitReceive_DMA(self->spi,(uint8_t*)self->spiSendDevice1,(uint8_t*)self->spiGetDevice1,1); //(uint8_t*)
    }
    else {
      HAL_GPIO_WritePin(SS2_GPIO_Port,self->ssPin2,GPIO_PIN_RESET);
      HAL_SPI_TransmitReceive_DMA(self->spi,(uint8_t*)self->spiSendDevice2,(uint8_t*)self->spiGetDevice2,1); //(uint8_t*)
    }
}