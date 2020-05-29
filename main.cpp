#include <stdio.h>

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_i2c.h"
#include "stm32f7xx_nucleo_144_BSP.h"

#include "board_config.h"
#include "globals.h"
#include "main.h"
#include "usart.h"

// ADXL345 -> 0x53
// L3G4200D -> 0x69
// BMP085 -> 0x77
// HMC5883L -> 0x1e

class I2CBus {
private:
	I2C_HandleTypeDef* interface;
	const static unsigned int timeout = 1000;

public:
	I2CBus(I2C_HandleTypeDef* i2c_bus)
		: interface(i2c_bus) { }

	void write(uint16_t device_add, uint8_t* data, uint16_t data_size) {
		HAL_I2C_Master_Transmit(this->interface, device_add << 1, data, data_size, this->timeout);
	}

	void read(uint16_t device_add,
		uint8_t* reg_add,
		uint8_t bytes_in_add,
		uint16_t bytes_to_read,
		uint8_t* data) {
		HAL_I2C_Master_Transmit(
			this->interface, device_add << 1, reg_add, bytes_in_add, this->timeout);
		HAL_I2C_Master_Receive(
			this->interface, device_add << 1, data, bytes_to_read, this->timeout);
	}
};

int main(void) {
	uint32_t curr = 0;
	board_init();
	printf("Hello World!\n");

	I2CBus i2c_inter(&hi2c1);

	uint8_t acc_id_add = 0;
	uint8_t acc_id;
	while(1) {
		/* Blink Red LED */

		i2c_inter.read(0x53, &acc_id_add, 1, 1, &acc_id);
		printf("Acc ID: %X\n", acc_id);
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

// void I2CBus::write(uint16_t device_add, uint8_t* data, uint16_t data_size) {
// 	HAL_I2C_Master_Transmit(this->interface, device_add << 1, data, data_size, this->timeout);
// }
// void I2CBus::read(uint16_t device_add,
// 	uint8_t* reg_add,
// 	uint8_t bytes_in_add,
// 	uint16_t bytes_to_read,
// 	uint8_t* data) {
// 	HAL_I2C_Master_Transmit(this->interface, device_add << 1, reg_add, bytes_in_add, this->timeout);
// 	HAL_I2C_Master_Receive(this->interface, device_add << 1, data, bytes_to_read, this->timeout);
// }
