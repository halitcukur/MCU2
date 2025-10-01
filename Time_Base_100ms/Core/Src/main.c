#include "main.h"
#include <string.h>

void SystemClockConfig(void);
void Error_Handler(void);
void TIMER11_Init(void);
void GPIO_Init(void);

TIM_HandleTypeDef htimer11;

int main(void)
{
	HAL_Init();
	SystemClockConfig();

	TIMER11_Init();
	GPIO_Init();

	HAL_TIM_Base_Start(&htimer11);

	while(1)
	{
		while(!(TIM11->SR & TIM_SR_UIF));
		TIM11->SR &= ~TIM_SR_UIF;
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
	}

	return 0;
}

void TIMER11_Init(void)
{
	htimer11.Instance = TIM11;
	htimer11.Init.Prescaler = 24;
	htimer11.Init.Period = 32000 - 1;

	if(HAL_TIM_Base_Init(&htimer11) != HAL_OK)
		Error_Handler();
}

void GPIO_Init(void)
{
	__HAL_RCC_GPIOD_CLK_ENABLE();

	GPIO_InitTypeDef ledgpio = {0};

	ledgpio.Pin = GPIO_PIN_14;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	ledgpio.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(GPIOD, &ledgpio);
}

void SystemClockConfig(void)
{

}

void Error_Handler(void)
{
	while(1);
}
