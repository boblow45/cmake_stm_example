#ifndef __IMU_H__
#define __IMU_H__

#include "i2c.hpp"
#include <stdint.h>

typedef struct __adxl345_data {
	int16_t x;
	int16_t y;
	int16_t z;
} adxl345_data;

typedef struct __l3g4300d_data {
	int16_t x;
	int16_t y;
	int16_t z;
} l3g4300d_data;

typedef struct __hmc5883l_data {
	int16_t x;
	int16_t y;
	int16_t z;
} hmc5883l_data;

class ADXL345 {

private:
	static const uint8_t i2c_add = 0x53;

	static const uint8_t dev_id = 0;
	static const uint8_t bw_rate = 0x2C;
	static const uint8_t x_add = 0x32;
	static const uint8_t data_format = 0x31;
	static const uint8_t power_ctl = 0x2D;

	I2C& hi2c;

public:
	ADXL345(I2C& i2c_interface);

	uint8_t id(void);
	void init(void);
	void data(adxl345_data* data);
};

class L3G4200D {
private:
	static const uint8_t i2c_add = 0x69;

	static const uint8_t dev_id = 0xF;
	static const uint8_t ctrl_reg1 = 0x20;
	static const uint8_t ctrl_reg4 = 0x23;
	static const uint8_t data_add = 0x28;

	I2C& hi2c;

public:
	L3G4200D(I2C& i2c_interface);

	uint8_t id(void);
	void init(void);
	void data(l3g4300d_data* data);
};

class HMC5883L {
private:
	static const uint8_t i2c_add = 0x1e;

	static const uint8_t con_reg_a = 0x0;
	static const uint8_t con_reg_b = 0x1;
	static const uint8_t mode_reg = 0x2;
	static const uint8_t dev_id = 0x0A;

	static const uint8_t data_add = 0x03;

	uint8_t i2c_buffer[6];

	I2C& hi2c;

public:
	HMC5883L(I2C& i2c_interface);

	uint8_t id(void);
	void init(void);
	void data(hmc5883l_data* data);
};

#endif
