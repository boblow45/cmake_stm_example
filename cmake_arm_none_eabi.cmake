set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_TRY_COMPILE_TARGET_TYPE   STATIC_LIBRARY)
set(CMAKE_AR            "arm-none-eabi-ar")
set(CMAKE_ASM_COMPILER  "arm-none-eabi-gcc")
set(CMAKE_C_COMPILER    "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER  "arm-none-eabi-g++")
set(CMAKE_OBJCOPY       "arm-none-eabi-objcopy")
set(CMAKE_RANLIB        "arm-none-eabi-ranlib")
set(CMAKE_SIZE          "arm-none-eabi-size")
set(CMAKE_STRIP         "arm-none-eabi-strip")

# Set compiler to maximum optimization and remove all debug code from the compiled file 
set(CMAKE_C_FLAGS_DEBUG     "-g -O0" CACHE INTERNAL "")
set(CMAKE_C_FLAGS_RELEASE   "-Os" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_C_FLAGS_DEBUG}" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}" CACHE INTERNAL "")

# Options for specific architecture
set(STARTUP_DEFS "-D__STARTUP_CLEAR_BSS -D__START=main")
add_definitions(${STARTUP_DEFS})

# Options for specific architecture
set(ARCH_FLAGS          "-mthumb -mcpu=cortex-m7 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp")
set(EXTRA_OPTIONS       "-Wall -Wextra")
set(CMAKE_C_FLAGS       "${CMAKE_C_FLAGS} ${ARCH_FLAGS} ${EXTRA_OPTIONS} -fdata-sections -ffunction-sections -fno-builtin" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS     "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -fno-exceptions -fno-unwind-tables" CACHE INTERNAL "")

set(CMAKE_EXE_LINKER_FLAGS "--specs=nano.specs -Wl,--gc-sections --specs=nosys.specs" CACHE INTERNAL "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
