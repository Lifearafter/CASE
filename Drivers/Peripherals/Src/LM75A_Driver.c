#include "LM75A_Driver.h"

I2C_HandleTypeDef hi2c;

// Initialize I2C peripheral and GPIO pins
void LM75_Init(void)
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

    if (HAL_I2C_Init(&hi2c) != HAL_OK)
    {
        // Initialization Error
        Error_Handler();
    }
}

// Write data to an I2C device
HAL_StatusTypeDef LM75_WriteReg(uint8_t register_address, uint8_t *data, uint16_t size)
{
    if (register_address == LM75_TEMP_REG || register_address == LM75_INFO_REG)
    {
        return HAL_ERROR;
    }

    // Check if the device is ready
    HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(&hi2c, LM75A_ADDRESS, 10, 1000);
    if (status != HAL_OK)
    {
        HAL_Delay(1000);
        return HAL_ERROR;
    }

    return HAL_I2C_Master_Transmit(&hi2c, LM75A_ADDRESS, data, size, HAL_MAX_DELAY);
}

// Read data from an I2C device
HAL_StatusTypeDef LM75_ReadReg(uint8_t register_address, uint8_t *data, uint16_t size)
{
    // Check if the device is ready
    HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(&hi2c, LM75A_ADDRESS, 10, HAL_MAX_DELAY);
    if (status != HAL_OK)
    {
        // if (status == HAL_BUSY)
        // {
        //     I2C_ClearBusyFlagErratum(&hi2c);
        // }'
        return HAL_ERROR;
    }

    return HAL_I2C_Master_Receive(&hi2c, LM75A_ADDRESS, data, size, HAL_MAX_DELAY);
}

