#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f7xx_hal.h"

	UART_HandleTypeDef huart3;
	I2C_HandleTypeDef hi2c;

#ifdef __cplusplus
}
#endif

#endif // __GLOBALS_H__