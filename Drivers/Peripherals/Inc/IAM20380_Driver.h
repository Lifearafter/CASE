#ifndef IAM20380_DRIVER_H
#define IAM20380_DRIVER_H

#include "stm32f4xx_hal.h"

// Define SPI instance
struct SPI_Module {
    SPI_HandleTypeDef instance;
    GPIO_TypeDef *csPort;
    uint16_t csPin;
};

void IAM20380_Init(void);
HAL_StatusTypeDef IAM20380_ReadReg(uint8_t register_address, uint8_t *data, uint16_t size);
HAL_StatusTypeDef IAM20380_WriteReg(uint8_t register_address, uint8_t *data, uint16_t size);
void IAM20380_Config(void);
HAL_StatusTypeDef IAM20380_Check(void);
void IAM20380_ReadGyro(int16_t *x, int16_t *y, int16_t *z);

#endif /* IAM20380_DRIVER_H */