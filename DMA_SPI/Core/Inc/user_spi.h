#ifndef __USERSPI_H
#define __USERSPI_H
#include "stm32f1xx_hal.h"
#include "stdint.h"

typedef struct SPIConf {
    SPI_HandleTypeDef* spi;
    uint16_t ssPin1;
    uint16_t ssPin2;
    uint16_t spiSendDevice1[1];
    uint16_t spiGetDevice1[1];
    uint16_t spiSendDevice2[1];
    uint16_t spiGetDevice2[1];
}SPIConf;

void user_spi_init(SPIConf* self,SPI_HandleTypeDef* spi);
SPIConf* user_spi_creat(SPI_HandleTypeDef* spi);
void user_spi_delete(SPIConf* self);
void user_init_ss_pin(SPIConf* self);
void spi_callback(SPIConf* self);
void spi_device1_cb(SPIConf* self);
void spi_device2_cb(SPIConf* self);
void spi_user_send_data(SPIConf* self);
#endif