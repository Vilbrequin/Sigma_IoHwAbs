/*
 * Pmm.h
 *
 *  Created on: Jul 8, 2025
 *      Author: HSM
 */

#ifndef INC_PMM_H_
#define INC_PMM_H_

#include "Pwm.h"
#include "Pwm_Cfg.h"
#include <stdint.h>
// APB1 Timer Clock Frequency (TIM2/TIM3/TIM4/TIM5/TIM12/TIM13/TIM14)
#define PMM_TIMx_FREQ_HZ_1					40000000U

// APB2 Timer Clock Frequency (TIM1/TIM8/TIM9/TIM10/TIM11)
#define PMM_TIMx_FREQ_HZ_2					80000000U

#define PMM_MAX_DUTY_CYCLE					0x8000U

#define PMM_NUM_CHANNELS					3U

#define PMM_ADAPT_DUTY_CYCLE(duty_cycle)	(uint16_t)(((uint32_t)duty_cycle * PMM_MAX_DUTY_CYCLE)/100)

//PMM Channels
#define PMM_HEAD_LAMPS_CHANNLE				PWM_HEAD_LAMPS_CHANNLE
#define PMM_RIGHT_TI_CHANNLE				PWM_RIGHT_TI_CHANNLE
#define PMM_LEFT_TI_CHANNLE					PWM_LEFT_TI_CHANNLE

#define PMM_HEAD_LAMPS_HIGH_BEAM			0U
#define PMM_HEAD_LAMPS_LOW_BEAM				1U
#define PMM_RIGHT_TI						2U
#define PMM_LEFT_TI							3U


// Channels Frequency
/*
 * Fin = 40MHz, PSC = 999
 * 1 tick = (PSC + 1)/Fin
 * to achieve a out frequency Fout we shall know how many ticks we need out Counter to tick before reloading
 * n ticks = Fin/((PSC + 1) * Fout)*/

#define PMM_FREQ_HEAD_LAMPS					4U // 10KHz

#define PMM_FREQ_RIGHT_TI					20000U // 2Hz (90 +/- 30 flash per minute)

#define PMM_FREQ_LEFT_TI					10000U // 2Hz (90 +/- 30 flash per minute)

// Duty Cycles
#define PMM_HEAD_LAMPS_HIGH_BEAM_DC			90U

#define PMM_HEAD_LAMPS_LOW_BEAM_DC			60U

#define PMM_RL_TI_DC						50U

void Pmm_Init(void);

void pmm_SetOutputToIdleState(uint8_t channelId);

void pmm_SetPeriodAndDuty_HighBeam(void);

void pmm_SetPeriodAndDuty_LowBeam(void);

void pmm_SetPeriodAndDuty_RightTI(void);

void pmm_SetPeriodAndDuty_LeftTI(void);


#endif /* INC_PMM_H_ */
