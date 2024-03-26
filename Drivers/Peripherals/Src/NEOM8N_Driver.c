#include "NEOM8N_Driver.h"

UART_HandleTypeDef huart;
DMA_HandleTypeDef hdma_usart1_rx;

uint8_t circularBuffer[CIRCULAR_BUFFER_SIZE];
uint16_t bufferHead = 0;
uint16_t bufferTail = 0;

void NEOM8N_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct_UART;

    // Enable clock for UART
    __HAL_RCC_USART1_CLK_ENABLE();

    huart.Instance = USARTx;
    huart.Init.BaudRate = DEF_BAUDRATE;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;

    /* DMA controller clock enable */
    __HAL_RCC_DMA2_CLK_ENABLE();

    /* DMA interrupt init */
    /* DMA2_Stream5_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);

    /* Configure the DMA stream for UART reception */
    hdma_usart1_rx.Instance = DMA2_Stream5;
    hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_CIRCULAR;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
        Error_Handler();
    }

    /* Associate the DMA handle with the UART handle */
    __HAL_LINKDMA(&huart, hdmarx, hdma_usart1_rx);

    /* Configure the NVIC for DMA transfer complete interrupt */
    HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);

    if (HAL_UART_Init(&huart) != HAL_OK)
    {
        Error_Handler();
    }
}

void NEOM8N_Transmit_Uart(uint8_t *data, uint16_t size)
{
    HAL_StatusTypeDef status;
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
    static uint8_t buffer[MINMEA_MAX_SENTENCE_LENGTH];
    static uint16_t bufferIndex = 0;

    // Receive data until an idle line is detected
    HAL_StatusTypeDef status = HAL_UARTEx_ReceiveToIdle_DMA(&huart, buffer, MINMEA_MAX_SENTENCE_LENGTH);

    if (status == HAL_OK)
    {
        // Null-terminate the buffer
        buffer[bufferIndex] = '\0';

        // Parse the NMEA sentence
        if (buffer[0] == '$')
        {
            parse_buffer(buffer);
        }

        // Reset the buffer index
        bufferIndex = 0;
    }
    else
    {
        Error_Handler(); // Handle other errors
    }

    // Restart the DMA transfer for the next sentence
    HAL_UARTEx_ReceiveToIdle_DMA(&huart, buffer, MINMEA_MAX_SENTENCE_LENGTH);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1) // Check if it's the UART instance you're using
    {
        // Process the received data in the circular buffer
        uint16_t dataCount = CIRCULAR_BUFFER_SIZE - hdma_usart1_rx.Instance->NDTR;
        uint16_t nextHead = (bufferHead + dataCount) % CIRCULAR_BUFFER_SIZE;

        // Check for buffer overflow
        if (nextHead == bufferTail)
        {
            // Handle buffer overflow
            bufferTail = (bufferTail + 1) % CIRCULAR_BUFFER_SIZE;
            bufferHead = nextHead;
        }
        else
        {
            bufferHead = nextHead;
        }
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
