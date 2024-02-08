#include "vTelemetry.h"

/**
 * @brief Initialize the telemetry tasks
 * @param None
 * @retval None
 */
void vTelemetryInit(void)
{

    xTaskCreate(vTelemetryTask, "Telemetry", 128, NULL, 1, NULL);
}

/**
 * @brief Initialize the telemetry tasks
 * @param pvParameters not used
 * @retval None
 */
void vTelemetryTask(void *pvParameters)
{
    xTaskCreate(vTelemetryLM75AReadTask, "LM75A Read", 128, NULL, 1, NULL);
}

/**
 * @brief Read the LM75A temperature sensor
 * @param pvParameters not used
 * @retval None
 */
void vTelemetryLM75AReadTask(void *pvParameters)
{
    LM75_Init();
    COM_Init();

    uint8_t data[2];
    float temperature;
    char tes[32];

    // Initialize the buffer with 0
    memset(tes, 0, sizeof(tes));

    for (;;)
    {
        HAL_StatusTypeDef status = LM75_ReadReg(LM75_TEMP_REG, data, 2);

        if (status != HAL_OK)
        {

            if (status == HAL_BUSY)
            {
                COM_printf("LM75A busy");
                continue;
            }
            COM_printf("Error reading LM75A \n");
            vTaskDelay(1000);
            continue;
        }

        temperature = (float)((data[0] << 8) | data[1]) / 256;
        float_to_char(temperature, tes);
        COM_printf_chararray(tes, 32);
        COM_printf("\n");
        vTaskDelay(1000);
    }
}