/*
 * Pmm.c
 *
 *  Created on: Jul 8, 2025
 *      Author: HSM
 */

#include "Pmm.h"

void Pmm_Init(void){
	Pwm_Init(&Pwm_Config);
}

void pmm_SetOutputToIdleState(uint8_t channelId){
	Pwm_SetOutputToIdle(channelId);
}

void pmm_SetPeriodAndDuty_HighBeam(void){
	uint16_t duty_cycle = PMM_ADAPT_DUTY_CYCLE(PMM_HEAD_LAMPS_HIGH_BEAM_DC);
	Pwm_SetPeriodAndDuty(PMM_HEAD_LAMPS_CHANNLE, PMM_FREQ_HEAD_LAMPS, duty_cycle);
}

void pmm_SetPeriodAndDuty_LowBeam(void){
	uint16_t duty_cycle = PMM_ADAPT_DUTY_CYCLE(PMM_HEAD_LAMPS_LOW_BEAM_DC);
	Pwm_SetPeriodAndDuty(PMM_HEAD_LAMPS_CHANNLE, PMM_FREQ_HEAD_LAMPS, duty_cycle);
}

void pmm_SetPeriodAndDuty_RightTI(void){
	uint16_t duty_cycle = PMM_ADAPT_DUTY_CYCLE(PMM_RL_TI_DC);
	Pwm_SetPeriodAndDuty(PMM_RIGHT_TI_CHANNLE, PMM_FREQ_RIGHT_TI, duty_cycle);
}

void pmm_SetPeriodAndDuty_LeftTI(void){
	uint16_t duty_cycle = PMM_ADAPT_DUTY_CYCLE(PMM_RL_TI_DC);
	Pwm_SetPeriodAndDuty(PMM_LEFT_TI_CHANNLE, PMM_FREQ_LEFT_TI, duty_cycle);
}
