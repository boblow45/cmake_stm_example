#ifndef __IMU_H__
#define __IMU_H__

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

class ADXL345 {

private:
	static const uint8_t i2c_add = 0x53;

	static const uint8_t dev_id = 0;
	static const uint8_t bw_rate = 0x2C;
	static const uint8_t x_add = 0x32;
	static const uint8_t data_format = 0x31;
	static const uint8_t power_ctl = 0x2D;

public:
	ADXL345();

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

public:
	L3G4200D();

	uint8_t id(void);
	void init(void);
	void data(l3g4300d_data* data);
};

#endif
