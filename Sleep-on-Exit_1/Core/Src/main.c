/* Includes -------------------------------------------------------------*/
#include "main.h"
#include <string.h>
#include <stdio.h>

/* Private variables ----------------------------------------------------*/
UART_HandleTypeDef huart2;
TIM_HandleTypeDef htimer2;

char *msg = "halit cukur\r\n";

/* Private function prototypes ------------------------------------------*/
void SystemClockConfig(void);
void UART2_Init(void);
void TIM2_Init(void);
void Error_Handler(void);
void GPIO_Init(void);
void printClockInfo(void);

int main(void)
{
	HAL_Init();
	SystemClockConfig();
	UART2_Init();
	TIM2_Init();
	GPIO_Init();

	TIM2->SR = 0;

	if(HAL_TIM_Base_Start_IT(&htimer2) != HAL_OK)
		Error_Handler();

	while(1);

	return 0;
}

void SystemClockConfig(void)
{
	RCC_OscInitTypeDef osc_init = {0};

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState = RCC_HSE_ON;
	osc_init.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	osc_init.PLL.PLLM = 8;
	osc_init.PLL.PLLN = 200;
	osc_init.PLL.PLLP = RCC_PLLP_DIV4;

	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK)
		Error_Handler();

	RCC_ClkInitTypeDef clk_init = {0};

	clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
						RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
	clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

	if(HAL_RCC_ClockConfig(&clk_init, FLASH_ACR_LATENCY_1WS) != HAL_OK)
		Error_Handler();

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void UART2_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 9600;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;

	if(HAL_UART_Init(&huart2) != HAL_OK)
		Error_Handler();
}

void TIM2_Init(void)
{
	htimer2.Instance = TIM2;
	htimer2.Init.Prescaler = 4999;
	htimer2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htimer2.Init.Period = 99;
	htimer2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htimer2.Init.RepetitionCounter = 0;
	htimer2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	if(HAL_TIM_Base_Init(&htimer2) != HAL_OK)
		Error_Handler();
}

void Error_Handler(void)
{
	while(1);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	printClockInfo();
}

void GPIO_Init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef gpio_init = {0};

	gpio_init.Pin = GPIO_PIN_1;
	gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init.Pull = GPIO_NOPULL;
	gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(GPIOA, &gpio_init);
}

void printClockInfo(void)
{
	char msg[100];

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "SYSCLK: %lu Hz\r\n", HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "HCLK: %lu Hz\r\n", HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "PCLK1: %lu Hz\r\n", HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "PCLK2: %lu Hz\r\n\n", HAL_RCC_GetPCLK2Freq());
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);
}
