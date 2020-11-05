
set(HOST_ASM_COMPILER "gcc")
set(HOST_C_COMPILER    "gcc")
set(HOST_CXX_COMPILER  "g++")
set(CURRENT_COMPILER  "NATIVE")
set(HOST_C_FLAGS  "")


macro(use_host_compiler)
if (${CURRENT_COMPILER} STREQUAL "NATIVE")
  # Save current native flags
  set(NATIVE_C_FLAGS ${CMAKE_C_FLAGS} CACHE STRING "GCC flags for the native compiler." FORCE)

  # Change compiler
  set(CMAKE_SYSTEM_NAME ${CMAKE_HOST_SYSTEM_NAME})
  set(CMAKE_SYSTEM_PROCESSOR ${CMAKE_HOST_SYSTEM_PROCESSOR})
  set(CMAKE_ASM_COMPILER ${HOST_ASM_COMPILER})
  set(CMAKE_C_COMPILER ${HOST_C_COMPILER})
  set(CMAKE_CXX_COMPILER ${HOST_CXX_COMPILER})
  set(CMAKE_C_FLAGS ${HOST_C_FLAGS})
  set(CURRENT_COMPILER "HOST" CACHE STRING "Which compiler we are using." FORCE)
endif()
endmacro()


# Set the cmake version which the user needs in order for this to work
cmake_minimum_required(VERSION 3.12)
use_host_compiler()

set(this ExampleTests)
set(CMAKE_EXECUTABLE_SUFFIX ".bin")

# set(CMAKE_ASM_COMPILER    "/usr/bin/gcc")
# set(CMAKE_C_COMPILER    "/usr/bin/gcc")
# set(CMAKE_CXX_COMPILER  "/usr/bin/g++")

# Set the C++ Standard to use for the project.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

##
# Build dependencies (googletest)
# 
# Google test build for bare metal without OS. 
# This means the following infrastructre is not available.
# - POSIX reg. exp. (GTEST_HAS_POSIX_RE=0), 
# - POSIX threads (GTEST_HAS_PTHREAD=0), 
# - POSIX OS with the memory management (GTEST_HAS_DEATH_TEST=0),
# - POSIX IPC (GTEST_HAS_STREAM_REDIRECTION=0),
# - POSIX OS with the file system (GTEST_OS_NONE should be selected
#    after gtest is patched with gtest-filepath.cc.patch).
#


set(GTEST_OPTIONS       "-DGTEST_HAS_POSIX_RE=0 -DGTEST_HAS_PTHREAD=0 -DGTEST_HAS_DEATH_TEST=0 -DGTEST_HAS_STREAM_REDIRECTION=0 -DGTEST_OS_NONE")
set(CMAKE_C_FLAGS       "${CMAKE_C_FLAGS} ${GTEST_OPTIONS} " CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS     "${CMAKE_CXX_FLAGS} ${GTEST_OPTIONS} " CACHE INTERNAL "")

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)
    
# Prevent GoogleTest from overriding our compiler/linker options
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds the following targets:
# gtest, gtest_main, gmock and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build"
)
# Add the test directory as a subdirectory. This directory will contain another cmake file
# which will build the tests 

# Add indiviual source files
set(Sources
    "./unit/ExampleTests.cpp"
    "./main.cpp"
)

add_executable(${this} ${Sources})

# Link google test framework and the static lib of our code which we are about to test 
target_link_libraries(${this} PUBLIC
    gtest_main
    Example
)

# Add List of tests and the commands which need to be pasted to the test
add_test(
    NAME ${this}
    COMMAND ${this}
)