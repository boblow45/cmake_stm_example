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
	/* As per most tasks, this task is implemented in an infinite loop. */
	for(;;) {
		printf("Task 1 is running\r\n");
		/* Delay for a period. */
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

void vTask2(void* pvParameters) {
	/* As per most tasks, this task is implemented in an infinite loop. */
	for(;;) {
		printf("Task 2 is running\r\n");

		/* Delay for a period. */
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

int main(void) {
	uint32_t curr = 0;
	board_init();

	printf("Hello World!\n");
	printf("System core clock %d\n", SystemCoreClock);

	xTaskCreate(vTask1, "Task 1", 1000, NULL, 2, NULL);
	xTaskCreate(vTask2, "Task 2", 1000, NULL, 1, NULL);

	vTaskStartScheduler();

	I2C hi2c;
	ADXL345 accelerometer(hi2c);
	L3G4200D gyroscope(hi2c);
	HMC5883L compass(hi2c);

	adxl345_data acc_data;
	l3g4300d_data gyro_data;
	hmc5883l_data compass_data;
	printf("Accelerometer ID: %X\n", accelerometer.id());
	printf("Gyroscope ID: %X\n", gyroscope.id());
	printf("Compass ID: %X\n", compass.id());
	while(1) {
		/* Blink Red LED */

		accelerometer.data(&acc_data);
		gyroscope.data(&gyro_data);
		compass.data(&compass_data);
		printf("Acc x val: %d\ty val: %d\tz val: %d\n", acc_data.x, acc_data.y, acc_data.z);
		printf(
			"Gyroscope x val: %d\ty val: %d\tz val: %d\n", gyro_data.x, gyro_data.y, gyro_data.z);
		printf("Compass x val: %d\ty val: %d\tz val: %d\n",
			compass_data.x,
			compass_data.y,
			compass_data.z);

		HAL_Delay(100);
		if(curr) {
			BSP_LED_On(LED_GREEN);
			curr = 0;
		}
		else {
			BSP_LED_Off(LED_GREEN);
			curr = 1;
		}
	}
	return 0;
}
