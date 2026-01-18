/*
 * Pwm_Cfg.c
 *
 *  Created on: Jun 26, 2025
 *      Author: HSM
 */


#include "Pwm_Cfg.h"


/*
 * Fpwm = Fcnt/(ARR + 1)
 * Fcnt = Ftim/(PSC + 1)
 * Fpwm = Ftim/[(ARR + 1) * (PSC + 1)]
 *
 */
static const Pwm_InstanceConfigType Pwm_InstancesConfig[] = {
			/*PSC - ARR*/
    {PWM_TIM3, 0, 39},


};

static const Pwm_ChannelConfigType Pwm_ChannelsConfig[] = {
		{PWM_TIM3, TIM_CHANNEL_1, 0x0, PWM_HIGH, PWM_LOW, PWM_VARIABLE_PERIOD, PWM_MODE_1},
		{PWM_TIM3, TIM_CHANNEL_2, 0x0, PWM_HIGH, PWM_LOW, PWM_VARIABLE_PERIOD, PWM_MODE_1},
		{PWM_TIM3, TIM_CHANNEL_3, 0x0, PWM_HIGH, PWM_LOW, PWM_VARIABLE_PERIOD, PWM_MODE_1}
};


const Pwm_ConfigType Pwm_Config = {
		.InstanceCfgArr = Pwm_InstancesConfig,
		.NumInstances = 1,
		.ChannelCfgArr = Pwm_ChannelsConfig,
		.NumChannels = 3
};
