include("cmake_arm_none_eabi.cmake")
cmake_minimum_required(VERSION 3.12)

# Set the variable "This", which will be used as the project name through out this file
set(This stm_drone)

project(${This} C CXX ASM)
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

# Add directories of any header files which will be used in the project
include_directories (
                        ${CMAKE_CURRENT_LIST_DIR}/drivers/cmsis/arm
                        ${CMAKE_CURRENT_LIST_DIR}/drivers/cmsis/device
                        ${CMAKE_CURRENT_LIST_DIR}/drivers/hal/inc
                        ${CMAKE_CURRENT_LIST_DIR}/inc
)

# Options for specific architecture
set(ARCH_FLAGS "-mthumb -mcpu=cortex-m7")
set(STARTUP_DEFS "-D__STARTUP_CLEAR_BSS -D__START=main")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ARCH_FLAGS} ${STARTUP_DEFS} -Os -g -Wall -flto -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS}")

# Add indiviual assemble files
set(Asmfiles "${CMAKE_CURRENT_LIST_DIR}/startup/startup_ARMCM7.S")

set(Sources
    main.c
    "${CMAKE_CURRENT_LIST_DIR}/src/board_config.c"
    "${CMAKE_CURRENT_LIST_DIR}/src/error_handling.c"
    "${CMAKE_CURRENT_LIST_DIR}/src/system_stm32f7xx.c"
    "${CMAKE_CURRENT_LIST_DIR}/src/stm32f7xx_it.c"
    "${CMAKE_CURRENT_LIST_DIR}/src/stm32f7xx_hal_msp.c"
    "${CMAKE_CURRENT_LIST_DIR}/src/usart.c"
    "${CMAKE_CURRENT_LIST_DIR}/src/retarget.c"                 
    "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal.c"    
    "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_rcc.c"
    "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_gpio.c"
    "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_cortex.c"
    "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_dma.c"
    "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_uart.c"
    "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_i2c.c"
)

add_executable(${This} ${Sources} ${Asmfiles})