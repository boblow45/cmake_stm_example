#include <stdio.h>

#include "stm32f7xx_hal.h"
#include "stm32f7xx_nucleo_144_BSP.h"

#include "board_config.h"
#include "globals.h"
#include "main.h"
#include "stm32f7xx_hal.h"

#include "FreeRTOS.h"
#include "task.h"

#include "i2c.hpp"
#include "imu.hpp"

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
	I2C hi2c;

	IMU imu(hi2c);
	euler_angles angles;
	for(;;) {
		imu.get_euler_angles(&angles);
		printf("Pitch: %d\tRoll: %d\r\n", (int32_t)angles.pitch, (int32_t)angles.roll);
		/* Delay for a period. */
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

int main(void) {

	board_init();

	printf("System core clock %d\n", SystemCoreClock);

	xTaskCreate(vTask1, "Task 1", 1000, NULL, 1, NULL);
	xTaskCreate(vTask2, "Task 2", 1000, NULL, 2, NULL);

	vTaskStartScheduler();

	while(1) {
	}
	return 0;
}
