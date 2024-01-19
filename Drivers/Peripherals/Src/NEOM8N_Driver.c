#include "NEOM8N_Driver.h"
#include "gpio_mapping.h"
#include "stm32f4xx_hal.h"

// Private function prototypes
static void SPI_GPIO_Init(void);

// Initialize SPI peripheral and GPIO pins
void SPI_Init(void)
{
    SPI_HandleTypeDef hspi2;

    // Enable clock for SPI peripheral and GPIO port
    SPIx_CLK_ENABLE();
    SPIx_GPIO_CLK_ENABLE();

    // Initialize GPIO pins for SPI
    SPI_GPIO_Init();

    // SPI peripheral configuration
    hspi2.Instance = SPI2;
    hspi2.Init.Mode = SPI_MODE_MASTER;
    hspi2.Init.Direction = SPI_DIRECTION_1LINE;
    hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi2.Init.NSS = SPI_NSS_SOFT;
    hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi2.Init.CRCPolynomial = 10;

    if (HAL_SPI_Init(&hspi2) != HAL_OK)
    {
        // Initialization Error
        Error_Handler();
    }
}

// Transmit data over SPI
void SPI_Transmit(uint8_t data)
{
    while ((SPIx->SR & SPI_FLAG_TXE) == RESET)
        ;
    SPIx->DR = data;
    while ((SPIx->SR & SPI_FLAG_BSY) != RESET)
        ;
}

// Receive data over SPI
uint8_t SPI_Receive(void)
{
    while ((SPIx->SR & SPI_FLAG_RXNE) == RESET)
        ;
    return SPIx->DR;
}

// Initialize GPIO pins for SPI
static void SPI_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Configure SCK, MISO, MOSI pins as alternate function
    GPIO_InitStruct.Pin = SPIx_SCK_PIN | SPIx_MISO_PIN | SPIx_MOSI_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = SPIx_AF;
    HAL_GPIO_Init(SPIx_GPIO_PORT, &GPIO_InitStruct);
}