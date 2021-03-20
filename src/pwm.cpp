#include "pwm.hpp"
#include "error_handling.h"
#include "stm32f7xx_hal.h"

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle);

void MX_TIM1_Init(TIM_HandleTypeDef* tim_handle) {

	TIM_MasterConfigTypeDef sMasterConfig;
	TIM_OC_InitTypeDef sConfigOC;

	tim_handle->Instance = TIM1;
	tim_handle->Init.Prescaler = 0;
	tim_handle->Init.CounterMode = TIM_COUNTERMODE_UP;
	tim_handle->Init.Period = 500;
	tim_handle->Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
	tim_handle->Init.RepetitionCounter = 0;
	tim_handle->Init.AutoReloadPreload = 0;

	if(HAL_TIM_PWM_Init(tim_handle) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if(HAL_TIMEx_MasterConfigSynchronization(tim_handle, &sMasterConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 400;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if(HAL_TIM_PWM_ConfigChannel(tim_handle, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	HAL_TIM_OC_Init(tim_handle);
	HAL_TIM_MspPostInit(tim_handle);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* tim_handle) {
	GPIO_InitTypeDef GPIO_InitStruct;
	if(tim_handle->Instance == TIM1) {
		__HAL_RCC_TIM1_CLK_ENABLE();
	}
}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle) {

	GPIO_InitTypeDef GPIO_InitStruct;
	if(timHandle->Instance == TIM1) {
		/* USER CODE BEGIN TIM2_MspPostInit 0 */

		/* USER CODE END TIM2_MspPostInit 0 */

		/**TIM2 GPIO Configuration    
			// PE9 (pin 60) -> Timer_A_PWM1 (TIM1_CH1)
   		 */
		__HAL_RCC_GPIOE_CLK_ENABLE();

		GPIO_InitStruct.Pin = GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

		/* USER CODE BEGIN TIM2_MspPostInit 1 */

		/* USER CODE END TIM2_MspPostInit 1 */
	}
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* tim_handle) {}
