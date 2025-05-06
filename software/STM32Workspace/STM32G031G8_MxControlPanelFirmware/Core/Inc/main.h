/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ACTIVE_SIGNAL_Pin GPIO_PIN_5
#define ACTIVE_SIGNAL_GPIO_Port GPIOA
#define RIGHT_LED_Pin GPIO_PIN_7
#define RIGHT_LED_GPIO_Port GPIOA
#define REVERSE_LED_Pin GPIO_PIN_8
#define REVERSE_LED_GPIO_Port GPIOA
#define DRIVE_LED_Pin GPIO_PIN_6
#define DRIVE_LED_GPIO_Port GPIOC
#define LEFT_LED_Pin GPIO_PIN_12
#define LEFT_LED_GPIO_Port GPIOA
#define LEFT_BUTTON_Pin GPIO_PIN_15
#define LEFT_BUTTON_GPIO_Port GPIOA
#define REVERSE_BUTTON_Pin GPIO_PIN_5
#define REVERSE_BUTTON_GPIO_Port GPIOB
#define DRIVE_BUTTON_Pin GPIO_PIN_6
#define DRIVE_BUTTON_GPIO_Port GPIOB
#define RIGHT_BUTTON_Pin GPIO_PIN_8
#define RIGHT_BUTTON_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
