###############################################################################
# Default Settings
PROJECT=Blinky
.PHONY: clean
.DEFAULT_GOAL := $(PROJECT).bin
INCLUDES=-I inc -I drivers/cmsis/arm -I drivers/cmsis/device -I drivers/hal/inc  
ENTRY_POINT=main

STARTUP_DEFS=-D__STARTUP_CLEAR_BSS -D__START=main -D__NO_SYSTEM_INIT
BASE=./

# Options for specific architecture
CORTEX_M=7
CORE=CM$(CORTEX_M)
ARCH_FLAGS=-mthumb -mcpu=cortex-m$(CORTEX_M)
##############################################################################
# Tool-Chain
CC=arm-none-eabi-gcc
CXX=arm-none-eabi-g++
OBJDUMP=arm-none-eabi-objdump
OBJCOPY=arm-none-eabi-objcopy
SIZE=arm-none-eabi-size
# Compiler & Linker

# -Os -flto -ffunction-sections -fdata-sections to compile for code size
CFLAGS=$(ARCH_FLAGS) $(STARTUP_DEFS) $(INCLUDES) -Os -g -flto -ffunction-sections -fdata-sections 
CXXFLAGS=$(CFLAGS)

# Link for code size
GC=-Wl,--gc-sections
LDSCRIPTS=-L. -L$(BASE)/ldscripts -T nokeep.ld
MAP=-Wl,-Map=$(ENTRY_POINT).map

# Use newlib-nano. To disable it, specify USE_NANO=
USE_NANO=--specs=nano.specs

# Use seimhosting or not
USE_SEMIHOST=--specs=rdimon.specs
USE_NOHOST=--specs=nosys.specs

# Linker Settings
LFLAGS=$(USE_NANO) $(USE_NOHOST) $(LDSCRIPTS) $(GC) $(MAP)
# LFLAGS= $(USE_NOHOST) $(LDSCRIPTS) $(GC) $(MAP)

###############################################################################
# Global Objects
OBJECTS += main.o 

OBJECTS += startup/startup_ARMCM7.o

OBJECTS += src/board_config.o
OBJECTS += src/error_handling.o
OBJECTS += src/system_stm32f7xx.o
OBJECTS += src/stm32f7xx_it.o
OBJECTS += src/stm32f7xx_hal_msp.o
OBJECTS += src/usart.o
OBJECTS += src/retarget.o

OBJECTS += drivers/hal/src/stm32f7xx_hal.o

OBJECTS += drivers/hal/src/stm32f7xx_hal_rcc.o
OBJECTS += drivers/hal/src/stm32f7xx_hal_gpio.o
OBJECTS += drivers/hal/src/stm32f7xx_hal_cortex.o
OBJECTS += drivers/hal/src/stm32f7xx_hal_dma.o
OBJECTS += drivers/hal/src/stm32f7xx_hal_uart.o
OBJECTS += drivers/hal/src/stm32f7xx_hal_i2c.o

###############################################################################
# Source Rules
%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(PROJECT).elf: $(OBJECTS)
	$(CC) $(LFLAGS) $^ $(CFLAGS) -o $@
	$(SIZE) $@

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -O binary $< $@

clean: 
	rm -f *.elf *.map *.o *.bin
ifeq ($(OS), Windows_NT)
	
else
	find . -name '*.o' -delete
endif
	
dump: $(PROJECT).elf
	$(OBJDUMP) -D $(PROJECT).elf

flash: $(PROJECT).bin
	cp $(PROJECT).bin ./j-link/$(PROJECT).bin
	JLink -device STM32F767ZI -if SWD -speed 4000 -autoconnect 1 -CommanderScript ./j-link/flash.jlink