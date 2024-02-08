#ifndef __COM_DRIVER_H
#define __COM_DRIVER_H

#include <string.h>

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "error_handler.h"

#define COM_BaudRate 9600
#define CHAR_BUFF_SIZE 32

void COM_Init(void);
void COM_printf(char *str);
void COM_printf_chararray(char *str, uint16_t size);
char float_to_char(float x, char *p);

#endif