#include <stdio.h>

#include "stm32f7xx_hal.h"
#include "stm32f7xx_nucleo_144_BSP.h"

#include "board_config.h"
#include "globals.h"
#include "main.h"
#include "stm32f7xx_hal.h"

#include "i2c.hpp"
#include "imu.hpp"

// ADXL345 -> 0x53
// L3G4200D -> 0x69
// BMP085 -> 0x77
// HMC5883L -> 0x1e

int main(void) {
	uint32_t curr = 0;
	board_init();

	I2C hi2c;
	printf("Hello World!\n");

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
