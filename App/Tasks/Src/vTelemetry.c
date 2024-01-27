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
    I2C_Init();
    xTaskCreate(vTelemetryLM75AReadTask, "LM75A Read", 128, NULL, 1, NULL);
}

/**
 * @brief Read the LM75A temperature sensor
 * @param pvParameters not used
 * @retval None
 */
void vTelemetryLM75AReadTask(void *pvParameters)
{
    I2C_Write(LM75A_ADDRESS, LM75A_CONF_REG, 0, 0);
    uint8_t data[2];
    float temperature;
    for (;;)
    {
        HAL_StatusTypeDef status = I2C_Read(LM75A_ADDRESS, LM75A_TEMP_REG, data, 2);
        temperature = (float)((data[0] << 8) | data[1]) / 256;
        printf("Temperature: %f\n", temperature);
        vTaskDelay(1000);
    }
}