#include "NEOM8N_Driver.h"

UART_HandleTypeDef huart;
HAL_StatusTypeDef status;

void NEOM8N_Init(void)
{
    huart.Instance = USARTx;
    huart.Init.BaudRate = DEF_BAUDRATE;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart) != HAL_OK)
    {
        Error_Handler();
    }
}

void NEOM8N_Transmit_Uart(uint8_t *data, uint16_t size)
{
    status = HAL_UART_Transmit(&huart, data, size, DEF_TIMEOUT);

    if (status != HAL_OK)
    {
        Error_Handler();
    }
}

void NEOM8N_Receive_Uart(uint8_t *data, uint16_t size)
{
    status = HAL_UART_Receive(&huart, data, size, DEF_TIMEOUT);

    if (status != HAL_OK)
    {
        Error_Handler();
    }
}
