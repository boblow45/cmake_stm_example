#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "i2c.hpp"
#include "imu.hpp"

const float PI = 3.141592654;

uint8_t i2c_buffer[6];

ADXL345::ADXL345(I2C& i2c_interface)
	: hi2c(i2c_interface) {
	this->init();
}

uint8_t ADXL345::id(void) {

	this->hi2c.read(this->i2c_add, this->dev_id, 1, i2c_buffer, 1);
	return i2c_buffer[0];
}

void ADXL345::init(void) {
	i2c_buffer[0] = 0b1111; // Set the update range to 3.200 kHz
	this->hi2c.write(this->i2c_add, this->bw_rate, 1, i2c_buffer, 1);
	i2c_buffer[0] = 0b11 | 1 << 2; // Set the range to 16g and the left justified
	this->hi2c.write(this->i2c_add, this->data_format, 1, i2c_buffer, 1);
	i2c_buffer[0] = 0b1 << 3; // power up the part
	this->hi2c.write(this->i2c_add, this->power_ctl, 1, i2c_buffer, 1);
}

void ADXL345::data(adxl345_data* data) {
	this->hi2c.read(this->i2c_add, this->x_add, 1, i2c_buffer, 6);

	data->x = *((int16_t*)i2c_buffer) / 8;
	data->y = *((int16_t*)(i2c_buffer + 2)) / 8;
	data->z = *((int16_t*)(i2c_buffer + 4)) / 8;
}

L3G4200D::L3G4200D(I2C& i2c_interface)
	: hi2c(i2c_interface) {
	this->init();
}

void L3G4200D::init(void) {
	i2c_buffer[0] = 0xF; // power up the part and enable all the axis and set the update rate to max
	this->hi2c.write(this->i2c_add, this->ctrl_reg1, 1, i2c_buffer, 1);
	i2c_buffer[0] = 1 << 6;
	this->hi2c.write(this->i2c_add, this->ctrl_reg4, 1, i2c_buffer, 1);
}

uint8_t L3G4200D::id(void) {
	this->hi2c.read(this->i2c_add, this->dev_id, 1, i2c_buffer, 1);
	return i2c_buffer[0];
}

void L3G4200D::data(l3g4300d_data* data) {
	this->hi2c.read(this->i2c_add, this->data_add, 1, i2c_buffer, 6);

	data->x = *((int16_t*)i2c_buffer);
	data->y = *((int16_t*)(i2c_buffer + 2));
	data->z = *((int16_t*)(i2c_buffer + 4));
}

HMC5883L::HMC5883L(I2C& i2c_interface)
	: hi2c(i2c_interface) {
	i2c_buffer[0] = 0b110 << 2;
	this->hi2c.write(this->i2c_add, this->con_reg_a, 1, i2c_buffer, 1);
	i2c_buffer[0] = 0b001 << 5;
	this->hi2c.write(this->i2c_add, this->con_reg_b, 1, i2c_buffer, 1);
	i2c_buffer[0] = 0;
	this->hi2c.write(this->i2c_add, this->mode_reg, 1, i2c_buffer, 1);
}

uint8_t HMC5883L::id(void) {
	this->hi2c.read(this->i2c_add, this->dev_id, 1, i2c_buffer, 1);
	return i2c_buffer[0];
}

void HMC5883L::data(hmc5883l_data* data) {
	this->hi2c.read(this->i2c_add, this->data_add, 1, i2c_buffer, 6);

	data->x = *((int16_t*)i2c_buffer);
	data->y = *((int16_t*)(i2c_buffer + 2));
	data->z = *((int16_t*)(i2c_buffer + 4));
}

IMU::IMU(I2C& i2c_interface)
	: accelerometer(ADXL345(i2c_interface))
	, gyroscope(L3G4200D(i2c_interface))
	, compass(HMC5883L(i2c_interface)) {
	printf("Accelerometer ID: %X\n", this->accelerometer.id());
	printf("Gyroscope ID: %X\n", this->gyroscope.id());
	printf("Compass ID: %X\n", this->compass.id());
}

void IMU::get_euler_angles(euler_angles* angles) {
	adxl345_data acc_data;
	this->accelerometer.data(&acc_data);

	angles->roll = atan2(acc_data.y, acc_data.x);
	angles->pitch = atan2(-acc_data.x, sqrt(acc_data.y * acc_data.y + acc_data.z * acc_data.z));

	angles->roll = angles->roll * 180 / PI;
	angles->pitch = angles->pitch * 180 / PI;
}