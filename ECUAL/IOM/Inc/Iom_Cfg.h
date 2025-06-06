/*
 * Iom_Cfg.h
 *
 *  Created on: Jun 1, 2025
 *      Author: HSM
 */

#ifndef INC_IOM_CFG_H_
#define INC_IOM_CFG_H_

#include "Iom.h"

#define IOM_CH_DOOR_SWITCH   	0u

#define IOM_CH_FRONT_LAMPS	  	0u

#define IOM_NUM_INPUTS 			1u

#define IOM_NUM_OUTPUT 			1u

#define IOM_TASK_FREQ			50u

extern const Iom_ConfigType Iom_InputCfg;
extern Iom_ChannelStateType Iom_ChannelState[];

#endif /* INC_IOM_CFG_H_ */
