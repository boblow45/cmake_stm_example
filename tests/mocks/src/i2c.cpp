
/* Includes ------------------------------------------------------------------*/
#include "i2c.hpp"
#include "stm32f7xx_hal.h"

I2C::I2C(void) { }

void I2C::write(
	uint16_t device_add, uint16_t mem_add, uint16_t mem_add_size, uint8_t* data, uint16_t size) {
	*data = 42;
	return;
}

void I2C::read(
	uint16_t device_add, uint16_t mem_add, uint16_t mem_add_size, uint8_t* data, uint16_t size) {
	*data = 42;
	return;
}
