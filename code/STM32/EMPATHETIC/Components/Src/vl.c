/*
 * vl.c
 *
 *  Created on: May 26, 2024
 *      Author: Konrad
 */

#include "vl.h"

VL53L0X_RangingMeasurementData_t RangingData;
VL53L0X_Dev_t vl53l0x_c;
VL53L0X_DEV Dev = &vl53l0x_c;

uint32_t refSpadCount;
uint8_t isApertureSpads;
uint8_t VhvSettings;
uint8_t PhaseCal;

void vl_init( I2C_HandleTypeDef * i2c ) {
	// Reset sensor after upload, or uC reset.
	HAL_GPIO_WritePin( VL_EN1_GPIO_Port, VL_EN1_Pin, GPIO_PIN_RESET );
	HAL_Delay( 50 );
	HAL_GPIO_WritePin( VL_EN1_GPIO_Port, VL_EN1_Pin, GPIO_PIN_SET );

	Dev->I2cHandle = i2c;
	Dev->I2cDevAddr = VL_DEFAULT_ADDRESS;

	VL53L0X_WaitDeviceBooted( Dev );
	VL53L0X_DataInit( Dev );
	VL53L0X_StaticInit( Dev );
	VL53L0X_PerformRefCalibration( Dev, &VhvSettings, &PhaseCal );
	VL53L0X_PerformRefSpadManagement( Dev, &refSpadCount, &isApertureSpads );
	VL53L0X_SetDeviceMode( Dev, VL53L0X_DEVICEMODE_SINGLE_RANGING );

	// Enable/Disable Sigma and Signal check
	VL53L0X_SetLimitCheckEnable(
			Dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1 );
	VL53L0X_SetLimitCheckEnable(
			Dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1 );
	VL53L0X_SetLimitCheckValue(
			Dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE,
			(FixPoint1616_t)( 0.1 * 65536 ) );
	VL53L0X_SetLimitCheckValue(
			Dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE,
			(FixPoint1616_t)( 60 * 65536 ) );
	VL53L0X_SetMeasurementTimingBudgetMicroSeconds( Dev, 33000 * 2 );
	VL53L0X_SetVcselPulsePeriod( Dev, VL53L0X_VCSEL_PERIOD_PRE_RANGE, 18 );
	VL53L0X_SetVcselPulsePeriod( Dev, VL53L0X_VCSEL_PERIOD_FINAL_RANGE, 14 );

	HAL_Delay( 1000 );
}

// Function will return 1 (true) on success, and 0 (false) on error
uint8_t vl_get_distance( uint16_t * distance ) {
	VL53L0X_PerformSingleRangingMeasurement( Dev, &RangingData );

	if( RangingData.RangeStatus == 0 ) {
		*distance = RangingData.RangeMilliMeter;
		return 1;
	}

	return 0;
}
