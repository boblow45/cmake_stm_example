#include <stdint.h>

#include "i2c.hpp"
#include "imu.hpp"

ADXL345::ADXL345(I2C& i2c_interface)
	: hi2c(i2c_interface) {
	this->init();
}

uint8_t ADXL345::id(void) {

	uint8_t i2c_data;
	this->hi2c.read(this->i2c_add, this->dev_id, 1, &i2c_data, 1);
	return i2c_data;
}

void ADXL345::init(void) {
	uint8_t data;
	data = 0b1111; // Set the update range to 3.200 kHz
	this->hi2c.write(this->i2c_add, this->bw_rate, 1, &data, 1);
	data = 0b11 | 1 << 2; // Set the range to 16g and the left justified
	this->hi2c.write(this->i2c_add, this->data_format, 1, &data, 1);
	data = 0b1 << 3; // power up the part
	this->hi2c.write(this->i2c_add, this->power_ctl, 1, &data, 1);
}

void ADXL345::data(adxl345_data* data) {
	uint8_t i2c_data[6];
	this->hi2c.read(
		this->i2c_add, this->x_add, 1, i2c_data, sizeof(i2c_data) / sizeof(i2c_data[0]));

	data->x = *((int16_t*)i2c_data) / 8;
	data->y = *((int16_t*)(i2c_data + 2)) / 8;
	data->z = *((int16_t*)(i2c_data + 4)) / 8;
}

L3G4200D::L3G4200D(I2C& i2c_interface)
	: hi2c(i2c_interface) {
	this->init();
}

void L3G4200D::init(void) {
	uint8_t data;
	data = 0xF; // power up the part and enable all the axis and set the update rate to max
	this->hi2c.write(this->i2c_add, this->ctrl_reg1, 1, &data, 1);
	data = 1 << 6;
	this->hi2c.write(this->i2c_add, this->ctrl_reg4, 1, &data, 1);
}

uint8_t L3G4200D::id(void) {
	uint8_t i2c_data;
	this->hi2c.read(this->i2c_add, this->dev_id, 1, &i2c_data, 1);
	return i2c_data;
}

void L3G4200D::data(l3g4300d_data* data) {
	uint8_t i2c_data[6];
	this->hi2c.read(
		this->i2c_add, this->data_add, 1, i2c_data, sizeof(i2c_data) / sizeof(i2c_data[0]));

	data->x = *((int16_t*)i2c_data);
	data->y = *((int16_t*)(i2c_data + 2));
	data->z = *((int16_t*)(i2c_data + 4));
}

HMC5883L::HMC5883L(I2C& i2c_interface)
	: hi2c(i2c_interface) {
	uint8_t data;
	data = 0b110 << 2;
	this->hi2c.write(this->i2c_add, this->con_reg_a, 1, &data, 1);
	data = 0b001 << 5;
	this->hi2c.write(this->i2c_add, this->con_reg_b, 1, &data, 1);
	data = 0;
	this->hi2c.write(this->i2c_add, this->mode_reg, 1, &data, 1);
}

uint8_t HMC5883L::id(void) {
	uint8_t i2c_data;
	this->hi2c.read(this->i2c_add, this->dev_id, 1, &i2c_data, 1);
	return i2c_data;
}

void HMC5883L::data(hmc5883l_data* data) {
	uint8_t i2c_data[6];
	this->hi2c.read(
		this->i2c_add, this->data_add, 1, i2c_data, sizeof(i2c_data) / sizeof(i2c_data[0]));

	data->x = *((int16_t*)i2c_data);
	data->y = *((int16_t*)(i2c_data + 2));
	data->z = *((int16_t*)(i2c_data + 4));
}