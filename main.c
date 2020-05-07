#include <stdio.h>
#include <stdio.h>

#include "board_config.h"
#include "main.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_nucleo_144_BSP.h"

int32_t main(void) {
	uint32_t curr = 0;
	board_init();

	while(1) {
		/* Blink Red LED */
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
