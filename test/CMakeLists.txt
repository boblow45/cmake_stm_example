# Set the cmake version which the user needs in order for this to work

cmake_minimum_required(VERSION 3.12)

execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)
    
# Prevent GoogleTest from overriding our compiler/linker options
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds the following targets:
# gtest, gtest_main, gmock and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build"
)

set(this ExampleTests)

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
    ${PROJECT_NAME}
)

# Add List of tests and the commands which need to be pasted to the test
add_test(
    NAME ${this}
    COMMAND ${this}
)
