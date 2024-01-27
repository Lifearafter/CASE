#ifndef __Error_Handler_H
#define __Error_Handler_H

#include "stm32f4xx_hal.h"

// Define error codes
typedef enum
{
    ERROR_NONE = 0,
    ERROR_UNKNOWN,
    ERROR_INVALID_PARAMETER,
    ERROR_TIMEOUT,
    // Add more error codes as needed
} ErrorCode_t;

// Function prototypes
void handleError(ErrorCode_t errorCode);
void handleCriticalError(ErrorCode_t errorCode);
void Error_Handler(void);

#endif