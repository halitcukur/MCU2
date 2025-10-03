/*
 * it.c
 *
 *  Created on: Sep 29, 2025
 *      Author: halit
 */

#include "main.h"

extern TIM_HandleTypeDef htimer2;
extern TIM_HandleTypeDef htimer5;

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void TIM2_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htimer2);
}

void TIM5_IRQHandler(void)
{
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
	HAL_TIM_IRQHandler(&htimer5);
}
