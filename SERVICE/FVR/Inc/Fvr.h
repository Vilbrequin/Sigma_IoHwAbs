/*
 * Fvr.h
 *
 *  Created on: Nov 1, 2025
 *      Author: Lenovo X13
 */

#ifndef INC_FVR_H_
#define INC_FVR_H_

#include <stdint.h>

#define FVR_NUM_OF_VALID_RANGES			4U

// FVR Out
#define FVR_WASHER_OUT_CHANNLE				0U
#define FVR_HIGH_BEAM_OUT_CHANNLE			1U
#define FVR_LOW_BEAM_OUT_CHANNLE			2U
#define FVR_WIPER_OUT_CHANNLE				3U

// FVR IN
#define FVR_HIGH_BEAM_IN_CHANNLE		0U
#define FVR_LOW_BEAM_IN_CHANNLE			1U
#define FVR_WASHER_IN_CHANNLE			2U
#define FVR_ENGINE_TEMPERATURE_CHANNEL	3U
#define FVR_OIL_PRESSURE_CHANNEL		4U
#define FVR_BATTERY_VOLTAGE_CHANNEL		5U
#define FVR_WIPER_LEVEL_CHANNEL			6U

/*FVR Valid Ranges*/
#define FVR_OFF							0U
#define FVR_IGNORED						1U
#define FVR_OPERATIONEL					2U


void Fvr_InTask_10ms(void);
void Fvr_OutTask_10ms(void);
#endif /* INC_FVR_H_ */
