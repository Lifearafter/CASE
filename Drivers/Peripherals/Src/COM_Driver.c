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
    if (HAL_UART_Transmit(&uart_handle, (uint8_t *)str, 32, HAL_MAX_DELAY) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief Print a string to the COM port
 * @param str the string to print
 * @param size the size of the string
 * @retval None
 */
void COM_printf_chararray(char *str, uint16_t size)
{
    if (HAL_UART_Transmit(&uart_handle, (uint8_t *)str, size, HAL_MAX_DELAY) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief Convert a float to a string and print to the COM port
 * @param x the float to print
 * @retval None
 */
char float_to_char(float x, char *p)
{
    char *s = p + CHAR_BUFF_SIZE; // go to end of buffer
    uint16_t decimals;            // variable to store the decimals
    int units;                    // variable to store the units (part to left of decimal place)
    if (x < 0)
    {                                     // take care of negative numbers
        decimals = (int)(x * -100) % 100; // make 1000 for 3 decimals etc.
        units = (int)(-1 * x);
    }
    else
    { // positive numbers
        decimals = (int)(x * 100) % 100;
        units = (int)x;
    }

    *--s = (decimals % 10) + '0';
    decimals /= 10; // repeat for as many decimal places as you need
    *--s = (decimals % 10) + '0';
    *--s = '.';

    while (units > 0)
    {
        *--s = (units % 10) + '0';
        units /= 10;
    }
    if (x < 0)
        *--s = '-'; // unary minus sign for negative numbers
    return s;
}