#ifndef __IMU_H__
#define __IMU_H__

#include <stdint.h>
typedef struct __adxl345_data {
	int16_t x;
	int16_t y;
	int16_t z;
} adxl345_data;

class ADXL345 {

private:
	static const uint8_t i2c_add = 0x53;

	uint8_t dev_id;
	uint8_t bw_rate;
	uint8_t x_add;
	uint8_t data_format;
	uint8_t power_ctl;

public:
	ADXL345();

	uint8_t id(void);
	void init(void);
	void data(adxl345_data* data);
};

#endif
