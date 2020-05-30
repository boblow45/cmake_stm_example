#include <stdint.h>

#include "i2c.h"
#include "imu.hpp"

uint8_t ADXL345::id(void) {

	uint8_t i2c_data;
	i2c_read(this->i2c_add, (uint16_t)this->dev_id, 1, &i2c_data, 1);
	return i2c_data;
}

void ADXL345::init(void) {
	uint8_t data;
	data = 0b1111; // Set the update range to 3.200 kHz
	i2c_write(this->i2c_add, (uint16_t)this->bw_rate, 1, &data, 1);
	data = 0b11 | 1 << 2; // Set the range to 16g and the left justified
	i2c_write(this->i2c_add, (uint16_t)this->data_format, 1, &data, 1);
	data = 0b1 << 3; // power up the part
	i2c_write(this->i2c_add, (uint16_t)this->power_ctl, 1, &data, 1);
}

ADXL345::ADXL345()
	: dev_id(0)
	, bw_rate(0x2C)
	, x_add(0x32)
	, y_add(0x34)
	, z_add(0x36)
	, data_format(0x31)
	, power_ctl(0x2D) {
	this->init();
};

int16_t ADXL345::x_data(void) {
	uint8_t data[2];
	i2c_read(this->i2c_add, (uint16_t)this->x_add, 1, data, 2);

	int16_t result = (data[1] << 8) | data[0];
	result /= 3;

	return result;
}

int16_t ADXL345::y_data(void) {
	uint8_t data[2];
	i2c_read(this->i2c_add, (uint16_t)this->y_add, 1, data, 2);

	int16_t result = (data[1] << 8) | data[0];
	result /= 3;

	return result;
}

int16_t ADXL345::z_data(void) {
	uint8_t data[2];
	i2c_read(this->i2c_add, (uint16_t)this->z_add, 1, data, 2);

	int16_t result = (data[1] << 8) | data[0];
	result /= 3;
	return result;
}