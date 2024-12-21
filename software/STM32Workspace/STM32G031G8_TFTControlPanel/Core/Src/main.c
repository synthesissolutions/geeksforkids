/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
#define THROTTLE_OFF		500
#define THROTTLE_FORWARD	800
#define THROTTLE_REVERSE	200

#define STEERING_STRAIGHT	500
#define STEERING_LEFT		200
#define STEERING_RIGHT		800
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint16_t pwmSteering = STEERING_STRAIGHT;
uint16_t pwmThrottle = THROTTLE_OFF;
int throttleOn = 0;
uint8_t rx_buffer[4];
uint32_t lastGoodCodeMillis = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

  HAL_UART_Receive_IT(&huart2, rx_buffer, 4);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, pwmSteering);
	  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwmThrottle);

	  HAL_Delay(20);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 15;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 500;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.Pulse = 0;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ACTIVE_SIGNAL_Pin|SOUND_2_Pin|SOUND_1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : ACTIVE_SIGNAL_Pin SOUND_2_Pin SOUND_1_Pin */
  GPIO_InitStruct.Pin = ACTIVE_SIGNAL_Pin|SOUND_2_Pin|SOUND_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : FORWARD_PAD_Pin */
  GPIO_InitStruct.Pin = FORWARD_PAD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(FORWARD_PAD_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : REVERSE_PAD_Pin */
  GPIO_InitStruct.Pin = REVERSE_PAD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(REVERSE_PAD_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RIGHT_PAD_Pin LEFT_PAD_Pin */
  GPIO_InitStruct.Pin = RIGHT_PAD_Pin|LEFT_PAD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  switch(rx_buffer[1])
  {
	  case '0':		// Middle Go Button
		  throttleOn = 0;
		  pwmThrottle = THROTTLE_OFF;
		  pwmSteering = STEERING_STRAIGHT;
		  lastGoodCodeMillis = HAL_GetTick();
		  HAL_GPIO_WritePin(GPIOA, SOUND_1_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOA, SOUND_2_Pin, GPIO_PIN_SET);
		  break;
	  case '1':		// Middle Go Button
		  throttleOn = 1;
		  pwmThrottle = THROTTLE_FORWARD;
		  pwmSteering = STEERING_STRAIGHT;
		  lastGoodCodeMillis = HAL_GetTick();
		  HAL_GPIO_WritePin(GPIOA, SOUND_1_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOA, SOUND_2_Pin, GPIO_PIN_SET);
		  break;
	  case '2':		// Left Go Button
		  throttleOn = 1;
		  pwmThrottle = THROTTLE_FORWARD;
		  pwmSteering = STEERING_LEFT;
		  lastGoodCodeMillis = HAL_GetTick();
		  HAL_GPIO_WritePin(GPIOA, SOUND_1_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOA, SOUND_2_Pin, GPIO_PIN_SET);
		  break;
	  case '3':		// Right Go Button
		  throttleOn = 1;
		  pwmThrottle = THROTTLE_FORWARD;
		  pwmSteering = STEERING_RIGHT;
		  lastGoodCodeMillis = HAL_GetTick();
		  HAL_GPIO_WritePin(GPIOA, SOUND_1_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOA, SOUND_2_Pin, GPIO_PIN_SET);
		  break;
	  case '4':		// Left Sound Button
		  throttleOn = 0;
		  pwmThrottle = THROTTLE_OFF;
		  pwmSteering = STEERING_STRAIGHT;
		  lastGoodCodeMillis = HAL_GetTick();
		  HAL_GPIO_WritePin(GPIOA, SOUND_1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOA, SOUND_2_Pin, GPIO_PIN_SET);
		  break;
	  case '5':		// Right Sound Button
		  throttleOn = 0;
		  pwmThrottle = THROTTLE_OFF;
		  pwmSteering = STEERING_STRAIGHT;
		  lastGoodCodeMillis = HAL_GetTick();
		  HAL_GPIO_WritePin(GPIOA, SOUND_1_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOA, SOUND_2_Pin, GPIO_PIN_RESET);
		  break;
	  default:
		  // For some reason we are getting a bunch of bad data interspersed with good data
		  // so wait a bit before turning everything off
		  if (HAL_GetTick() - lastGoodCodeMillis > 50)
		  {
			  throttleOn = 0;
			  pwmThrottle = THROTTLE_OFF;
			  pwmSteering = STEERING_STRAIGHT;
			  HAL_GPIO_WritePin(GPIOA, SOUND_1_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOA, SOUND_2_Pin, GPIO_PIN_SET);
		  }
  }

  HAL_UART_Receive_IT(&huart2, rx_buffer, 4);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
