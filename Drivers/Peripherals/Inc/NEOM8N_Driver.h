#ifndef __NEOM8N_DRIVER_H
#define __NEOM8N_DRIVER_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "minmea.h"
#include "gpio_mapping.h"
#include "error_handler.h"

#include <string.h>
#include <stdio.h>

#define DEF_BAUDRATE 9600
#define DEF_TIMEOUT HAL_MAX_DELAY

// Define USART instance
#define USARTx USART1

// Define GPIO pins used for UART
#define USARTx_TX_PIN GPIO_PIN_9
#define USARTx_TX_GPIO_PORT GPIOA
#define USARTx_TX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_AF GPIO_AF7_USART1

#define USARTx_RX_PIN GPIO_PIN_10
#define USARTx_RX_GPIO_PORT GPIOA
#define USARTx_RX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_RX_AF GPIO_AF7_USART1

typedef struct
{
    uint8_t *const buffer;
    int head;
    int tail;
    const int maxlen;
} circ_bbuf_t;

// Function prototypes
void NEOM8N_Init(void);
void NEOM8N_Receive_Uart(uint8_t *data, uint16_t size);
void NEOM8N_Transmit_Uart(uint8_t *data, uint16_t size);
void UART_GPIO_Init(void);

#endif
