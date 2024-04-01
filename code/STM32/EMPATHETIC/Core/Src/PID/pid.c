#include "pid.h"

void pid_init(pid_t * pid, float kp, float ki, float kd) {
  pid->kp = kp;
  pid->ki = ki;
  pid->kd = kd;

  pid->target = 0.0f;
  pid->prev_error = 0.0f;
  pid->integral = 0.0f;
}

float pid_update(pid_t * pid, float value) {
  float error = pid->target - value;

  pid->integral += error;

  float de = error - pid->prev_error;

  float output = pid->kp * error + pid->ki * pid->integral + pid->kd * de;

  pid->prev_error = error;

  return output;
}
