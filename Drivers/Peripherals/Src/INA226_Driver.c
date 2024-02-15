#include "INA226_Driver.h"

static I2C_HandleTypeDef hi2c;

void INA226_Init(void)
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

HAL_StatusTypeDef readBusVoltage(uint16_t *busVoltage)
{
    uint8_t data[2];
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c, INA226_ADDRESS, INA260_REG_BUSVOLTAGE, I2C_MEMADD_SIZE_8BIT, data, 2, 100);
    if (status == HAL_OK)
    {
        *busVoltage = (data[0] << 8) | data[1];
    }
    return status;
}

HAL_StatusTypeDef readCurrent(uint16_t *current)
{
    uint8_t data[2];
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c, INA226_ADDRESS, INA260_REG_CURRENT, I2C_MEMADD_SIZE_8BIT, data, 2, 100);
    if (status == HAL_OK)
    {
        *current = (data[0] << 8) | data[1];
    }
    return status;
}

HAL_StatusTypeDef readPower(uint16_t *power)
{
    uint8_t data[2];
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c, INA226_ADDRESS, INA260_REG_POWER, I2C_MEMADD_SIZE_8BIT, data, 2, 100);
    if (status == HAL_OK)
    {
        *power = (data[0] << 8) | data[1];
    }
    return status;
}

HAL_StatusTypeDef writeRegister(uint8_t register_address, uint16_t data)
{
    uint8_t buffer[3];
    buffer[0] = register_address;
    buffer[1] = (data >> 8) & 0xFF;
    buffer[2] = data & 0xFF;
    return HAL_I2C_Master_Transmit(&hi2c, INA226_ADDRESS, buffer, 3, 100);
}

HAL_StatusTypeDef configReset(void)
{
    return writeRegister(INA260_REG_CONFIG, INA260_CONFIG_RESET);
}