#ifndef __LM75A_DRIVER_H
#define __LM75A_DRIVER_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"
#include "gpio_mapping.h"

#define I2Cx I2C1 // Replace with the appropriate I2C peripheral
#define I2Cx_CLK_ENABLE() __HAL_RCC_I2C1_CLK_ENABLE()
#define I2Cx_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE() // Replace with the appropriate GPIO port
#define I2Cx_SCL_PIN GPIO_PIN_6                             // Replace with the appropriate SCL pin
#define I2Cx_SDA_PIN GPIO_PIN_9                             // Replace with the appropriate SDA pin
#define I2Cx_GPIO_PORT GPIOB                                // Replace with the appropriate GPIO port
#define I2Cx_AF GPIO_AF4_I2C1                               // Replace with the appropriate alternate function

// Function prototypes
void I2C_Init(void);
HAL_StatusTypeDef I2C_Write(uint8_t device_address, uint8_t register_address, uint8_t *data, uint16_t size);
HAL_StatusTypeDef I2C_Read(uint8_t device_address, uint8_t register_address, uint8_t *data, uint16_t size);

#endif