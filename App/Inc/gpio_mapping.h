#ifndef __GPIO_MAPPING_H
#define __GPIO_MAPPING_H

#include "stm32f4xx_hal.h"

#ifndef B1_Pin
#define B1_Pin GPIO_PIN_13
#endif

#ifndef B1_GPIO_Port
#define B1_GPIO_Port GPIOC
#endif

#ifndef USART2_TX_Pin
#define USART_TX_Pin GPIO_PIN_2
#endif

#ifndef USART2_TX_GPIO_Port
#define USART_TX_GPIO_Port GPIOA
#endif

#ifndef USART2_RX_Pin
#define USART_RX_Pin GPIO_PIN_3
#endif

#ifndef USART2_RX_GPIO_Port
#define USART_RX_GPIO_Port GPIOA
#endif

#ifndef LD2_Pin
#define LD2_Pin GPIO_PIN_5
#endif

#ifndef LD2_GPIO_Port
#define LD2_GPIO_Port GPIOA
#endif

#ifndef TMS_Pin
#define TMS_Pin GPIO_PIN_13
#endif

#ifndef TMS_GPIO_Port
#define TMS_GPIO_Port GPIOA
#endif

#ifndef TCK_Pin
#define TCK_Pin GPIO_PIN_14
#endif

#ifndef TCK_GPIO_Port
#define TCK_GPIO_Port GPIOA
#endif

#ifndef SWO_Pin
#define SWO_Pin GPIO_PIN_3
#endif

#define SWO_GPIO_Port GPIOB
#define I2Cx I2C1
#define I2Cx_CLK_ENABLE() __HAL_RCC_I2C1_CLK_ENABLE()
#define I2Cx_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_SCL_PIN GPIO_PIN_8
#define I2Cx_SDA_PIN GPIO_PIN_9
#define I2Cx_GPIO_PORT GPIOB
#define I2Cx_AF GPIO_AF4_I2C1

#endif