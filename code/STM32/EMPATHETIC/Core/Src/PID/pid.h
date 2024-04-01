/*
 * pid.h
 *
 *  Created on: Apr 1, 2024
 *      Author: Konrad
 */

#ifndef SRC_PID_PID_H_
#define SRC_PID_PID_H_

typedef struct {
  float kp, ki, kd;

  float prev_error;
  float integral;

  float target;
} pid_t;

void pid_init(pid_t * pid, float kp, float ki, float kd);
float pid_update(pid_t * pid, float value);

#endif /* SRC_PID_PID_H_ */
