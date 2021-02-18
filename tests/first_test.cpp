#include <cstdint>

#include "CppUTest/TestHarness.h"

using namespace std;

TEST_GROUP(FirstTestGroup){};

TEST(FirstTestGroup, TestAdd)
{
    uint32_t x;
    x = 3;
    CHECK_EQUAL(3, x);
}