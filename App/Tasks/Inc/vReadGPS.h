// Use interrupts to read GPS data
// Try to implement a freeRTOS interrupt driven task
//  2024-01-025  Zaid M.  Created

#ifndef _vReadGPS_H_
#define _vReadGPS_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "NEOM8N_Driver.h"
#include "error_handler.h"

// Task handle
TaskHandle_t vReadGPSHandle;

#endif