#ifndef __BOARD_CONFIGS_H__
#define __BOARD_CONFIGS_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f7xx_nucleo_144_BSP.h"

	void board_init(void);
	void BSP_LED_On(Led_TypeDef Led);
	void BSP_LED_Off(Led_TypeDef Led);

#ifdef __cplusplus
}
#endif

#endif // __BOARD_CONFIGS_H__
