#include "COM_Driver.h"

UART_HandleTypeDef uart_handle;

void COM_Init(void)
{
    __HAL_RCC_USART2_CLK_ENABLE();

    uart_handle.Instance = USART2;
    uart_handle.Init.BaudRate = 9600;
    uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
    uart_handle.Init.StopBits = UART_STOPBITS_1;
    uart_handle.Init.Parity = UART_PARITY_NONE;
    uart_handle.Init.Mode = UART_MODE_TX_RX;
    uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&uart_handle) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief Print a string to the COM port
 * @param str the string to print
 * @retval None
 */
void COM_printf(char *str)
{
    if (HAL_UART_Transmit(&uart_handle, (uint8_t *)str, strlen(str), HAL_MAX_DELAY) != HAL_OK)
    {
        Error_Handler();
    }
}