#include "INA226_Driver.h"

static I2C_HandleTypeDef hi2c;

void INA226_Init(void)
{
    // Enable clock for I2C peripheral and GPIO port
    I2Cx_CLK_ENABLE();
    I2Cx_GPIO_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct;

    // Configure SCL, SDA pins as alternate function
    GPIO_InitStruct.Pin = I2Cx_SCL_PIN | I2Cx_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = I2Cx_AF;

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_I2C1_CLK_ENABLE();

    HAL_GPIO_Init(I2Cx_GPIO_PORT, &GPIO_InitStruct);

    // I2C peripheral configuration
    hi2c.Instance = I2Cx;
    hi2c.Init.ClockSpeed = 300000; // Adjust as needed
    hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c.Init.OwnAddress1 = 0;
    hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c.Init.OwnAddress2 = 0;
    hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    HAL_I2C_Init(&hi2c);
}

HAL_StatusTypeDef INA226_present(void)
{
    uint8_t data[2];
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c, INA226_ADDRESS, INA260_REG_CONFIG, I2C_MEMADD_SIZE_8BIT, data, 2, 100);
    return status;
}

HAL_StatusTypeDef readBusVoltage(uint16_t *busVoltage)
{
    uint8_t data[2];
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c, INA226_ADDRESS, INA260_REG_BUSVOLTAGE, I2C_MEMADD_SIZE_8BIT, data, 2, 100);
    if (status == HAL_OK)
    {
        uint16_t rawVoltage = (data[0] << 8) | data[1];
        *busVoltage = rawVoltage * BUS_VOLTAGE_LSB; // 1.25mV/LSB
    }
    return status;
}

HAL_StatusTypeDef readCurrent(uint16_t *current)
{
    uint8_t data[2];
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c, INA226_ADDRESS, INA260_REG_CURRENT, I2C_MEMADD_SIZE_8BIT, data, 2, 100);
    if (status == HAL_OK)
    {
        uint16_t rawCurrent = (data[0] << 8) | data[1];
        if (rawCurrent < 0)
        {
            // Convert rawCurrent to its absolute value and set the sign bit in two's complement
            rawCurrent = ~rawCurrent + 1;
            rawCurrent *= -1;
        }
        *current = rawCurrent * CURRENT_LSB; // 1.25mA/LSB
    }

    return status;
}

HAL_StatusTypeDef readPower(uint16_t *power)
{
    uint8_t data[2];
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c, INA226_ADDRESS, INA260_REG_POWER, I2C_MEMADD_SIZE_8BIT, data, 2, 100);
    if (status == HAL_OK)
    {
        uint16_t rawPower = (data[0] << 8) | data[1];
        *power = rawPower * POWER_LSB; // 10mW/LSB
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