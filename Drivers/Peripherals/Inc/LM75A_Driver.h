#ifndef __LM75A_DRIVER_H
#define __LM75A_DRIVER_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"
#include "gpio_mapping.h"
#include "error_handler.h"



#define LM75A_ADDRESS 0x48 // Replace with the appropriate device address
#define LM75A_TEMP_REG 0x00 
#define LM75A_CONF_REG 0x01


// Function prototypes
void I2C_Init(void);
HAL_StatusTypeDef I2C_Write(uint8_t device_address, uint8_t register_address, uint8_t *data, uint16_t size);
HAL_StatusTypeDef I2C_Read(uint8_t device_address, uint8_t register_address, uint8_t *data, uint16_t size);

#endif