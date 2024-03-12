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
#include "usart.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LEFT 350
#define RIGHT 357

#define ENCODER_RESOLUTION 1000
#define PI 3.14159f
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void motor_left_forward(void) {
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, LEFT);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
}

void motor_right_forward(void) {
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, RIGHT);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
}

void motor_left_backward(void) {
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, LEFT);
}

void motor_right_backward(void) {
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, RIGHT);
}

void motor_left_stop(void) {
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
}

void motor_right_stop(void) {
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
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
	MX_TIM2_Init();
	MX_LPUART1_UART_Init();
	MX_TIM3_Init();
	MX_TIM4_Init();
	/* USER CODE BEGIN 2 */
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

	HAL_UART_Transmit(&hlpuart1, (uint8_t*) "Starting\r\n", 10, HAL_MAX_DELAY);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	HAL_GPIO_WritePin(nSleep_GPIO_Port, nSleep_Pin, GPIO_PIN_SET);

	uint32_t line_num = 0;

	uint32_t tim = HAL_GetTick();
	uint32_t flag = 0;
	uint32_t uart_report = HAL_GetTick();

	// Speed variables
	uint32_t prev_counter2 = 0;
	uint32_t prev_counter4 = 0;
	uint32_t prev_time = 0;

	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		// Speed calculation
		uint32_t current_time = HAL_GetTick();
		uint32_t time_diff = current_time - prev_time;
		uint32_t current_counter2 = __HAL_TIM_GET_COUNTER(&htim2);
		uint32_t current_counter4 = __HAL_TIM_GET_COUNTER(&htim4);

		uint32_t count_diff2 = abs(current_counter2 - prev_counter2);
		uint32_t count_diff4 = abs(current_counter4 - prev_counter4);

		float angular_displacement2 = (float) count_diff2
				* (2 * PI)/ ENCODER_RESOLUTION;
		float angular_velocity2 = angular_displacement2 / (time_diff / 1000.0f);

		float angular_displacement4 = (float) count_diff4
				* (2 * PI)/ ENCODER_RESOLUTION;
		float angular_velocity4 = angular_displacement4 / (time_diff / 1000.0f);

		prev_counter2 = current_counter2;
		prev_counter4 = current_counter4;
		prev_time = current_time;

		uint8_t data[256];
		uint32_t counter2 = __HAL_TIM_GET_COUNTER(&htim2);
		uint32_t counter4 = __HAL_TIM_GET_COUNTER(&htim4);

		uint8_t value = (
				HAL_GPIO_ReadPin(nFAULT_GPIO_Port, nFAULT_Pin) == GPIO_PIN_SET ?
						1 : 0);

		if (HAL_GetTick() - tim > 1000) {
			if (flag) {
				motor_right_forward();
				motor_left_forward();
			} else {
				motor_right_stop();
				motor_left_stop();
			}

			flag ^= 1;
			tim = HAL_GetTick();
		}

		if (HAL_GetTick() - uart_report > 100) {
			uint8_t len =
					sprintf((char*) data,
							"%ld: Hello World! Encoder2: %ld, Encoder4: %ld, nFault: %d, speed2: %f, speed4: %f, time_diff: %ld, cnt_diff2: %ld, cnt_diff4: %ld\r\n",
							line_num++, counter2, counter4, value,
							angular_velocity2, angular_velocity4, time_diff,
							count_diff2, count_diff4);
			HAL_UART_Transmit(&hlpuart1, data, len, HAL_MAX_DELAY);

			uart_report = HAL_GetTick();
		}

		char ch = 0;
		HAL_UART_Receive(&hlpuart1, (uint8_t*) &ch, 1, 10);

		switch (ch) {
		case 'w':
			motor_right_forward();
			motor_left_forward();
			break;

		case 'd':
			motor_left_forward();
			motor_right_backward();
			break;

		case 'a':
			motor_right_forward();
			motor_left_backward();
			break;

		case 's':
			motor_left_backward();
			motor_right_backward();
			break;

		default:
			motor_right_stop();
			motor_left_stop();
			break;
		}

		HAL_Delay(25);
		motor_right_stop();
		motor_left_stop();
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/*AXI clock gating */
	RCC->CKGAENR = 0xFFFFFFFF;

	/** Supply configuration update enable
	 */
	HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

	/** Configure the main internal regulator output voltage
	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

	while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {
	}

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
	RCC_OscInitStruct.HSICalibrationValue = 64;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1
			| RCC_CLOCKTYPE_D1PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
	RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
