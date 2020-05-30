#include <stdio.h>

#include "stm32f7xx_hal.h"
#include "stm32f7xx_nucleo_144_BSP.h"

#include "board_config.h"
#include "globals.h"
#include "main.h"

#include "imu.hpp"

// ADXL345 -> 0x53
// L3G4200D -> 0x69
// BMP085 -> 0x77
// HMC5883L -> 0x1e

int main(void) {
	uint32_t curr = 0;
	board_init();
	printf("Hello World!\n");

	ADXL345 adxl;

	adxl345_data acc_data;
	printf("Acc ID: %X\n", adxl.id());
	while(1) {
		/* Blink Red LED */

		adxl.data(&acc_data);
		printf("Acc x val: %d\ty val: %d\tz val: %d\n", acc_data.x, acc_data.y, acc_data.z);

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
