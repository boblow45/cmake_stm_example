#ifndef __STM32F7xx_HAL_H
#define __STM32F7xx_HAL_H

#include <cstdint>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct __I2C_HandleTypeDef {

		uint8_t* pBuffPtr; /*!< Pointer to I2C transfer buffer            */

		uint16_t XferSize; /*!< I2C transfer size                         */

		volatile uint16_t XferCount; /*!< I2C transfer counter                      */

		volatile uint32_t XferOptions; /*!< I2C sequantial transfer options, this parameter can
                                                  be a value of @ref I2C_XFEROPTIONS */

		volatile uint32_t PreviousState; /*!< I2C communication Previous state          */

		volatile uint32_t ErrorCode; /*!< I2C Error code                            */

		volatile uint32_t AddrEventCount; /*!< I2C Address Event counter                 */
	} I2C_HandleTypeDef;

#ifdef __cplusplus
}
#endif

#endif /* __STM32F7xx_HAL_H */