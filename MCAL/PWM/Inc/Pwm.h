/*
 * pwm.h
 *
 *  Created on: Jun 22, 2025
 *      Author: HSM
 */

#ifndef SRC_PWM_H_
#define SRC_PWM_H_
/*********************************************************************************************************************/
/*													Includes														 */
/*********************************************************************************************************************/

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
/*********************************************************************************************************************/
/*												Type definitions													 */
/*********************************************************************************************************************/

typedef unsigned char 				boolean;
#define FALSE						(boolean)0x00
#define TRUE						(boolean)0x01

typedef uint8_t 					Pwm_ChannelType;

typedef uint16_t 					Pwm_PeriodType;

typedef uint16_t					Pwm_PrescalerType;

typedef uint8_t						Pwm_InstanceType;
#define	PWM_TIM1					(Pwm_InstanceType)0x00 /* TIM1 - Advanced Timer*/
#define	PWM_TIM2					(Pwm_InstanceType)0x01 /* TIM2 - GPT with 4 Channels*/
#define	PWM_TIM3					(Pwm_InstanceType)0x02 /* TIM3 - GPT with 4 Channels */
#define	PWM_TIM4					(Pwm_InstanceType)0x03 /* TIM4 - GPT with 4 Channels */
#define	PWM_TIM5					(Pwm_InstanceType)0x04 /* TIM5 - GPT with 4 Channels */
#define	PWM_TIM8					(Pwm_InstanceType)0x05 /* TIM8 - Advanced Timer*/
#define	PWM_TIM9					(Pwm_InstanceType)0x06 /* TIM9 - GPT with 2 Channels*/
#define	PWM_TIM10					(Pwm_InstanceType)0x07 /* TIM10 - GPT with 1 Channel */
#define	PWM_TIM11					(Pwm_InstanceType)0x08 /* TIM11 - GPT with 1 Channel */
#define	PWM_TIM12					(Pwm_InstanceType)0x09 /* TIM12 - GPT with 2 Channels*/
#define	PWM_TIM13					(Pwm_InstanceType)0x0A /* TIM13 - GPT with 1 Channel */
#define	PWM_TIM14					(Pwm_InstanceType)0x0B /* TIM14 - GPT with 1 Channel */


typedef uint8_t 					Pwm_OutputStateType;
#define PWM_HIGH					(Pwm_OutputStateType)0x00
#define PWM_LOW						(Pwm_OutputStateType)0x01

typedef uint8_t 					Pwm_EdgeNotificationType;
#define PWM_RISING_EDGE				(Pwm_EdgeNotificationType)0x00
#define PWM_FALLING_EDGE			(Pwm_EdgeNotificationType)0x01
#define PWM_BOTH_EDGES 				(Pwm_EdgeNotificationType)0x02

typedef uint8_t 					Pwm_ChannelClassType;
#define PWM_VARIABLE_PERIOD 		(Pwm_ChannelClassType)0x00
#define PWM_FIXED_PERIOD 			(Pwm_ChannelClassType)0x01
#define PWM_FIXED_PERIOD_SHIFTED  	(Pwm_ChannelClassType)0x02

typedef uint8_t						Pwm_PowerStateRequestResultType;
#define PWM_SERVICE_ACCEPTED		(Pwm_PowerStateRequestResultType)0x00
#define PWM_NOT_INIT 				(Pwm_PowerStateRequestResultType)0x01
#define PWM_SEQUENCE_ERROR			(Pwm_PowerStateRequestResultType)0x02
#define PWM_HW_FAILURE				(Pwm_PowerStateRequestResultType)0x03
#define PWM_POWER_STATE_NOT_SUPP 	(Pwm_PowerStateRequestResultType)0x04
#define PWM_TRANS_NOT_POSSIBLE		(Pwm_PowerStateRequestResultType)0x05

typedef uint8_t						Pwm_ChannelMode;
#define PWM_MODE_1					(Pwm_ChannelMode)0x00
#define PWM_MODE_2					(Pwm_ChannelMode)0x01

// Instance Level Configuration
typedef struct {
	Pwm_InstanceType				TimerInstance;
	Pwm_PrescalerType				Prescaler; /* PSC */
	Pwm_PeriodType					Period; /* ARR - in Ticks */
}Pwm_InstanceConfigType;

// Channel Level Configuration
typedef struct {
	Pwm_InstanceType				TimerInstance;
	Pwm_ChannelType 				ChannelId; /* TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3, TIM_CHANNEL_4, TIM_CHANNEL_ALL */
	uint16_t						PulseTicks;	/* Pulse (CCRx) 0 <=> 0%, 0x8000 <=> 100% - in Ticks*/
	Pwm_OutputStateType				Polarity;
	Pwm_OutputStateType				IdleState;
	Pwm_ChannelClassType			Class;
	Pwm_ChannelMode					Mode;
	boolean							NotificationEnabled;
}Pwm_ChannelConfigType;

typedef struct {
	const Pwm_InstanceConfigType*	InstanceCfgArr;
	uint8_t							NumInstances;
	const Pwm_ChannelConfigType* 	ChannelCfgArr;
	uint8_t                   		NumChannels;
}Pwm_ConfigType;


/*********************************************************************************************************************/
/*												Global Macros														 */
/*********************************************************************************************************************/
#define STD_OFF								0x00
#define STD_ON								0x01

#define PWM_DUTYCYCLE_UPDATED_END_PERIOD	STD_OFF
#define PWM_PERIOD_UPDATED_END_PERIOD		STD_ON


/*********************************************************************************************************************/
/*													Public APIs														 */
/*********************************************************************************************************************/
void Pwm_Init (const Pwm_ConfigType* ConfigPtr);
void Pwm_DeInit (void);
void Pwm_SetDutyCycle (Pwm_ChannelType ChannelNumber, uint16_t DutyCycle);
void Pwm_SetPeriodAndDuty (Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16_t DutyCycle);
void Pwm_SetOutputToIdle (Pwm_ChannelType ChannelNumber);
Pwm_OutputStateType Pwm_GetOutputState (Pwm_ChannelType ChannelNumber);
void Pwm_DisableNotification (Pwm_ChannelType ChannelNumber);
void Pwm_EnableNotification (Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification);

#endif /* SRC_PWM_H_ */
