#ifndef __VBLINKLD2_H
#define __VBLINKLD2_H

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#include "stm32f4xx_hal.h"

#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA

void vBlinkLD2(void *pvParameters);

#endif