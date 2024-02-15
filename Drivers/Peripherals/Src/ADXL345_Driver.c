#include "ADXL345_Driver.h"

// Define SPI instance
struct SPI_Module spi;

void ADXL345_Init(void)
{
    // Initialize SPI instance
    spi.instance.Instance = SPI1;
    spi.instance.Init.Mode = SPI_MODE_MASTER;
    spi.instance.Init.Direction = SPI_DIRECTION_2LINES;
    spi.instance.Init.DataSize = SPI_DATASIZE_8BIT;
    spi.instance.Init.CLKPolarity = SPI_POLARITY_LOW;
    spi.instance.Init.CLKPhase = SPI_PHASE_1EDGE;
    spi.instance.Init.NSS = SPI_NSS_SOFT;
    spi.instance.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
    spi.instance.Init.FirstBit = SPI_FIRSTBIT_MSB;
    spi.instance.Init.TIMode = SPI_TIMODE_DISABLE;
    spi.instance.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    spi.instance.Init.CRCPolynomial = 10;
    HAL_SPI_Init(&spi.instance);

    // Initialize CS pin
    GPIO_InitTypeDef GPIO_InitStruct;
    spi.csPort = GPIOA;
    spi.csPin = GPIO_PIN_4;
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = spi.csPin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(spi.csPort, &GPIO_InitStruct);
    HAL_GPIO_WritePin(spi.csPort, spi.csPin, GPIO_PIN_SET);
}

HAL_StatusTypeDef ADXL345_ReadReg(uint8_t register_address, uint8_t *data, uint16_t size)
{
    // Check if the device is ready
    HAL_StatusTypeDef status = HAL_SPI_GetState(&spi.instance);
    if (status != HAL_OK)
    {
        return HAL_ERROR;
    }

    // Select the device
    HAL_GPIO_WritePin(spi.csPort, spi.csPin, GPIO_PIN_RESET);

    // Send the register address
    uint8_t txData = register_address | 0x80;
    HAL_SPI_Transmit(&spi.instance, &txData, 1, HAL_MAX_DELAY);

    // Receive the data
    HAL_SPI_Receive(&spi.instance, data, size, HAL_MAX_DELAY);

    // Deselect the device
    HAL_GPIO_WritePin(spi.csPort, spi.csPin, GPIO_PIN_SET);

    return HAL_OK;
}

HAL_StatusTypeDef ADXL345_WriteReg(uint8_t register_address, uint8_t *data, uint16_t size)
{
    // Check if the device is ready
    HAL_StatusTypeDef status = HAL_SPI_GetState(&spi.instance);
    if (status != HAL_OK)
    {
        return HAL_ERROR;
    }

    // Select the device
    HAL_GPIO_WritePin(spi.csPort, spi.csPin, GPIO_PIN_RESET);

    // Send the register address
    uint8_t txData = register_address & 0x7F;
    HAL_SPI_Transmit(&spi.instance, &txData, 1, HAL_MAX_DELAY);

    // Send the data
    HAL_SPI_Transmit(&spi.instance, data, size, HAL_MAX_DELAY);

    // Deselect the device
    HAL_GPIO_WritePin(spi.csPort, spi.csPin, GPIO_PIN_SET);

    return HAL_OK;
}
