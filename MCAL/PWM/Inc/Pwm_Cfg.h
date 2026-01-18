/*
 * Pwm_Cfg.h
 *
 *  Created on: Jun 26, 2025
 *      Author: HSM
 */

#ifndef INC_PWM_CFG_H_
#define INC_PWM_CFG_H_

#include "Pwm.h"

#define PWM_HIGH_BEAM_CHANNLE			(Pwm_ChannelType)0U
#define PWM_LOW_BEAM_CHANNLE			(Pwm_ChannelType)1U
#define PWM_WIPER_CHANNLE				(Pwm_ChannelType)2U

extern const Pwm_ConfigType Pwm_Config;

#endif /* INC_PWM_CFG_H_ */
