#ifndef __STM32F7xx_HAL_I2C_H
#	define __STM32F7xx_HAL_I2C_H

#	ifdef __cplusplus
extern "C"
{
#	endif

#include <cstdint>

typedef struct __I2C_HandleTypeDef {
	uint32_t ErrorCode; 
    uint32_t AddrEventCount; 
} I2C_HandleTypeDef;


#	ifdef __cplusplus
}
#	endif

#endif /* __STM32F7xx_HAL_I2C_H */
