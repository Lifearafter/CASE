#include "INA226_Driver.h"

static I2C_HandleTypeDef hi2c;

void I2C_Init(void)
{
    hi2c.Instance = I2Cx;
    hi2c.Init.ClockSpeed = 100000; // Adjust the clock speed as needed
    hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c.Init.OwnAddress1 = 0;
    hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c.Init.OwnAddress2 = 0;
    hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    I2Cx_CLK_ENABLE();
    I2Cx_GPIO_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = I2Cx_SCL_PIN | I2Cx_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = I2Cx_AF;
    HAL_GPIO_Init(I2Cx_GPIO_PORT, &GPIO_InitStruct);

    HAL_I2C_Init(&hi2c);
}

HAL_StatusTypeDef I2C_Write(uint8_t device_address, uint8_t register_address, uint8_t *data, uint16_t size)
{
    return HAL_I2C_Mem_Write(&hi2c, device_address, register_address, I2C_MEMADD_SIZE_8BIT, data, size, HAL_MAX_DELAY);
}

HAL_StatusTypeDef I2C_Read(uint8_t device_address, uint8_t register_address, uint8_t *data, uint16_t size)
{
    return HAL_I2C_Mem_Read(&hi2c, device_address, register_address, I2C_MEMADD_SIZE_8BIT, data, size, HAL_MAX_DELAY);
}
