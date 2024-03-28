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
    COM_Init();
    COM_printf("Telemetry task started\n");
    INA226Read();
    LM75ARead();
    ADXL345Read();
    vTaskDelete(NULL);
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

    for (;;) // Infinite loop
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
        COM_printf("Temperature: ");
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

    if (INA226_present() != HAL_OK)
    {
        COM_printf("INA226 not present\n");
        return;
    }

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
        COM_printf("Current: ");
        COM_printf_chararray(tes, 32);
        COM_printf("\n");

        float_to_char(bus_voltage, tes);
        COM_printf("Bus Voltage: ");
        COM_printf_chararray(tes, 32);
        COM_printf("\n");

        float_to_char(power, tes);
        COM_printf("Power: ");
        COM_printf_chararray(tes, 32);
        COM_printf("\n");

        break;
    }
}

void ADXL345Read()
{
    ADXL345_Init();
    COM_Init();

    int16_t x = 0, y = 0, z = 0;

    for (;;)
    {
        ADXL345_ReadAccel(x, y, z);

        if (x != 0 || y != 0 || z != 0)
        {

            COM_printf("X: ");
            COM_printf(x);
            COM_printf("\n");

            COM_printf("Y: ");
            COM_printf(y);
            COM_printf("\n");

            COM_printf("Z: ");
            COM_printf(z);
            COM_printf("\n");
            break;
        }
        else
        {
            continue;
        }
    }
}