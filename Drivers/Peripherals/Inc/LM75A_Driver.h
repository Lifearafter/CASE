#ifndef __LM75A_DRIVER_H
#define __LM75A_DRIVER_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"
#include "gpio_mapping.h"
#include "error_handler.h"
#include "COM_Driver.h"

#define timeout 325

#define LM75_TEMP_REG 0x00  // Temperature Register
#define LM75_CONF_REG 0x01  // Configuration Register
#define LM75_THYST_REG 0x02 // Temperature Hysteresis Register
#define LMS75_TOS_REG 0x03  // Over-temp Shutdown threshold Register
#define LM75_INFO_REG 0x07  // Information Register

#define LM75A_ADDRESS 0x48 << 1 // LM75A address

struct I2C_Module
{
    I2C_HandleTypeDef instance;
    uint16_t sdaPin;
    GPIO_TypeDef *sdaPort;
    uint16_t sclPin;
    GPIO_TypeDef *sclPort;
};

// Function prototypes
void LM75_Init(void);
HAL_StatusTypeDef LM75_ReadReg(uint8_t register_address, uint8_t *data, uint16_t size);
HAL_StatusTypeDef LM75_WriteReg(uint8_t register_address, uint8_t *data, uint16_t size);

// void I2C_ClearBusyFlagErratum(struct I2C_Module *i2c);

#endif