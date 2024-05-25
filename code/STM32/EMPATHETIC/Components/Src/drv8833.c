/*
 * drv8833.c
 *
 *  Created on: Jan 4, 2024
 *      Author: Kacper
 */
#include "gpio.h"
#include "drv8833.h"

typedef enum{
  FORWARD,
  BACKWARD
}Direction;

void drv8833_init(DRV8833_TypeDef* drv8833_)
{
  PWM_Init(&drv8833_->AIN_1);
  PWM_Init(&drv8833_->BIN_1);
  PWM_Init(&drv8833_->AIN_2);
  PWM_Init(&drv8833_->BIN_2);
}

void drv8833_start(DRV8833_TypeDef* drv8833_)
{
  HAL_GPIO_WritePin(nSleep_GPIO_Port, nSleep_Pin, GPIO_PIN_SET);
}

void drv8833_stop(DRV8833_TypeDef* drv8833_)
{
  drv8833_speed_change(drv8833_, A_B, 0);
  HAL_GPIO_WritePin(nSleep_GPIO_Port, nSleep_Pin, GPIO_PIN_RESET);
}

void drv8833_speed_change(DRV8833_TypeDef* drv8833_, Channel channel, float duty)
{
  drv8833_->pwm_duty = duty;
  Direction dir = duty >=0 ? FORWARD : BACKWARD;
  switch(channel){
    case 1:
      if(dir == FORWARD){
        PWM_WriteDuty(&drv8833_->AIN_2, 0);
        PWM_WriteDuty(&drv8833_->AIN_1, duty);
      }
      else if(dir == BACKWARD){
        PWM_WriteDuty(&drv8833_->AIN_2, -duty);
        PWM_WriteDuty(&drv8833_->AIN_1, 0);
      }
      break;
    case 2:
      if(dir == FORWARD){
        PWM_WriteDuty(&drv8833_->BIN_2, 0);
        PWM_WriteDuty(&drv8833_->BIN_1, duty);
      }
      else if(dir == BACKWARD){
        PWM_WriteDuty(&drv8833_->BIN_2, -duty);
        PWM_WriteDuty(&drv8833_->BIN_1, 0);
      }
      break;
    case 3:
      if(dir == FORWARD){
        PWM_WriteDuty(&drv8833_->AIN_2, 0);
        PWM_WriteDuty(&drv8833_->AIN_1, duty);
        PWM_WriteDuty(&drv8833_->BIN_2, 0);
        PWM_WriteDuty(&drv8833_->BIN_1, duty);
      }
      else if(dir == BACKWARD){
        PWM_WriteDuty(&drv8833_->AIN_2, -duty);
        PWM_WriteDuty(&drv8833_->AIN_1, 0);
        PWM_WriteDuty(&drv8833_->BIN_2, -duty);
        PWM_WriteDuty(&drv8833_->BIN_1, 0);
      }
      break;
    default:
      break;
  }
}
