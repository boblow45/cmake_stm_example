cmake_minimum_required(VERSION 3.15)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING TRUE)

# Set the variable "This", which will be used as the project name through out this file
set(This stm_drone)

# State that we will be using C and C++
project(${This} C ASM)

set(CMAKE_EXECUTABLE_SUFFIX ".elf")
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER_TARGET "arm-none-eabi-g++")
set(CMAKE_ASM_COMPILER "arm-none-eabi-as")
set(CMAKE_OBJCOPY "arm-none-eabi-objcopy")

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# Options for specific architecture
set(ARCH_FLAGS "-mthumb -mcpu=cortex-m7")
set(STARTUP_DEFS "-D__STARTUP_CLEAR_BSS -D__START=main")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ARCH_FLAGS} ${STARTUP_DEFS} -Os -g -Wall -flto -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS}")

set(LDSCRIPTS "-L. -L ${CMAKE_CURRENT_LIST_DIR}/ldscripts -T nokeep.ld")
set(MAP "-Wl,-Map=main.map")
set(GC "-Wl,--gc-sections")
set(USE_NOHOST "--specs=nosys.specs")
set(USE_NANO "--specs=nano.specs")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} $(USE_NANO) $(USE_NOHOST) ${LINKSCRIPT} $(GC) $(MAP)")

# Add directories of any header files which will be used in the project
include_directories (
                        ${CMAKE_CURRENT_LIST_DIR}/drivers/cmsis/arm
                        ${CMAKE_CURRENT_LIST_DIR}/drivers/cmsis/device
                        ${CMAKE_CURRENT_LIST_DIR}/drivers/hal/inc
                        ${CMAKE_CURRENT_LIST_DIR}/inc
)

# Add indiviual assemble files
set(Asmfiles "${CMAKE_CURRENT_LIST_DIR}/startup/startup_ARMCM7.S")
# Add indiviual source files
set(Sources
    main.c
)


add_executable(${This} ${Sources} ${Asmfiles})