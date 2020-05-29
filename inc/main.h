#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

	// #include "stm32f7xx_hal.h"
	// #include "stm32f7xx_nucleo_144_BSP.h"

	// #include "board_config.h"
	// #include "globals.h"
	// #include "usart.h"

	extern volatile unsigned int ticks;

	// class I2CBus {

	// private:
	// 	I2C_HandleTypeDef* interface;
	// 	const static unsigned int timeout = 1000;

	// public:
	// 	I2CBus(I2C_HandleTypeDef* interface);

	// 	void write(uint16_t device_add, uint8_t* data, uint16_t data_size);
	// 	void read(uint16_t device_add,
	// 		uint8_t* reg_add,
	// 		uint8_t bytes_in_add,
	// 		uint16_t bytes_to_read,
	// 		uint8_t* data);
	// };

#ifdef __cplusplus
}
#endif

#endif
