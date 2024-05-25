/*
 * drv8833.h
 *
 *  Created on: Jan 4, 2024
 *      Author: Kacper
 */

#ifndef INC_DRV8833_H_
#define INC_DRV8833_H_

#include "dio.h"
#include "pwm.h"

typedef enum{
  A = 1,
  B = 2,
  A_B = 3
}Channel;

typedef struct{
  PWM_Handle_TypeDef AIN_1;
  PWM_Handle_TypeDef AIN_2;

  PWM_Handle_TypeDef BIN_1;
  PWM_Handle_TypeDef BIN_2;

  DIO_Handle_TypeDef nSLEEP;

  DIO_Handle_TypeDef nFAULT;

  float pwm_duty;
}DRV8833_TypeDef;

void drv8833_init(DRV8833_TypeDef* drv8833_);

void drv8833_start(DRV8833_TypeDef* drv8833_);

void drv8833_stop(DRV8833_TypeDef* drv8833_);

void drv8833_speed_change(DRV8833_TypeDef* drv8833_, Channel channel, float duty);

#endif /* INC_DRV8833_H_ */
