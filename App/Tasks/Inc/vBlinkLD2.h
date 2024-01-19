#ifndef __VBLINKLD2_H
#define __VBLINKLD2_H

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#include "stm32f4xx_hal.h"
#include "gpio_mapping.h"

void vBlinkLD2(void *pvParameters);

#endif