#ifndef __Telemetry_H
#define __Telemetry_H

#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "gpio_mapping.h"
#include "INA226_Driver.h"
#include "LM75A_Driver.h"
#include "ADXL345_Driver.h"
#include "NEOM8N_Driver.h"
#include "error_handler.h"
#include "COM_Driver.h"

#include <string.h>

void vTelemetryInit(void);
void vTelemetryTask(void *pvParameters);

void LM75ARead();
void INA226Read();
void NEOM8NRead();
void ADXL345Read();
void IAM20685Read();
void LIS3MDLRead();

#endif