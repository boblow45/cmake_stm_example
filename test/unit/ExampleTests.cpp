
extern "C"
{ }

#include <gtest/gtest.h>

TEST(ExampleTests, MAC) {
	int x = 43;
	int y = 16;
	int sum = 100;
	int oldSum = sum;
	int expectedNewSum = oldSum + x * y;

	EXPECT_EQ(sum, oldSum);
}