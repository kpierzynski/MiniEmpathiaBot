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

#include "drv8833.h"
#include "enc_inc.h"
#include "enc_A_LPF_biquad_df1.h"
#include "enc_B_LPF_biquad_df1.h"
#include "pid_controller.h"
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

/* USER CODE BEGIN PV */
DRV8833_TypeDef hdrv8833 = {
		.AIN_1 = PWM_INIT_HANDLE(&htim3, TIM_CHANNEL_1), .AIN_2 =
		PWM_INIT_HANDLE(&htim3, TIM_CHANNEL_2), .BIN_1 =
		PWM_INIT_HANDLE(&htim3, TIM_CHANNEL_3), .BIN_2 =
		PWM_INIT_HANDLE(&htim3, TIM_CHANNEL_4) };

float duty_A = 0;
float duty_B = 0;

ENC_INC_Handle_TypeDef henc_A = {
		.Encoder = &htim4, .Channel = TIM_CHANNEL_ALL, .Counter = 0,
		.CounterPrev = 0, .CounterDiff = 0, .Ts = 0.01 /* 10 ms */, .ppr = 12 };

float w_A = 0;  // [rad/s]
float wf_A = 0;  // [rad/s]

ENC_INC_Handle_TypeDef henc_B = {
		.Encoder = &htim2, .Channel = TIM_CHANNEL_ALL, .Counter = 0,
		.CounterPrev = 0, .CounterDiff = 0, .Ts = 0.01 /* 10 ms */, .ppr = 12 };

float w_B = 0;  // [rad/s]
float wf_B = 0;  // [rad/s]

PID_HandleTypeDef hpid_A = {
		.Kp = 0.0, .Ki = 0.5, .Kd = 0, .N = 1, .Ts = 0.01, .LimitLower = -100,
		.LimitUpper = 100 };

float w_A_ref = 0;

PID_HandleTypeDef hpid_B = {
		.Kp = 0.0, .Ki = 0.5, .Kd = 0, .N = 1, .Ts = 0.01, .LimitLower = -100,
		.LimitUpper = 100 };

float w_B_ref = 0;

unsigned char RxMsg[32];
unsigned int RxMsgLen = 8;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config( void );
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/**
 * @brief  Period elapsed callback in non-blocking mode
 * @param  htim TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback( TIM_HandleTypeDef * htim ) {
	if( htim == &htim15 ) {
		w_A = ENC_INC_Update( &henc_A );
		arm_biquad_cascade_df1_f32(
				&enc_A_LPF, &w_A, &wf_A, ENC_A_LPF_BLOCK_SIZE );
		if( w_A_ref == 0 ) {
			duty_A = 0;
		} else {
			duty_A = PID_GetOutput( &hpid_A, w_A_ref, wf_A );
		}
		drv8833_speed_change( &hdrv8833, A, duty_A );

		w_B = -ENC_INC_Update( &henc_B );
		arm_biquad_cascade_df1_f32(
				&enc_B_LPF, &w_B, &wf_B, ENC_B_LPF_BLOCK_SIZE );
		if( w_B_ref == 0 ) {
			duty_B = 0;
		} else {
			duty_B = PID_GetOutput( &hpid_B, w_B_ref, wf_B );
		}
		drv8833_speed_change( &hdrv8833, B, duty_B );
	}
}

/**
 * @brief  Rx Transfer completed callback.
 * @param  huart UART handle.
 * @retval None
 */
void HAL_UART_RxCpltCallback( UART_HandleTypeDef * huart ) {
	if( huart != &hlpuart1 )
		return;

	int value_left = atoi( (char*)( RxMsg ) );
	int value_right = atoi( (char*)( RxMsg + 4 ) );

	w_A_ref = value_left;
	w_B_ref = value_right;

	HAL_UART_Receive_IT( &hlpuart1, RxMsg, RxMsgLen );

}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main( void ) {

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
	MX_LPUART1_UART_Init();
	MX_TIM3_Init();
	MX_TIM4_Init();
	MX_TIM2_Init();
	MX_TIM15_Init();
	/* USER CODE BEGIN 2 */
	drv8833_init( &hdrv8833 );
	drv8833_start( &hdrv8833 );

	PID_Init( &hpid_A );
	arm_biquad_cascade_df1_init_f32(
			&enc_A_LPF, ENC_A_LPF_NUM_STAGES, enc_A_LPF_COEFFS,
			enc_A_LPF_STATE );
	ENC_INC_Init( &henc_A );

	arm_biquad_cascade_df1_init_f32(
			&enc_B_LPF, ENC_B_LPF_NUM_STAGES, enc_B_LPF_COEFFS,
			enc_B_LPF_STATE );
	ENC_INC_Init( &henc_B );

	HAL_TIM_Base_Start_IT( &htim15 );
	HAL_UART_Receive_IT( &hlpuart1, RxMsg, RxMsgLen );

	HAL_UART_Transmit( &hlpuart1, (const uint8_t*)"Started.\r\n", 10,
	HAL_MAX_DELAY );
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	uint32_t heart = HAL_GetTick();
	while( 1 ) {

		if( heart - HAL_GetTick() > 1000 )
			HAL_UART_Transmit(
					&hlpuart1, (const uint8_t*)". ", 2, HAL_MAX_DELAY );  // Send heartbeat dot
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config( void ) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/*AXI clock gating */
	RCC->CKGAENR = 0xFFFFFFFF;

	/** Supply configuration update enable
	 */
	HAL_PWREx_ConfigSupply( PWR_LDO_SUPPLY );

	/** Configure the main internal regulator output voltage
	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG( PWR_REGULATOR_VOLTAGE_SCALE3 );

	while( !__HAL_PWR_GET_FLAG( PWR_FLAG_VOSRDY ) ) {
	}

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
	RCC_OscInitStruct.HSICalibrationValue = 64;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if( HAL_RCC_OscConfig( &RCC_OscInitStruct ) != HAL_OK ) {
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

	if( HAL_RCC_ClockConfig( &RCC_ClkInitStruct, FLASH_LATENCY_2 ) != HAL_OK ) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler( void ) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while( 1 ) {
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
