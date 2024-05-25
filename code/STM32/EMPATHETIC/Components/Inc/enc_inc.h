/**
  ******************************************************************************
  * @file		  : enc_inc.h
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.0.0
  * @date    	: Apr 27,2024
  * @brief   	: Incremental encoder handling
  *
  ******************************************************************************
  */

#ifndef INC_ENC_INC_H_
#define INC_ENC_INC_H_

/* Public includes -----------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
#include "stm32h7xx_hal.h"
#endif

/* Public typedef ------------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
typedef TIM_HandleTypeDef* ENC_TIM_TypeDef;
typedef uint32_t ENC_Channel_TypeDef;
#endif

typedef struct {
  ENC_TIM_TypeDef Encoder;
  ENC_Channel_TypeDef Channel;
  int32_t Counter;
  int32_t CounterPrev;
  int32_t CounterDiff;
  float Ts;
  float ppr;
} ENC_INC_Handle_TypeDef;

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Incremental encoder initialization:
 *        starting TIM channel(s) in 'Encoder Mode'
 * @param[inout] henc : Incremental encoder handler
 */
void ENC_INC_Init(ENC_INC_Handle_TypeDef* henc);

/**
 * @brief Incremental encoder update:
 *        computes angular speed based on counter derivative
 * @param[inout] henc : Incremental encoder handler
 * @retval: Angular speed in radians per second
 */
float ENC_INC_Update(ENC_INC_Handle_TypeDef* henc);

#endif /* INC_ENC_INC_H_ */
