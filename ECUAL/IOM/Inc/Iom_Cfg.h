/*
 * Iom_Cfg.h
 *
 *  Created on: Jun 1, 2025
 *      Author: HSM
 */

#ifndef INC_IOM_CFG_H_
#define INC_IOM_CFG_H_

#include "Iom.h"

// OUTPUTS
#define IOM_CH_WASHER_LED   				0U

// INPUTS
#define IOM_CH_HIGH_BEAM_BTN	   			0U
#define IOM_CH_LOW_BEAM_BTN   				1U
#define IOM_CH_WASHER_BTN			   		2U

#define IOM_NUM_INPUT 						3U

#define IOM_NUM_OUTPUT 						1U

#define IOM_TASK_FREQ						5u // 5 ms

extern const Iom_ConfigType Iom_InputCfg;
extern Iom_ChannelStateType Iom_ChannelState[IOM_NUM_INPUT];

#endif /* INC_IOM_CFG_H_ */
