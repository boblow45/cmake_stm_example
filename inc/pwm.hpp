#ifndef __PWM_H
#define __PWM_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f7xx_hal.h"
#include <stdint.h>

	void MX_TIM1_Init(TIM_HandleTypeDef* tim_handle);
	void MX_TIM2_Init(TIM_HandleTypeDef* tim_handle);
	void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* tim_handle);
	void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* tim_handle);

#ifdef __cplusplus
}
#endif
#endif /*__PWM_H */