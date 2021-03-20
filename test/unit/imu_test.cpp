#include "i2c.hpp"
#include "imu.hpp"

extern "C"
{ }

#include <gtest/gtest.h>

TEST(IMUTest, TestAcc) {
	I2C i2c;
	ADXL345 acc(i2c);

	EXPECT_EQ(1, 1);
}