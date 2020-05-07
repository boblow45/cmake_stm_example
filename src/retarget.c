#include <stdint.h>
#include <stdio.h>

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_conf.h"
#include "globals.h"
#include "usart.h"


// int _write(int fd, const void* buf, size_t count) {
// 	HAL_UART_Transmit(&huart3, (uint8_t*)buf, count, 500);
// 	return count;
// }

// int _read(int fd, const void* buf, size_t count) {
// 	HAL_UART_Receive(&huart3, (uint8_t*)buf, count, 500);
// 	return count;
// }
