#include "CC1120_Driver.h"

// SPI Handle
SPI_HandleTypeDef hspi;

// Initialize SPI peripheral
void SPI_Init(void)
{
    hspi.Instance = SPI1;
    hspi.Init.Mode = SPI_MODE_MASTER;
    hspi.Init.Direction = SPI_DIRECTION_2LINES;
    hspi.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi.Init.NSS = SPI_NSS_SOFT;
    hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2; // Adjust as needed
    hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi.Init.CRCPolynomial = 10;
    HAL_SPI_Init(&hspi);
}

// Write to CC1120 register
void CC1120_WriteRegister(uint8_t regAddr, uint8_t data)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // CS low
    uint8_t txData[2];
    txData[0] = regAddr | 0x80; // Setting write command
    txData[1] = data;
    HAL_SPI_Transmit(&hspi, txData, 2, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); // CS high
}

// Read from CC1120 register
uint8_t CC1120_ReadRegister(uint8_t regAddr)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // CS low
    uint8_t txData = regAddr | 0x80;                      // Setting read command
    uint8_t rxData;
    HAL_SPI_Transmit(&hspi, &txData, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi, &rxData, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); // CS high
    return rxData;
}
