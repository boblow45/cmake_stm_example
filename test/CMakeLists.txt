# Set the cmake version which the user needs in order for this to work
include(GoogleTest)
cmake_minimum_required(VERSION 3.12)

set(this Tests)

# Set the C++ Standard to use for the project.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories (
                        "./mocks/inc"
                        "./../drivers/cmsis/arm"
                        "./../drivers/cmsis/device"
                        "./../drivers/hal/inc"
                        "./../inc"
)

set(Headers
    "./mocks/inc/stm32f7xx_hal.h"
    "./../inc/i2c.hpp"
    "./../inc/imu.hpp"
    )

# Add indiviual source files
set(Sources
    "./unit/imu_test.cpp"
    "./../src/imu.cpp"
    "./mocks/src/i2c.cpp"

    "./main.cpp"
)

add_executable(${this} ${Sources} ${Headers})

# Link google test framework and the static lib of our code which we are about to test 
target_link_libraries(${this} PUBLIC
    gtest
    gmock_main
    ${PRO_NAME}
)

# Add List of tests and the commands which need to be pasted to the test
gtest_discover_tests(${this})