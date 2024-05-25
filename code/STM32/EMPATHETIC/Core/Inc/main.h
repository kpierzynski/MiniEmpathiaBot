/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Enkoder_silnika_2_Hall_1_Pin GPIO_PIN_0
#define Enkoder_silnika_2_Hall_1_GPIO_Port GPIOA
#define Enkoder_silnika_2_Hall_2_Pin GPIO_PIN_1
#define Enkoder_silnika_2_Hall_2_GPIO_Port GPIOA
#define DEBUG_Pin GPIO_PIN_3
#define DEBUG_GPIO_Port GPIOA
#define VL_MIDDLE_XSHUT_Pin GPIO_PIN_5
#define VL_MIDDLE_XSHUT_GPIO_Port GPIOC
#define nFAULT_Pin GPIO_PIN_13
#define nFAULT_GPIO_Port GPIOB
#define nSleep_Pin GPIO_PIN_14
#define nSleep_GPIO_Port GPIOB
#define Enkoder_silnika_1_Hall_1_Pin GPIO_PIN_6
#define Enkoder_silnika_1_Hall_1_GPIO_Port GPIOB
#define Enkoder_silnika_1_Hall_2_Pin GPIO_PIN_7
#define Enkoder_silnika_1_Hall_2_GPIO_Port GPIOB
#define VL_INT_Pin GPIO_PIN_8
#define VL_INT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
