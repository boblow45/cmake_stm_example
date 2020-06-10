/**
  ******************************************************************************
  * File Name          : ADC.c
  * Description        : This file provides code for the configuration
  *                      of the ADC instances.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

#include "stm32f7xx_hal.h"

#include "adc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

const uint16_t Analog_1_Pin = GPIO_PIN_3;
const uint16_t Analog_2_Pin = GPIO_PIN_1;
const uint16_t Analog_3_Pin = GPIO_PIN_0;
const uint16_t Analog_4_Pin = GPIO_PIN_2;
const uint16_t Analog_5_Pin = GPIO_PIN_3;
const uint16_t Analog_6_Pin = GPIO_PIN_3;
const uint16_t Analog_7_Pin = GPIO_PIN_4;
const uint16_t Analog_8_Pin = GPIO_PIN_5;
const uint16_t Analog_9_Pin = GPIO_PIN_10;

#define Analog_1_GPIO_Port GPIOA
#define Analog_2_GPIO_Port GPIOB

ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc3;

/* ADC1 init function */
void MX_ADC1_Init(ADC_HandleTypeDef* adcHandle) {

	/* USER CODE END ADC1_MspInit 0 */
	/* ADC1 clock enable */
	__HAL_RCC_ADC1_CLK_ENABLE();

	printf("configured ADC1 struct\r\n");
	adcHandle->Instance = ADC1;
	adcHandle->Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	adcHandle->Init.Resolution = ADC_RESOLUTION_12B;
	adcHandle->Init.ScanConvMode = DISABLE;
	adcHandle->Init.ContinuousConvMode = DISABLE;
	adcHandle->Init.DiscontinuousConvMode = DISABLE;
	adcHandle->Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	adcHandle->Init.ExternalTrigConv = ADC_SOFTWARE_START;
	adcHandle->Init.DataAlign = ADC_DATAALIGN_RIGHT;
	adcHandle->Init.NbrOfConversion = 1;
	adcHandle->Init.DMAContinuousRequests = DISABLE;
	adcHandle->Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if(HAL_ADC_Init(adcHandle) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. */
	ADC_ChannelConfTypeDef sConfig;
	sConfig.Channel = ADC_CHANNEL_3;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	if(HAL_ADC_ConfigChannel(adcHandle, &sConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}
}
/* ADC3 init function */
void MX_ADC3_Init(ADC_HandleTypeDef* adcHandle) {
	ADC_ChannelConfTypeDef sConfig;

	/**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
	adcHandle->Instance = ADC3;
	adcHandle->Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	adcHandle->Init.Resolution = ADC_RESOLUTION_12B;
	adcHandle->Init.ScanConvMode = DISABLE;
	adcHandle->Init.ContinuousConvMode = DISABLE;
	adcHandle->Init.DiscontinuousConvMode = DISABLE;
	adcHandle->Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	adcHandle->Init.ExternalTrigConv = ADC_SOFTWARE_START;
	adcHandle->Init.DataAlign = ADC_DATAALIGN_RIGHT;
	adcHandle->Init.NbrOfConversion = 1;
	adcHandle->Init.DMAContinuousRequests = DISABLE;
	adcHandle->Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if(HAL_ADC_Init(adcHandle) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
	sConfig.Channel = ADC_CHANNEL_9;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if(HAL_ADC_ConfigChannel(adcHandle, &sConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle) {

	GPIO_InitTypeDef GPIO_InitStruct;
	if(adcHandle->Instance == ADC1) {
		printf("configured ADC1 GPIOs\r\n");
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		/* USER CODE BEGIN ADC1_MspInit 0 */

		/**ADC1 GPIO Configuration    
    PC0     ------> ADC1_IN10
    PC2     ------> ADC1_IN12
    PC3     ------> ADC1_IN13
    PA3     ------> ADC1_IN3
    PB1     ------> ADC1_IN9 
    */
		GPIO_InitStruct.Pin = Analog_3_Pin | Analog_4_Pin | Analog_5_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = Analog_1_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(Analog_1_GPIO_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = Analog_2_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(Analog_2_GPIO_Port, &GPIO_InitStruct);

		/* USER CODE BEGIN ADC1_MspInit 1 */

		/* USER CODE END ADC1_MspInit 1 */
	}
	else if(adcHandle->Instance == ADC3) {
		/* USER CODE BEGIN ADC3_MspInit 0 */

		/* USER CODE END ADC3_MspInit 0 */
		/* ADC3 clock enable */
		__HAL_RCC_ADC3_CLK_ENABLE();

		/**ADC3 GPIO Configuration    
    PF3     ------> ADC3_IN9
    PF4     ------> ADC3_IN14
    PF5     ------> ADC3_IN15
    PF10     ------> ADC3_IN8 
    */
		GPIO_InitStruct.Pin = Analog_6_Pin | Analog_7_Pin | Analog_8_Pin | Analog_9_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

		/* USER CODE BEGIN ADC3_MspInit 1 */

		/* USER CODE END ADC3_MspInit 1 */
	}
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle) {

	if(adcHandle->Instance == ADC1) {
		/* USER CODE BEGIN ADC1_MspDeInit 0 */

		/* USER CODE END ADC1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_ADC1_CLK_DISABLE();

		/**ADC1 GPIO Configuration    
    PC0     ------> ADC1_IN10
    PC2     ------> ADC1_IN12
    PC3     ------> ADC1_IN13
    PA3     ------> ADC1_IN3
    PB1     ------> ADC1_IN9 
    */
		HAL_GPIO_DeInit(GPIOC, Analog_3_Pin | Analog_4_Pin | Analog_5_Pin);

		HAL_GPIO_DeInit(Analog_1_GPIO_Port, Analog_1_Pin);

		HAL_GPIO_DeInit(Analog_2_GPIO_Port, Analog_2_Pin);

		/* USER CODE BEGIN ADC1_MspDeInit 1 */

		/* USER CODE END ADC1_MspDeInit 1 */
	}
	else if(adcHandle->Instance == ADC3) {
		/* USER CODE BEGIN ADC3_MspDeInit 0 */

		/* USER CODE END ADC3_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_ADC3_CLK_DISABLE();

		/**ADC3 GPIO Configuration    
    PF3     ------> ADC3_IN9
    PF4     ------> ADC3_IN14
    PF5     ------> ADC3_IN15
    PF10     ------> ADC3_IN8 
    */
		HAL_GPIO_DeInit(GPIOF, Analog_6_Pin | Analog_7_Pin | Analog_8_Pin | Analog_9_Pin);

		/* USER CODE BEGIN ADC3_MspDeInit 1 */

		/* USER CODE END ADC3_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
