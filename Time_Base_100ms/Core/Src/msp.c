#include "main.h"
#include "stm32f4xx_hal_cortex.h"

void HAL_MspInit(void)
{
	// Here we will do low level processor specific inits.

	// 1. Set up the priority grouping of the ARM Cortex Mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	// 2. Enable the required system exceptions of the ARM Cortex Mx processor
	SCB->SHCSR |= (0x7 << 16);   // UsageFault, BusFault and MemManage system exceptions

	// 3. Configure the priority for the system exceptions
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	__HAL_RCC_TIM11_CLK_ENABLE();

	HAL_NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
	HAL_NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, 15, 0);
}
