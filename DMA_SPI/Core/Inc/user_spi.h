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
/**
 * init SPI
 */
void user_spi_init(SPIConf* self, SPI_HandleTypeDef* spi);
/**
 * ham khoi tao
 */
SPIConf* user_spi_creat(SPI_HandleTypeDef* spi);
/**
 * ham huy
 */
void user_spi_delete(SPIConf* self);
/**
 * ham khoi tao GPIO pin SS
 */
void user_init_ss_pin(SPIConf* self);
/**
 * SPI CALLback khi DMA nhận xong
 */
void spi_callback(SPIConf* self);
/**
 * Get data sensor 1
 */
void spi_device1_cb(SPIConf* self);
/**
 * Get data sensor 2
 */
void spi_device2_cb(SPIConf* self);

/**
 * ham send data tới lần lượt 2 cảm biến
 */
void spi_user_send_data(SPIConf* self);
#endif