#include "main.h"
#include "stm32f4xx_it.h"

extern TIM_HandleTypeDef htimer2;
extern TIM_HandleTypeDef htimer4;

void TIM2_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htimer2);
}

void TIM4_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htimer4);
}

void NMI_Handler(void)
{
	while(1);
}

void HardFault_Handler(void)
{
	while(1);
}

void MemManage_Handler(void)
{
	while(1);
}

void BusFault_Handler(void)
{
	while(1);
}

void UsageFault_Handler(void)
{
	while(1);
}

void SVC_Handler(void)
{

}

void DebugMon_Handler(void)
{

}

void PendSV_Handler(void)
{

}

void SysTick_Handler(void)
{
	HAL_IncTick();
}
