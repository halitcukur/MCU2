#include "main.h"
#include "stm32f4xx_hal_cortex.h"

void HAL_MspInit(void)
{
	/* SYSCFG ve PWR saatlerini etkinleştir */
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();

	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	SCB->SHCSR |= (0x7 << 16);

	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef uart_gpio = {0};

	uart_gpio.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	uart_gpio.Mode = GPIO_MODE_AF_PP;
	uart_gpio.Pull = GPIO_NOPULL;
	uart_gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	uart_gpio.Alternate = GPIO_AF7_USART2;

	HAL_GPIO_Init(GPIOA, &uart_gpio);

	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	__HAL_RCC_TIM2_CLK_ENABLE();

	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
}
