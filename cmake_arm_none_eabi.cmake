set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

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

set(CMAKE_EXE_LINKER_FLAGS "--specs=nano.specs -Wl,--gc-sections --specs=nosys.specs" CACHE INTERNAL "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# set(CMAKE_SYSTEM_NAME Generic)
# set(CMAKE_SYSTEM_PROCESSOR arm)

# # set(CMAKE_TRY_COMPILE_TARGET_TYPE   STATIC_LIBRARY)
# set(CMAKE_AR            "arm-none-eabi-ar")
# set(CMAKE_ASM_COMPILER  "arm-none-eabi-gcc")
# set(CMAKE_C_COMPILER    "arm-none-eabi-gcc")
# set(CMAKE_CXX_COMPILER  "arm-none-eabi-g++")
# set(CMAKE_OBJCOPY       "arm-none-eabi-objcopy")
# set(CMAKE_RANLIB        "arm-none-eabi-ranlib")
# set(CMAKE_SIZE          "arm-none-eabi-size")
# set(CMAKE_STRIP         "arm-none-eabi-strip")

# set(CMAKE_C_FLAGS          "${CMAKE_C_FLAGS} --specs=nosys.specs -fdata-sections -ffunction-sections -flto  -Wl,--gc-sections" CACHE INTERNAL "")
# set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -fno-exceptions" CACHE INTERNAL "")

# set(CMAKE_C_FLAGS_DEBUG     "-g -O0" CACHE INTERNAL "")
# set(CMAKE_C_FLAGS_RELEASE   "-Os" CACHE INTERNAL "")
# set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_C_FLAGS_DEBUG}" CACHE INTERNAL "")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}" CACHE INTERNAL "")

# set(CMAKE_EXE_LINKER_FLAGS  "--specs=nano.specs -Wl,--gc-sections --specs=nosys.specs" CACHE INTERNAL "")

# set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)