#ifndef __IMU_H__
#define __IMU_H__

#include <stdint.h>
// #include "stm32f7xx_hal_i2c.h"

class ADXL345 {

private:
	static const uint8_t i2c_add = 0x53;

	uint8_t dev_id;
	uint8_t bw_rate;
	uint8_t x_add;
	uint8_t y_add;
	uint8_t z_add;
	uint8_t data_format;
	uint8_t power_ctl;

public:
	ADXL345();

	uint8_t id(void);
	void init(void);
	int16_t x_data(void);
	int16_t y_data(void);
	int16_t z_data(void);
};
#endif
