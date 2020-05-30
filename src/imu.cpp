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

void ADXL345::data(adxl345_data* data) {
	uint8_t i2c_data[6];
	i2c_read(
		this->i2c_add, (uint16_t)this->x_add, 1, i2c_data, sizeof(i2c_data) / sizeof(i2c_data[0]));

	data->x = (i2c_data[1] << 8) | i2c_data[0];
	data->x /= 8;
	data->y = (i2c_data[3] << 8) | i2c_data[2];
	data->y /= 8;
	data->z = (i2c_data[5] << 8) | i2c_data[4];
	data->z /= 8;
}

ADXL345::ADXL345()
	: dev_id(0)
	, bw_rate(0x2C)
	, x_add(0x32)
	, data_format(0x31)
	, power_ctl(0x2D) {
	this->init();
};
