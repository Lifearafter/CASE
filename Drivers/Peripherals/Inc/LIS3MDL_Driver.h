#ifndef LIS3MDL_DRIVER_H
#define LIS3MDL_DRIVER_H

#include "stm32f4xx_hal.h"

// Define SPI instance
struct SPI_Module
{
    SPI_HandleTypeDef instance;
    GPIO_TypeDef *csPort;
    uint16_t csPin;
};

void LIS3MDL_Init(void);
void LIS3MDL_Config(void);

HAL_StatusTypeDef LIS3MDL_Check(void);
HAL_StatusTypeDef LIS3MDL_ReadReg(uint8_t register_address, uint8_t *data, uint16_t size);
HAL_StatusTypeDef LIS3MDL_WriteReg(uint8_t register_address, uint8_t *data, uint16_t size);

void LIS3MDL_ReadMag(int16_t *x, int16_t *y, int16_t *z);

#endif /* LIS3MDL_DRIVER_H */
