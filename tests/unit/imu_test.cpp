#include <cstdint>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "i2c.hpp"
#include "imu.hpp"

using namespace std;

TEST_GROUP(IMUTest){

	// clang-format off
	void teardown(){
		mock().clear();
	}
// clang-format on
}
;

TEST(IMUTest, TestAcc) {

	I2C i2c;
	ADXL345 acc(i2c);

	CHECK_EQUAL(42, acc.id());
}