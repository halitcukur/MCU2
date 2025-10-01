/*
 * it.c
 *
 *  Created on: Sep 12, 2025
 *      Author: halit
 */

#include "main.h"

extern TIM_HandleTypeDef htimer11;

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htimer11);
}
