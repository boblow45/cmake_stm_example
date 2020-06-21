#include "stm32f7xx_hal.h"
#include "stm32f7xx_nucleo_144_BSP.h"

#include "board_config.h"
#include "error_handling.h"
#include "globals.h"
#include "usart.h"

GPIO_TypeDef* GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT, LED3_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN};
GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {USER_BUTTON_GPIO_PORT};
const uint16_t BUTTON_PIN[BUTTONn] = {USER_BUTTON_PIN};
const uint8_t BUTTON_IRQn[BUTTONn] = {USER_BUTTON_EXTI_IRQn};

static void system_clk_config();
static void nucleo144_gpio_init(void);

void board_init(void) {
	// Enable the instruction cache
	SCB_EnableICache();
	// Enable the data cache
	SCB_EnableDCache();
	system_clk_config();
	HAL_Init();
	nucleo144_gpio_init();

	MX_USART3_UART_Init();
	HAL_UART_MspInit(&huart3);

	// config_i2c();
}

/*

*/
static void system_clk_config(void) {
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

	__HAL_RCC_PWR_CLK_ENABLE();

	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 160;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 10;
	RCC_OscInitStruct.PLL.PLLR = 5;

	if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
		_Error_Handler(__FILE__, __LINE__);

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
	   clocks dividers */
	RCC_ClkInitStruct.ClockType =
		(RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
		_Error_Handler(__FILE__, __LINE__);

	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3 | RCC_PERIPHCLK_I2C1;
	PeriphClkInitStruct.PLLSAI.PLLSAIN = 96;
	PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
	PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2;
	PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV4;
	PeriphClkInitStruct.PLLSAIDivQ = 1;
	PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
	PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
	PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
	if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	__HAL_RCC_HSI_DISABLE();
}

void nucleo144_gpio_init(void) {
	BSP_LED_Init(LED_GREEN);
	BSP_LED_Init(LED_BLUE);
	BSP_LED_Init(LED_RED);
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
}

void BSP_LED_Init(Led_TypeDef Led) {
	GPIO_InitTypeDef GPIO_InitStruct;

	/* Enable the GPIO_LED Clock */
	LEDx_GPIO_CLK_ENABLE(Led);

	/* Configure the GPIO_LED pin */
	GPIO_InitStruct.Pin = GPIO_PIN[Led];
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	HAL_GPIO_Init(GPIO_PORT[Led], &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET);
}

void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode) {
	GPIO_InitTypeDef GPIO_InitStruct;

	/* Enable the BUTTON Clock */
	BUTTONx_GPIO_CLK_ENABLE(Button);

	/* Configure Button pin as input */
	if(ButtonMode == BUTTON_MODE_GPIO) {
		GPIO_InitStruct.Pin = BUTTON_PIN[Button];
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLDOWN;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);
	}

	/* Configure Button pin as input with External interrupt */
	if(ButtonMode == BUTTON_MODE_EXTI) {
		GPIO_InitStruct.Pin = BUTTON_PIN[Button];
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
		HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);

		/* Enable and set Button EXTI Interrupt to the lowest priority */
		HAL_NVIC_SetPriority((IRQn_Type)(BUTTON_IRQn[Button]), 0x0F, 0x00);
		HAL_NVIC_EnableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
	}
}

void BSP_LED_On(Led_TypeDef Led) {
	HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_SET);
}
void BSP_LED_Off(Led_TypeDef Led) {
	HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET);
}