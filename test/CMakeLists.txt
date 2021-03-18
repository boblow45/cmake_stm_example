# Set the cmake version which the user needs in order for this to work
include(GoogleTest)
cmake_minimum_required(VERSION 3.12)

set(this Tests)

# Set the C++ Standard to use for the project.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Add indiviual source files
set(Sources
    "./unit/ExampleTests.cpp"
    "./main.cpp"
)

add_executable(${this} ${Sources})

# Link google test framework and the static lib of our code which we are about to test 
target_link_libraries(${this} PUBLIC
    gtest_main
    ${PRO_NAME}
)

# Add List of tests and the commands which need to be pasted to the test
gtest_discover_tests(${this})