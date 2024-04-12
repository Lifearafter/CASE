#ifndef __ADXL345_DRIVER_H
#define __ADXL345_DRIVER_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"
#include "gpio_mapping.h"
#include "error_handler.h"
#include "COM_Driver.h"

#define ADXL345_ADDRESS 0x53 << 1 // ADXL345 address

#define ADXL345_REG_DEVID 0x00
#define ADXL345_REG_THRESH_TAP 0x1D
#define ADXL345_REG_OFSX 0x1E
#define ADXL345_REG_OFSY 0x1F
#define ADXL345_REG_OFSZ 0x20
#define ADXL345_REG_DUR 0x21
#define ADXL345_REG_LATENT 0x22
#define ADXL345_REG_WINDOW 0x23
#define ADXL345_REG_THRESH_ACT 0x24
#define ADXL345_REG_THRESH_INACT 0x25
#define ADXL345_REG_TIME_INACT 0x26
#define ADXL345_REG_ACT_INACT_CTL 0x27
#define ADXL345_REG_THRESH_FF 0x28
#define ADXL345_REG_TIME_FF 0x29
#define ADXL345_REG_TAP_AXES 0x2A
#define ADXL345_REG_ACT_TAP_STATUS 0x2B
#define ADXL345_REG_BW_RATE 0x2C
#define ADXL345_REG_POWER_CTL 0x2D
#define ADXL345_REG_INT_ENABLE 0x2E
#define ADXL345_REG_INT_MAP 0x2F
#define ADXL345_REG_INT_SOURCE 0x30
#define ADXL345_REG_DATA_FORMAT 0x31
#define ADXL345_REG_DATAX0 0x32
#define ADXL345_REG_DATAX1 0x33
#define ADXL345_REG_DATAY0 0x34
#define ADXL345_REG_DATAY1 0x35
#define ADXL345_REG_DATAZ0 0x36
#define ADXL345_REG_DATAZ1 0x37

#define ADXL345_RANGE_2G 0x00
#define ADXL345_RANGE_4G 0x01
#define ADXL345_RANGE_8G 0x02
#define ADXL345_RANGE_16G 0x03

struct SPI_Module
{
    SPI_HandleTypeDef instance;
    uint16_t sckPin;
    GPIO_TypeDef *sckPort;
    uint16_t misoPin;
    GPIO_TypeDef *misoPort;
    uint16_t mosiPin;
    GPIO_TypeDef *mosiPort;
    uint16_t csPin;
    GPIO_TypeDef *csPort;
};

// Function prototypes
void ADXL345_Init(void);
HAL_StatusTypeDef ADXL345_ReadReg(uint8_t register_address, uint8_t *data, uint16_t size);
HAL_StatusTypeDef ADXL345_WriteReg(uint8_t register_address, uint8_t *data, uint16_t size);

HAL_StatusTypeDef ADXL345_Check(void);
void ADXL345_Config(void);
void ADXL345_SetRange(uint8_t range);
void ADXL345_ReadAccel(int16_t *x, int16_t *y, int16_t *z);

#endif