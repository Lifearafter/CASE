#ifndef vBlinkLD2
#define vBlinkLD2

#include "main.h"

/**
 * @brief LD2 blinking task
 * @param pvParameters not used
 * @retval None
 */
void vBlinkLD2(void *pvParameters)
{
    for (;;)
    {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
#endif