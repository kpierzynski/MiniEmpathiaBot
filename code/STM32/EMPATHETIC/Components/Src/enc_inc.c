/**
  ******************************************************************************
  * @file     : enc_inc.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.0.0
  * @date     : Apr 27,2024
  * @brief    : Incremental encoder handling
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "enc_inc.h"
#include <stdlib.h>
#include <math.h>

/* Private variables ---------------------------------------------------------*/
static const int32_t ENC_INC_CounterMax = 65535;

/* Private functions ---------------------------------------------------------*/
static int32_t sign(int32_t x)
{
  if(x < 0)
    return -1;
  else
    return 1;
}

/* Public functions ----------------------------------------------------------*/
/**
 * @brief Incremental encoder initialization:
 *        starting TIM channel(s) in 'Encoder Mode'
 * @param[inout] henc : Incremental encoder handler
 */
void ENC_INC_Init(ENC_INC_Handle_TypeDef* henc)
{
  HAL_TIM_Encoder_Start(henc->Encoder, henc->Channel);
}

/**
 * @brief Incremental encoder update:
 *        computes angular speed based on counter derivative
 * @param[inout] henc : Incremental encoder handler
 * @retval: Angular speed in radians per second
 */
float ENC_INC_Update(ENC_INC_Handle_TypeDef* henc)
{
  henc->Counter = __HAL_TIM_GET_COUNTER(henc->Encoder);

  // Compute difference between current and previous counter value
  henc->CounterDiff = henc->Counter - henc->CounterPrev;

  // Handle integer overflow
  if(abs(henc->CounterDiff) > ENC_INC_CounterMax/2)
    henc->CounterDiff = henc->Counter + sign(henc->CounterDiff)*henc->CounterPrev - sign(henc->CounterDiff)*ENC_INC_CounterMax;

  // Save counter value for next iteration
  henc->CounterPrev = henc->Counter;

  // Scale result to rad/s
  return ((2*M_PI/henc->Ts)/(4*henc->ppr)) * henc->CounterDiff;
}
