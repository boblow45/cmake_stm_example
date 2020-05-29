#include <stdint.h>
#include <stdio.h>

#include "error_handling.h"
#include "globals.h"

void assert_failed(uint8_t* file, uint32_t line) {
	printf("assert failed in file %s on line %lu.\n", file, line);
	while(1) {
		;
	}
}

void _Error_Handler(char* file, int line) {

	if(huart3.gState != HAL_UART_STATE_RESET) {
		printf("Error: %p\r\n", __builtin_return_address(0));
	}

	// BSP_LED_On(LED_RED); /* Turn LED3 on */
	while(1) {
		;
	}
}
