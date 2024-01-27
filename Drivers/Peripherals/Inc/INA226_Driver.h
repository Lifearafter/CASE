#ifndef __INA226_DRIVER_H
#define __INA226_DRIVER_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"
#include "gpio_mapping.h"
#include "error_handler.h"

// #define I2Cx I2C1 // Replace with the appropriate I2C peripheral
// #define I2Cx_CLK_ENABLE() __HAL_RCC_I2C1_CLK_ENABLE()
// #define I2Cx_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE() // Replace with the appropriate GPIO port
// #define I2Cx_SCL_PIN GPIO_PIN_6                             // Replace with the appropriate SCL pin
// #define I2Cx_SDA_PIN GPIO_PIN_9                             // Replace with the appropriate SDA pin
// #define I2Cx_GPIO_PORT GPIOB                                // Replace with the appropriate GPIO port
// #define I2Cx_AF GPIO_AF4_I2C1

// INA225 Address
#define INA226_ADDRESS 0x44 // A0 is connected to GND, A1 is connected to VS+ (5V)

// INA226 registers
#define INA226_REG_CONFIG 0x00
#define INA226_REG_SHUNTVOLTAGE 0x01
#define INA226_REG_BUSVOLTAGE 0x02
#define INA226_REG_POWER 0x03
#define INA226_REG_CURRENT 0x04
#define INA226_REG_CALIBRATION 0x05
#define INA226_REG_MASKENABLE 0x06
#define INA226_REG_ALERTLIMIT 0x07
#define INA226_REG_MANUFACTURERID 0xFE
#define INA226_REG_DIEID 0xFF

// INA226 configuration register bits
#define INA226_CONFIG_RESET 0x8000
#define INA226_CONFIG_MASK_ENABLE 0x4000
#define INA226_CONFIG_ALERT_POLARITY 0x2000
#define INA226_CONFIG_ALERT_LATCH 0x1000
#define INA226_CONFIG_ALERT_QUEUE_1 0x0000
#define INA226_CONFIG_ALERT_QUEUE_2 0x0400
#define INA226_CONFIG_ALERT_QUEUE_4 0x0800
#define INA226_CONFIG_ALERT_QUEUE_8 0x0C00
#define INA226_CONFIG_AVG_1 0x0000
#define INA226_CONFIG_AVG_4 0x0200
#define INA226_CONFIG_AVG_16 0x0400
#define INA226_CONFIG_AVG_64 0x0600
#define INA226_CONFIG_AVG_128 0x0800
#define INA226_CONFIG_AVG_256 0x0A00
#define INA226_CONFIG_AVG_512 0x0C00
#define INA226_CONFIG_AVG_1024 0x0E00
#define INA226_CONFIG_VBUSCT_140US 0x0000
#define INA226_CONFIG_VBUSCT_204US 0x0040
#define INA226_CONFIG_VBUSCT_332US 0x0080
#define INA226_CONFIG_VBUSCT_588US 0x00C0
#define INA226_CONFIG_VBUSCT_1100US 0x0100
#define INA226_CONFIG_VBUSCT_2116US 0x0140
#define INA226_CONFIG_VBUSCT_4156US 0x0180
#define INA226_CONFIG_VBUSCT_8244US 0x01C0
#define INA226_CONFIG_VSHCT_140US 0x0000
#define INA226_CONFIG_VSHCT_204US 0x0008
#define INA226_CONFIG_VSHCT_332US 0x0010
#define INA226_CONFIG_VSHCT_588US 0x0018
#define INA226_CONFIG_VSHCT_1100US 0x0020
#define INA226_CONFIG_VSHCT_2116US 0x0028
#define INA226_CONFIG_VSHCT_4156US 0x0030
#define INA226_CONFIG_VSHCT_8244US 0x0038
#define INA226_CONFIG_MODE_POWERDOWN 0x0000
#define INA226_CONFIG_MODE_SHUNT_TRIG 0x0001
#define INA226_CONFIG_MODE_BUS_TRIG 0x0002
#define INA226_CONFIG_MODE_SHUNT_BUS_TRIG 0x0003
#define INA226_CONFIG_MODE_ADC_OFF 0x0004
#define INA226_CONFIG_MODE_SHUNT_CONT 0x0005
#define INA226_CONFIG_MODE_BUS_CONT 0x0006
#define INA226_CONFIG_MODE_SHUNT_BUS_CONT 0x0007

// Function prototypes
void I2C_Init(void);
HAL_StatusTypeDef I2C_Write(uint8_t device_address, uint8_t register_address, uint8_t *data, uint16_t size);
HAL_StatusTypeDef I2C_Read(uint8_t device_address, uint8_t register_address, uint8_t *data, uint16_t size);

#endif