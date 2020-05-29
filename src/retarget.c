#include "globals.h"
#include "stm32f7xx_hal.h"

int _write(int fd, const void* buf, size_t count) {
	HAL_UART_Transmit(&huart3, (uint8_t*)buf, count, 500);
	return count;
}

int _read(int __fd, void* __buf, size_t __nbyte) {
	HAL_UART_Receive(&huart3, (uint8_t*)__buf, __nbyte, 500);
	return __nbyte;
}
