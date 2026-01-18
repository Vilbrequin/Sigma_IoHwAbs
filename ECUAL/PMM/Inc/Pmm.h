/*
 * Pmm.h
 *
 *  Created on: Jul 8, 2025
 *      Author: HSM
 */

#ifndef INC_PMM_H_
#define INC_PMM_H_

#include <stdint.h>
#include "Pwm.h"
#include "Pwm_Cfg.h"

#define PMM_NUM_CHANNELS					3U

#define PMM_MAX_DUTY_CYCLE					0x8000U

#define PMM_ADAPT_DUTY_CYCLE(duty_cycle)	(uint16_t)(((uint32_t)duty_cycle * PMM_MAX_DUTY_CYCLE)/100)

//PMM Channels
#define PMM_HIGH_BEAM_CHANNLE				PWM_HIGH_BEAM_CHANNLE
#define PMM_LOW_BEAM_CHANNLE				PWM_LOW_BEAM_CHANNLE
#define PMM_WIPER_CHANNLE					PWM_WIPER_CHANNLE


void Pmm_Init(void);
void Pmm_SetOutputToIdleState(void);
void Pmm_SetDutyCycle_HighBeam(void);
void Pmm_SetDutyCycle_LowBeam(void);
void Pmm_SetDutyCycle_Wipper(void);
void Pmm_Task_10ms(void);

#endif /* INC_PMM_H_ */
