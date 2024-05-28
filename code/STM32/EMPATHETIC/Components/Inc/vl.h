/*
 * vl.h
 *
 *  Created on: May 26, 2024
 *      Author: Konrad
 */

#ifndef INC_VL_H_
#define INC_VL_H_

#include "main.h"
#include "vl53l0x_api.h"

#define VL_DEFAULT_ADDRESS 0x52

void vl_init( I2C_HandleTypeDef * i2c );

uint8_t vl_get_distance( uint16_t * distance );

#endif /* INC_VL_H_ */
