#include <cstdint>

#include "CppUTest/TestHarness.h"
// #include "gmock/gmock.h"

#include "i2c.hpp"
#include "imu.hpp"

using namespace std;

TEST_GROUP(IMUTest){};

TEST(IMUTest, TestAcc) {

	I2C i2c;
	ADXL345 acc(i2c);

	CHECK_EQUAL(42, acc.id());
}