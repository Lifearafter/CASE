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
    LM75ARead();
    INA226Read();
}

/**
 * @brief Read the LM75A temperature sensor
 * @param pvParameters not used
 * @retval None
 */
void LM75ARead()
{
    LM75_Init();
    COM_Init();

    uint8_t data[2];
    uint8_t exit_counter = 0;

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
            exit_counter++;

            if (exit_counter == 5)
            {
                COM_printf("LM75A not responding, exiting\n");
                break;
            }
            continue;
        }

        temperature = (float)((data[0] << 8) | data[1]) / 256;
        float_to_char(temperature, tes);
        COM_printf_chararray(tes, 32);
        COM_printf("\n");

        break;
    }
}

/**
 * @brief Read the INA226 current sensor (Current, Power, Bus Voltage)
 * @param pvParameters not used
 * @retval None
 */
void INA226Read()
{
    INA226_Init();
    COM_Init();

    uint8_t exit_counter = 0;
    uint16_t data;
    char tes[32];

    float current;
    float power;
    float bus_voltage;

    // Initialize the buffer with 0
    memset(tes, 0, sizeof(tes));

    for (;;)
    {
        HAL_StatusTypeDef status = readCurrent(&data);
        current = (float)data / 1000;

        HAL_StatusTypeDef status2 = readBusVoltage(&data);
        bus_voltage = (float)data / 1000;

        HAL_StatusTypeDef status3 = readPower(&data);
        power = (float)data / 1000;

        if (status != HAL_OK || status2 != HAL_OK || status3 != HAL_OK)
        {

            if (status == HAL_BUSY)
            {
                COM_printf("INA226 busy");
                continue;
            }
            COM_printf("Error reading INA226 \n");

            exit_counter++;
            if (exit_counter == 5)
            {
                COM_printf("INA226 not responding, exiting\n");
                break;
            }

            vTaskDelay(1000);

            continue;
        }

        float_to_char(current, tes);
        COM_printf_chararray(tes, 32);
        COM_printf("\n");

        float_to_char(bus_voltage, tes);
        COM_printf_chararray(tes, 32);
        COM_printf("\n");

        float_to_char(power, tes);
        COM_printf_chararray(tes, 32);
        COM_printf("\n");

        break;
    }
}