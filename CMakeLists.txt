include("cmake_arm_none_eabi.cmake")
cmake_minimum_required(VERSION 3.12)

# Set the variable "This", which will be used as the project name through out this file
set(PROJECT_NAME stm_drone)
set(CMAKE_BUILD_TYPE RELEASE)

project(${PROJECT_NAME} ASM C CXX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

# Add directories of any header files which will be used in the project
include_directories (
    ${CMAKE_CURRENT_LIST_DIR}/drivers/cmsis/arm
    ${CMAKE_CURRENT_LIST_DIR}/drivers/cmsis/device
    ${CMAKE_CURRENT_LIST_DIR}/drivers/hal/inc
    ${CMAKE_CURRENT_LIST_DIR}/inc
    )
    
set(LDSCRIPTS "${CMAKE_CURRENT_LIST_DIR}/ldscripts/gcc.ld")

set(Sources
main.cpp

"${CMAKE_CURRENT_LIST_DIR}/startup/startup_ARMCM7.S"

"${CMAKE_CURRENT_LIST_DIR}/src/retarget.c"   

"${CMAKE_CURRENT_LIST_DIR}/src/board_config.c"
"${CMAKE_CURRENT_LIST_DIR}/src/error_handling.c"
"${CMAKE_CURRENT_LIST_DIR}/src/system_stm32f7xx.c"
"${CMAKE_CURRENT_LIST_DIR}/src/stm32f7xx_it.c"
"${CMAKE_CURRENT_LIST_DIR}/src/stm32f7xx_hal_msp.c"
"${CMAKE_CURRENT_LIST_DIR}/src/usart.c"
"${CMAKE_CURRENT_LIST_DIR}/src/i2c.c"   

"${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal.c"    
"${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_rcc.c"
"${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_gpio.c"
"${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_cortex.c"
"${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_dma.c"
"${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_uart.c"
"${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_i2c_ex.c"
"${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_i2c.c"
)

add_executable(${PROJECT_NAME} ${Sources})

target_link_libraries(${PROJECT_NAME}
                        -Wl,-Map=${PROJECT_NAME}.map
                        -T ${LDSCRIPTS}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf COMMENT "Calculating the size of the bin file")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin COMMENT "Converting ELF to binary")

set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
   "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.bin"
   "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.map"
   "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.elf")

add_custom_target(flash
COMMAND JLink -device STM32F767ZI -if SWD -speed 4000 -autoconnect 1 -CommanderScript ./j-link/flash.jlink 
DEPENDS ${PROJECT_NAME}
)
    
# enable_testing()
# # Download and unpack googletest at configure time
# configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
# execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
#     WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
# )
# execute_process(COMMAND "${CMAKE_COMMAND}" --build .
#     WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
# )
    
# # Prevent GoogleTest from overriding our compiler/linker options
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# # Add googletest directly to our build. This adds the following targets:
# # gtest, gtest_main, gmock and gmock_main
# add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
#                  "${CMAKE_BINARY_DIR}/googletest-build"
# )
# # Add the test directory as a subdirectory. This directory will contain another cmake file
# # which will build the tests 
# add_subdirectory(test)
