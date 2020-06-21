#include <stdio.h>

#include "stm32f7xx_hal.h"
#include "stm32f7xx_nucleo_144_BSP.h"

#include "board_config.h"
#include "globals.h"
#include "main.h"
#include "stm32f7xx_hal.h"

#include "adc.h"

#include "FreeRTOS.h"
#include "task.h"

#include "i2c.hpp"
#include "imu.hpp"
#include "pwm.hpp"

void set_PWM(TIM_HandleTypeDef* timer, uint32_t channel, uint16_t period, uint16_t pulse) {
	HAL_TIM_PWM_Stop(timer, channel); // stop generation of pwm
	TIM_OC_InitTypeDef sConfigOC;
	timer->Init.Period = period; // set the period duration
	HAL_TIM_PWM_Init(timer); // reinititialise with new period value
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = pulse; // set the pulse duration
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(timer, &sConfigOC, channel);
	HAL_TIM_PWM_Start(timer, channel); // start pwm generation
}

// TIM1_CH1 -> PE9

void vTask1(void* pvParameters) {
	uint32_t curr = 0;
	/* As per most tasks, this task is implemented in an infinite loop. */
	for(;;) {
		if(curr) {
			BSP_LED_On(LED_GREEN);
			curr = 0;
		}
		else {
			BSP_LED_Off(LED_GREEN);
			curr = 1;
		}
		vTaskDelay(pdMS_TO_TICKS(200));
	}
}

void vTask2(void* pvParameters) {

	// TIM_HandleTypeDef tim_handle;
	// MX_TIM1_Init(&tim_handle);
	// HAL_TIM_PWM_MspInit(&tim_handle);

	ADC_HandleTypeDef hadc1;
	MX_ADC1_Init(&hadc1);
	//HAL_ADC_MspInit(&hadc1);
	I2C hi2c;

	// IMU imu(hi2c);
	euler_angles angles;

	uint32_t adc_val;
	float voltage;
	// set_PWM(&tim_handle, TIM_CHANNEL_1, 255, 10);
	for(;;) {
		HAL_ADC_Start(&hadc1);

		HAL_ADC_Stop(&hadc1);

		adc_val = HAL_ADC_GetValue(&hadc1);
		voltage = ((float)adc_val / (1 << 12)) * 3.3;
		printf("ADC Voltage:%f\r\n", voltage);
		// imu.get_euler_angles(&angles);
		// printf("Pitch:%3.4f\tRoll:%3.4f\tYaw:%3.4f\r\n", angles.pitch, angles.roll, angles.yaw);
		/* Delay for a period. */
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

int main(void) {

	board_init();

	printf("System core clock %lu\n", SystemCoreClock);

	xTaskCreate(vTask1, "Task 1", 1000, NULL, 1, NULL);
	xTaskCreate(vTask2, "Task 2", 1000, NULL, 2, NULL);

	vTaskStartScheduler();

	while(1) {
	}
	return 0;
}
