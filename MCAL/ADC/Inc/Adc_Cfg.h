/*
 * Adc_Cfg.h
 *
 *  Created on: Jul 26, 2025
 *      Author: HSM
 */

#ifndef INC_ADC_CFG_H_
#define INC_ADC_CFG_H_

#include "Adc.h"

/***************************************************************************************************************************************/
/*														 POWER SUPPLY GRP															   */
/***************************************************************************************************************************************/
/*Group ID*/
#define ADC_IN_OUT_POWER_SUPPLY_GRP				0x00

/*Group Channels' rank*/
#define ADC_IN_POWER_SUPPLY_CHANNEL				0x00
#define ADC_OUT_POWER_SUPPLY_CHANNEL			0x01
/*Group number of channels*/
#define ADC_IN_OUT_POWER_SUPPLY_GRP_N_CHANNELS	0x02
/*Group number of samples*/
#define ADC_IN_OUT_POWER_SUPPLY_GRP_N_SAMPLES	0x03
/*Group 's buffer length*/
#define ADC_IN_OUT_POWER_SUPPLY_GRP_SAMPLES		(ADC_IN_OUT_POWER_SUPPLY_GRP_N_CHANNELS * ADC_IN_OUT_POWER_SUPPLY_GRP_N_SAMPLES)

/***************************************************************************************************************************************/
/*														 		SENSORS GRP															   */
/***************************************************************************************************************************************/
/*Group ID*/
#define ADC_IN_SESNORS_GRP						0x01

/*Group Channels' rank*/
#define ADC_WIPER_BUTTON_CHANNEL				0x00
#define ADC_E_TEMP_SENSOR_CHANNEL				0x01 // engine temperature sensor
#define ADC_OIL_PRESS_SENSOR_CHANNEL			0x02 // oil pressure sensor
#define ADC_BATT_VOLT_SENSOR_CHANNEL			0x03 // Battery voltage sensor

#define ADC_WIPP_POS_SENSOR_CHAMMEL				0X04 // Wiper position sensor to track if the wiper is in it's init state

/*Group number of channels*/
#define ADC_IN_SESNORS_GRP_N_CHANNELS			0x05
/*Group number of samples*/
#define ADC_IN_SESNORS_GRP_N_SAMPLES			0x05
/*Group 's buffer length*/
#define ADC_IN_SESNORS_GRP_SAMPLES		(ADC_IN_SESNORS_GRP_N_CHANNELS * ADC_IN_SESNORS_GRP_N_SAMPLES)

extern const Adc_ConfigType Adc_Config;

#endif /* INC_ADC_CFG_H_ */
