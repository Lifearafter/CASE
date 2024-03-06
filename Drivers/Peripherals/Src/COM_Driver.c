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
    if (HAL_UART_Transmit(&uart_handle, (uint8_t *)str, strlen((char *)str), HAL_MAX_DELAY) != HAL_OK)
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
    char *s = p + CHAR_BUFF_SIZE; // Go to end of buffer
    int units;
    int decimals;

    if (x < 0)
    {
        decimals = (int)(x * -100000) % 100000; // Adjust for 5 decimal places
        units = (int)(-1 * x);
    }
    else
    {
        decimals = (int)(x * 100000) % 100000;
        units = (int)x;
    }

    // Convert decimal part to string with leading zeros if necessary
    for (int i = 0; i < 5; i++)
    {
        *--s = (decimals % 10) + '0';
        decimals /= 10;
    }
    *--s = '.'; // Decimal point

    // Convert integer part to string
    do
    {
        *--s = (units % 10) + '0';
        units /= 10;
    } while (units > 0);

    if (x < 0)
        *--s = '-'; // Unary minus sign for negative numbers
    return s;
}