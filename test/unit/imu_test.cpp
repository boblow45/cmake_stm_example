#include "i2c.hpp"
#include "imu.hpp"

extern "C"
{ }

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <cstdint> // include this header for uint64_t

TEST(IMUTest, TestAcc) {
	I2C i2c;
	ADXL345 acc(i2c);

	EXPECT_EQ(1, 1);
}