#include "NEOM8N_Driver.h"

UART_HandleTypeDef huart;
HAL_StatusTypeDef status;

void NEOM8N_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct_UART;

    // Enable clock for UART and GPIO ports
    USARTx_TX_GPIO_CLK_ENABLE();
    USARTx_RX_GPIO_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();

    // Configure UART pins
    GPIO_InitStruct_UART.Pin = USARTx_TX_PIN;
    GPIO_InitStruct_UART.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct_UART.Pull = GPIO_PULLUP;
    GPIO_InitStruct_UART.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct_UART.Alternate = USARTx_TX_AF;
    HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct_UART);

    GPIO_InitStruct_UART.Pin = USARTx_RX_PIN;
    GPIO_InitStruct_UART.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct_UART.Pull = GPIO_PULLUP;
    GPIO_InitStruct_UART.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct_UART.Alternate = USARTx_RX_AF;
    HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct_UART);

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

// Need to implement circular DMA buffer for UART to handle variable length NMEA sentences
// https://github.com/MaJerle/stm32-usart-uart-dma-rx-tx
// Functionality: NeoM8N sends NMEA sentences to the STM32F4 over UART. The STM32F4 receives the sentences and parses them using the minmea library.
void NEOM8N_Receive_Uart(uint8_t *data, uint16_t size)
{

    circ_bbuf_t line;
    uint8_t counter = 0;

    // Initialize UART
    status = HAL_UARTEx_ReceiveToIdle_DMA(&huart, line.buffer, MINMEA_MAX_SENTENCE_LENGTH);

    if (status != HAL_OK)
    {
        Error_Handler();
    }

    // Parse NMEA sentences
    while (fgets(line.buffer, sizeof(line), stdin) != NULL)
    {
        if (line.buffer[counter] != '$')
        {
            if (counter < MINMEA_MAX_SENTENCE_LENGTH)
            {
                counter++;
            }
            else
            {
                break;
            }
            continue;
        }
        parse_buffer(&line);
    }
}

void parse_buffer(circ_bbuf_t *line)
{
    // Parse NMEA sentences
    switch (minmea_sentence_id(line, false))
    {
    case MINMEA_SENTENCE_RMC:
    {
        // Parse RMC sentence: For example, to get the latitude, longitude, and speed
        struct minmea_sentence_rmc frame;
        if (minmea_parse_rmc(&frame, line))
        {
        }
        else
        {
        }
    }
    break;

    case MINMEA_SENTENCE_GGA:
    {
        // Parse GGA sentence: For example, to get the fix quality (0 = invalid, 1 = GPS fix, 2 = DGPS fix, 6 = dead reckoning fix, 7 = manual input mode, 8 = simulation mode)
        struct minmea_sentence_gga frame;
        if (minmea_parse_gga(&frame, line))
        {
        }
        else
        {
        }
    }
    break;

    case MINMEA_SENTENCE_GST:
    {
        // Parse GST sentence: For example, to get the raw latitude, longitude, and altitude error deviation
        struct minmea_sentence_gst frame;
        if (minmea_parse_gst(&frame, line))
        {
        }
        else
        {
        }
    }
    break;

    case MINMEA_SENTENCE_GSV:
    {
        // Parse GSV sentence (satellites in view): For example, to get the number of satellites in view
        struct minmea_sentence_gsv frame;
        if (minmea_parse_gsv(&frame, line))
        {
        }
        else
        {
        }
    }
    break;

    case MINMEA_SENTENCE_VTG:
    {
        // Parse VTG sentence: For example, to get the true track made good and speed over ground
        struct minmea_sentence_vtg frame;
        if (minmea_parse_vtg(&frame, line))
        {
        }
        else
        {
        }
    }
    break;

    case MINMEA_SENTENCE_ZDA:
    {
        // Parse ZDA sentence: For example, to get the time and date
        struct minmea_sentence_zda frame;
        if (minmea_parse_zda(&frame, line))
        {
        }
        else
        {
        }
    }
    break;

    case MINMEA_INVALID:
    {
        // Invalid sentence
    }
    break;

    default:
    {
        // Ignore other sentences
    }
    break;
    }
}
