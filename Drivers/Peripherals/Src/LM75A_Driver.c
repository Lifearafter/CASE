#include "LM75A_Driver.h"

// Private function prototypes
static void I2C_GPIO_Init(void);

I2C_HandleTypeDef hi2c;

// Initialize I2C peripheral and GPIO pins
void I2C_Init(void)
{

    // Enable clock for I2C peripheral and GPIO port
    I2Cx_CLK_ENABLE();
    I2Cx_GPIO_CLK_ENABLE();

    // Initialize GPIO pins for I2C
    I2C_GPIO_Init();

    // I2C peripheral configuration
    hi2c.Instance = I2Cx;
    hi2c.Init.ClockSpeed = 100000; // Adjust as needed
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
HAL_StatusTypeDef I2C_Write(uint8_t device_address, uint8_t register_address, uint8_t *data, uint16_t size)
{
    return HAL_I2C_Master_Transmit(&hi2c, device_address, data, size, HAL_MAX_DELAY);
}

// Read data from an I2C device
HAL_StatusTypeDef I2C_Read(uint8_t device_address, uint8_t register_address, uint8_t *data, uint16_t size)
{
    return HAL_I2C_Master_Receive(&hi2c, device_address, data, size, HAL_MAX_DELAY);
}

// Initialize GPIO pins for I2C
static void I2C_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Configure SCL, SDA pins as alternate function
    GPIO_InitStruct.Pin = I2Cx_SCL_PIN | I2Cx_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = I2Cx_AF;
    HAL_GPIO_Init(I2Cx_GPIO_PORT, &GPIO_InitStruct);
}