/*
 * Pwm_Cfg.c
 *
 *  Created on: Jun 26, 2025
 *      Author: HSM
 */


#include "Pwm_Cfg.h"

static const Pwm_InstanceConfigType Pwm_InstancesConfig[] = {

    {PWM_TIM3, 999, 16000},


};

static const Pwm_ChannelConfigType Pwm_ChannelsConfig[] = {
		{PWM_TIM3, TIM_CHANNEL_1, 0x4000, PWM_HIGH, PWM_LOW, PWM_VARIABLE_PERIOD, PWM_MODE_1},
		{PWM_TIM3, TIM_CHANNEL_2, 0x4000, PWM_HIGH, PWM_LOW, PWM_VARIABLE_PERIOD, PWM_MODE_1},
		{PWM_TIM3, TIM_CHANNEL_3, 0x4000, PWM_HIGH, PWM_LOW, PWM_VARIABLE_PERIOD, PWM_MODE_1}
};

/*
 * typedef struct {
	const Pwm_InstanceConfigType*	InstanceCfgArr;
	uint8_t							NumInstances;
	const Pwm_ChannelConfigType* 	ChannelCfgArr;
	uint8_t                   		NumChannels;
}Pwm_ConfigType;
*/
const Pwm_ConfigType Pwm_Config = {
		.InstanceCfgArr = Pwm_InstancesConfig,
		.NumInstances = 1,
		.ChannelCfgArr = Pwm_ChannelsConfig,
		.NumChannels = 3
};
