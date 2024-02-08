#ifndef __COM_DRIVER_H
#define __COM_DRIVER_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include <string.h>
#include "error_handler.h"

#define COM_BaudRate 9600

void COM_Init(void);
void COM_printf(char *str);

#endif