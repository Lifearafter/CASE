#include "vTelemetry.h"
#pragma 1

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
    // LM75_WriteReg(LM75A_ADDRESS, LM75_CONF_REG, 0, 0);
    uint8_t data[2];
    volatile float temperature;
    char *tes;
    for (;;)
    {
        volatile HAL_StatusTypeDef status = LM75_ReadReg(LM75A_ADDRESS, LM75_TEMP_REG, data, 2);
        temperature = (float)((data[0] << 8) | data[1]) / 256;
        sprintf(tes, "%f\n", temperature);
        COM_printf(tes);
        vTaskDelay(1000);
    }
}