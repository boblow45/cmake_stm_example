cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME stm_drone)

project(${PROJECT_NAME} ASM C CXX) 
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

if (CMAKE_CROSSCOMPILING)
    include("cmake_arm_none_eabi.cmake")

    # Set the variable "This", which will be used as the project name through out this file
    set(CMAKE_EXECUTABLE_SUFFIX ".elf")

    # Add directories of any header files which will be used in the project
    include_directories (
        ${CMAKE_CURRENT_LIST_DIR}/drivers/cmsis/arm
        ${CMAKE_CURRENT_LIST_DIR}/drivers/cmsis/device
        ${CMAKE_CURRENT_LIST_DIR}/drivers/hal/inc
        ${CMAKE_CURRENT_LIST_DIR}/inc
        ${CMAKE_CURRENT_LIST_DIR}/middleware/FreeRTOS/Source/include
        ${CMAKE_CURRENT_LIST_DIR}/middleware/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1
        )
        
    set(LDSCRIPTS "${CMAKE_CURRENT_LIST_DIR}/ldscripts/gcc.ld")

    set(Sources
    
        "${CMAKE_CURRENT_LIST_DIR}/startup/startup_ARMCM7.S"

        "${CMAKE_CURRENT_LIST_DIR}/src/main.cpp"

        "${CMAKE_CURRENT_LIST_DIR}/src/board_config.c"
        "${CMAKE_CURRENT_LIST_DIR}/src/error_handling.c"
        "${CMAKE_CURRENT_LIST_DIR}/src/system_stm32f7xx.c"
        "${CMAKE_CURRENT_LIST_DIR}/src/stm32f7xx_it.c"
        "${CMAKE_CURRENT_LIST_DIR}/src/stm32f7xx_hal_msp.c"
        "${CMAKE_CURRENT_LIST_DIR}/src/usart.c"
        "${CMAKE_CURRENT_LIST_DIR}/src/adc.c"            
    
    
        "${CMAKE_CURRENT_LIST_DIR}/src/i2c.cpp"   
        "${CMAKE_CURRENT_LIST_DIR}/src/imu.cpp"   
        "${CMAKE_CURRENT_LIST_DIR}/src/pwm.cpp"   
        
        "${CMAKE_CURRENT_LIST_DIR}/middleware/FreeRTOS/Source/tasks.c"
        "${CMAKE_CURRENT_LIST_DIR}/middleware/FreeRTOS/Source/queue.c"
        "${CMAKE_CURRENT_LIST_DIR}/middleware/FreeRTOS/Source/list.c"
        "${CMAKE_CURRENT_LIST_DIR}/middleware/FreeRTOS/Source/timers.c"
        "${CMAKE_CURRENT_LIST_DIR}/middleware/FreeRTOS/Source/event_groups.c"
        "${CMAKE_CURRENT_LIST_DIR}/middleware/FreeRTOS/Source/portable/MemMang/heap_2.c"
        "${CMAKE_CURRENT_LIST_DIR}/middleware/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/port.c"

        "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal.c"    
        "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_rcc.c"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_rcc_ex.c"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_gpio.c"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_cortex.c"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_dma.c"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_uart.c"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_i2c_ex.c"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_i2c.c"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_adc.c"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_tim.c"
        "${CMAKE_CURRENT_LIST_DIR}/drivers/hal/src/stm32f7xx_hal_tim_ex.c"
    )

    add_executable(${PROJECT_NAME} ${Sources})

    target_link_libraries(${PROJECT_NAME}
                            -Wl,-Map=${PROJECT_NAME}.map
                            -T ${LDSCRIPTS}
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf COMMENT "Calculating the size of the bin file")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin COMMENT "Converting ELF to binary")

    add_custom_target(flash
    COMMAND JLinkExe -device STM32F767ZI -if SWD -speed 4000 -autoconnect 1 -CommanderScript ${CMAKE_CURRENT_LIST_DIR}/j-link/flash.jlink 
    DEPENDS ${PROJECT_NAME}
    )
else()

    # Download and unpack googletest at configure time
    configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
    execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
    )
    execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
    )

    # Prevent GoogleTest from overriding our compiler/linker options
    # when building with Visual Studio
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This adds the following targets:
    # gtest, gtest_main, gmock and gmock_main
    add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                    "${CMAKE_BINARY_DIR}/googletest-build"
    )

    # The gtest/gmock targets carry header search path dependencies
    # automatically when using CMake 2.8.11 or later. Otherwise we
    # have to add them here ourselves.
    if(CMAKE_VERSION VERSION_LESS 2.8.11)
        include_directories("${gtest_SOURCE_DIR}/include"
                            "${gmock_SOURCE_DIR}/include"
        )
    endif()

    # Set the compiler to the strictest mode, enable all warnings and make all warnings errors
    # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
    # Force all libs to be staticly linked instead of dynamicly linked 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -g")
    # Set compiler to maximum optimization and remove all debug code from the compiled file
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -s -DNDEBUG") 

    set(CMAKE_POSITION_INDEPENDENT_CODE ON)

    include_directories (
                        "./inc"
                        "./src"
    )

    set(Headers
        "${CMAKE_CURRENT_LIST_DIR}/inc/defines.h"
        "${CMAKE_CURRENT_LIST_DIR}/inc/circular_buffer.h"
    )

    set(Sources
        "${CMAKE_CURRENT_LIST_DIR}/src/circular_buffer.c"
        
    )

    add_library(${PROJECT_NAME} STATIC ${Sources} ${Headers})
    enable_testing()


    # Add the test directory as a subdirectory. This directory will contain another cmake file
    # which will build the tests 
    add_subdirectory(test)
endif()