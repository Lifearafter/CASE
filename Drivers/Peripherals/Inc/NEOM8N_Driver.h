#ifndef __NEOM8N_DRIVER_H
#define __NEOM8N_DRIVER_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"
#include "gpio_mapping.h"

// Define SPI peripheral and GPIO pins
#define SPIx SPI1 // Replace with the appropriate SPI peripheral
#define SPIx_CLK_ENABLE() __HAL_RCC_SPI1_CLK_ENABLE()
#define SPIx_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE() // Replace with the appropriate GPIO port
#define SPIx_SCK_PIN GPIO_PIN_5                             // Replace with the appropriate SCK pin
#define SPIx_MISO_PIN GPIO_PIN_6                            // Replace with the appropriate MISO pin
#define SPIx_MOSI_PIN GPIO_PIN_7                            // Replace with the appropriate MOSI pin
#define SPIx_GPIO_PORT GPIOA                                // Replace with the appropriate GPIO port
#define SPIx_AF GPIO_AF5_SPI1                               // Replace with the appropriate alternate function

// Function prototypes
void SPI_Init(void);
void SPI_Transmit(uint8_t data);
uint8_t SPI_Receive(void);

#endif
