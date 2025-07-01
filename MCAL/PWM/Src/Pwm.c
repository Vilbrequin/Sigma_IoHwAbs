/*
 * Pwm.c
 *
 *  Created on: Jun 26, 2025
 *      Author: HSM
 */

/*********************************************************************************************************************/
/*													Includes														 */
/*********************************************************************************************************************/

#include "Pwm.h"

/*********************************************************************************************************************/
/*													Macros															 */
/*********************************************************************************************************************/

#define NUM_TIMER_IDS 	(PWM_TIM14 + 1)
#define NUM_CH_IDS		3 // need to match the number of channels in the configuration
/*********************************************************************************************************************/
/*													Sahred Data														 */
/*********************************************************************************************************************/
static TIM_HandleTypeDef 		TimerHandle[NUM_TIMER_IDS] = { {0} };
static Pwm_ChannelConfigType 	Pwm_ChannelRunTime[NUM_CH_IDS] = { {0} };
static TIM_TypeDef* 			Pwm_MapSymbolicName[NUM_TIMER_IDS] = {TIM1, TIM2, TIM3, TIM4, TIM5, TIM8, TIM9, TIM10, TIM11, TIM12, TIM13, TIM14};
static IRQn_Type				PWM_Map_TIM_IRQ_Num[NUM_TIMER_IDS][2] = {
																			{TIM1_CC_IRQn, TIM1_UP_TIM10_IRQn},
																			{TIM2_IRQn, TIM2_IRQn},
																			{TIM3_IRQn, TIM3_IRQn},
																			{TIM4_IRQn, TIM4_IRQn},
																			{TIM5_IRQn, TIM5_IRQn},
																			{TIM8_CC_IRQn, TIM8_UP_TIM13_IRQn},
																			{TIM1_BRK_TIM9_IRQn, TIM1_BRK_TIM9_IRQn},
																			{TIM1_UP_TIM10_IRQn, TIM1_UP_TIM10_IRQn},
																			{TIM1_TRG_COM_TIM11_IRQn, TIM1_TRG_COM_TIM11_IRQn},
																			{TIM8_BRK_TIM12_IRQn, TIM8_BRK_TIM12_IRQn},
																			{TIM8_UP_TIM13_IRQn, TIM8_UP_TIM13_IRQn},
																			{TIM8_TRG_COM_TIM14_IRQn, TIM8_TRG_COM_TIM14_IRQn},

																		};
boolean Pwm_Initialized  = FALSE;
/*********************************************************************************************************************/
/*												Private APIs Prototype												 */
/*********************************************************************************************************************/

static inline void Pwm_TimerEnableClock(Pwm_InstanceType InstanceId);
/*********************************************************************************************************************/
/*													Public APIs														 */
/*********************************************************************************************************************/
void Pwm_Init (const Pwm_ConfigType* ConfigPtr){
	if(ConfigPtr == NULL){
		return; /* No DET yet !! */
	}
	// step 1: Instances configuration
	for(uint8_t i = 0; i < ConfigPtr->NumInstances; ++i){
		const Pwm_InstanceConfigType* pwm_instance = &ConfigPtr->InstanceCfgArr[i];
		TIM_TypeDef* timer_instance = Pwm_MapSymbolicName[pwm_instance->TimerInstance];
		TIM_HandleTypeDef *htim = &TimerHandle[pwm_instance->TimerInstance];
		// Enable the Timer Clock
		Pwm_TimerEnableClock(pwm_instance->TimerInstance);
		htim->Instance = timer_instance;
		htim->Init.Prescaler = pwm_instance->Prescaler;
		htim->Init.Period = pwm_instance->Period - 1;
		htim->Init.CounterMode = TIM_COUNTERMODE_UP;
	#if PWM_PERIOD_UPDATED_END_PERIOD
		htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	#else
		htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	#endif
		if ( HAL_TIM_PWM_Init(htim) != HAL_OK){
				return; /* No DET yet !! */
		}
	}
	// step 2: Channels configuration
	for(uint8_t j = 0; j < ConfigPtr->NumChannels; ++j){
		const Pwm_ChannelConfigType* pwm_channel = &ConfigPtr->ChannelCfgArr[j];
		TIM_OC_InitTypeDef htim_oc_init = {0};
		TIM_HandleTypeDef* htim = &TimerHandle[pwm_channel->TimerInstance];
		htim_oc_init.OCMode = (pwm_channel->Mode) ? TIM_OCMODE_PWM2 : TIM_OCMODE_PWM1;
		htim_oc_init.OCPolarity = (pwm_channel->Polarity) ? TIM_OCPOLARITY_LOW : TIM_OCPOLARITY_HIGH;
		htim_oc_init.Pulse = ((uint32_t)(htim->Init.Period + 1) * pwm_channel->PulseTicks) >> 15;

		if ( HAL_TIM_PWM_ConfigChannel(htim, &htim_oc_init, pwm_channel->ChannelId) != HAL_OK){
					return;
		}

	#if PWM_DUTYCYCLE_UPDATED_END_PERIOD
		__HAL_TIM_ENABLE_OCxPRELOAD(htim, pwm_channel->ChannelId);
	#else
		__HAL_TIM_DISABLE_OCxPRELOAD(htim, pwm_channel->ChannelId);
	#endif

		if (HAL_TIM_PWM_Start(htim, pwm_channel->ChannelId) != HAL_OK) {
				return;
		}
		 Pwm_ChannelRunTime[j] = *pwm_channel;
	}
	Pwm_Initialized = TRUE;
}

void Pwm_SetDutyCycle (Pwm_ChannelType ChannelNumber, uint16_t DutyCycle){
	if(Pwm_Initialized == FALSE){
		return; /* No DET yet! */
	}
	if (ChannelNumber >= NUM_CH_IDS){
		return; /* No DET yet ! */
	}
	if (DutyCycle > 0x8000){
		return; /* No DET yet ! */
	}
	if(0 == DutyCycle){
		// set the PWM output state to either PWM_HIGH or PWM_LOW with regard to both the configured polarity
	}
	if(0x8000 == DutyCycle){
		// set the PWM output state to either PWM_HIGH or PWM_LOW with regard to both the configured polarity
	}
	Pwm_ChannelConfigType* channel = &Pwm_ChannelRunTime[ChannelNumber];
	TIM_HandleTypeDef* htim = &TimerHandle[channel->TimerInstance];

	if(htim->Instance == NULL){
		return; /* No DET yet ! */
	}

	Pwm_PeriodType period = __HAL_TIM_GET_AUTORELOAD(htim) + 1; /* __HAL_TIM_GET_AUTORELOAD() returns ARR = Period - 1 (because CNT rolls 0…ARR) */
	uint32_t Absolute_Pulse = ((uint32_t)period * DutyCycle) >> 15;

	__HAL_TIM_SET_COMPARE(htim, channel->ChannelId, (uint16_t)Absolute_Pulse);

	Pwm_ChannelRunTime[ChannelNumber].PulseTicks = (uint16_t)Absolute_Pulse;
}

#if PWM_PERIOD_UPDATED_END_PERIOD
void Pwm_SetPeriodAndDuty (Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16_t DutyCycle){
	if(Pwm_Initialized == FALSE){
		return; /* No DET yet! */
	}
	if (ChannelNumber >= NUM_CH_IDS){
		return; /* No DET yet ! */
	}
	if (DutyCycle > 0x8000){
		return; /* No DET yet ! */
	}
	Pwm_ChannelConfigType* channel = &Pwm_ChannelRunTime[ChannelNumber];
	if(channel->Class != PWM_VARIABLE_PERIOD){
		return; /* No DET yet! */
	}
	TIM_HandleTypeDef* htim = &TimerHandle[channel->TimerInstance];

	if(htim->Instance == NULL){
		return; /* No DET yet ! */
	}
	uint32_t Absolute_Pulse = 0;
	if(0 == Period){
		__HAL_TIM_SET_COMPARE(htim, channel->ChannelId, 0);
	}
	else {
		__HAL_TIM_SET_AUTORELOAD(htim, (Period - 1u));
		Absolute_Pulse = ((uint32_t)Period * DutyCycle) >> 15;
		__HAL_TIM_SET_COMPARE(htim, channel->ChannelId, (uint16_t)Absolute_Pulse);
	}
	Pwm_ChannelRunTime[ChannelNumber].PulseTicks = (uint16_t)Absolute_Pulse;

}
#endif

void Pwm_SetOutputToIdle (Pwm_ChannelType ChannelNumber){
	if(Pwm_Initialized == FALSE){
		return; /* No DET yet! */
	}
	if (ChannelNumber >= NUM_CH_IDS){
		return; /* No DET yet ! */
	}
	Pwm_ChannelConfigType* channel = &Pwm_ChannelRunTime[ChannelNumber];

	TIM_HandleTypeDef* htim = &TimerHandle[channel->TimerInstance];

	if(htim->Instance == NULL){
		return; /* No DET yet ! */
	}
	Pwm_PeriodType period = __HAL_TIM_GET_AUTORELOAD(htim) + 1; /* __HAL_TIM_GET_AUTORELOAD() returns ARR = Period - 1 (because CNT rolls 0…ARR) */

	if(channel->Polarity == PWM_HIGH){
		if(channel->IdleState == PWM_HIGH){
			__HAL_TIM_SET_COMPARE(htim, channel->ChannelId, period);
		}
		else if(channel->IdleState == PWM_LOW){
			__HAL_TIM_SET_COMPARE(htim, channel->ChannelId, 0);
		}
	}
	else{
		if(channel->IdleState == PWM_HIGH){
			__HAL_TIM_SET_COMPARE(htim, channel->ChannelId, 0);
		}
		else if(channel->IdleState == PWM_LOW){
			__HAL_TIM_SET_COMPARE(htim, channel->ChannelId, period);
		}
	}
}

Pwm_OutputStateType Pwm_GetOutputState (Pwm_ChannelType ChannelNumber){
	if(Pwm_Initialized == FALSE){
		return; /* No DET yet! */
	}
	if(Pwm_Initialized == FALSE){
		return PWM_LOW;
	}
	if (ChannelNumber >= NUM_CH_IDS){
		return PWM_LOW;
	}
	Pwm_ChannelConfigType* channel = &Pwm_ChannelRunTime[ChannelNumber];

	TIM_HandleTypeDef* htim = &TimerHandle[channel->TimerInstance];

	if(htim->Instance == NULL){
		return PWM_LOW; /* No DET yet ! */
	}
	uint16_t counter  = __HAL_TIM_GET_COUNTER(htim);
	uint16_t ccr = __HAL_TIM_GET_COMPARE(htim, channel->ChannelId);
	boolean raw = (channel->Mode == PWM_MODE_1) ? (ccr > counter) : (ccr < counter);
	if(channel->Polarity == PWM_LOW)
	{
		raw = !raw;
	}
	return raw ? PWM_LOW : PWM_HIGH;

}

void Pwm_EnableNotification (Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification){
	if (ChannelNumber >= NUM_CH_IDS){
		return; /* No DET yet ! */
	}

	Pwm_ChannelConfigType* channel = &Pwm_ChannelRunTime[ChannelNumber];

	TIM_HandleTypeDef* htim = &TimerHandle[channel->TimerInstance];

	if(htim->Instance == NULL){
		return; /* No DET yet ! */
	}

	uint32_t interruptCCMask;
	switch (channel->ChannelId) {
	case TIM_CHANNEL_1:
		interruptCCMask = TIM_IT_CC1;
		break;
	case TIM_CHANNEL_2:
		interruptCCMask = TIM_IT_CC2;
		break;
	case TIM_CHANNEL_3:
		interruptCCMask = TIM_IT_CC3;
		break;
	case TIM_CHANNEL_4:
		interruptCCMask = TIM_IT_CC4;
		break;
	default:
		// Do Nothing !
		break; /* No DET yet ! */
	}
	const uint32_t updateEventMask = TIM_IT_UPDATE;
/*

	|Channel Mode|Channel Polarity|Edge in CC match case|Update Event Edge|
	|------------|----------------|---------------------|-----------------|
	|PWM MODE 1	 |HIGH			  |Falling				|Rising			  |
	|------------|----------------|---------------------|-----------------|
	|PWM MODE 1	 |LOW			  |Rising				|Falling		  |
	|------------|----------------|---------------------|-----------------|
	|PWM MODE 2	 |HIGH			  |Rising				|Falling		  |
	|------------|----------------|---------------------|-----------------|
	|PWM MODE 2	 |LOW			  |Falling				|Rising			  |
	|------------|----------------|---------------------|-----------------|

	1. The match case depends on the channel's mode and polarity, so the the pwm mode is 1 and  polarity is high then the match case occurs on falling edge,
	 and in the other hand if the Pwm mode is 2 and the polarity is low then  the match case occurs on falling edge, so this looks like a XOR truth table.

	2. In case the requested notification type does not match the "CC match case" then the other edge happen in the update event
*/
	boolean isRising = (channel->Mode == PWM_MODE_1) ^ (channel->Polarity == PWM_HIGH);
	boolean ccIRQ = FALSE;
	boolean upIRQ = FALSE;
	boolean isAdvTIM = (channel->TimerInstance == PWM_TIM1) || (channel->TimerInstance == PWM_TIM8);

	switch(Notification){
	case PWM_RISING_EDGE:
		if(isRising){
			__HAL_TIM_ENABLE_IT(htim, interruptCCMask);
			ccIRQ = TRUE;
		}
		else {
			__HAL_TIM_ENABLE_IT(htim, updateEventMask);
			upIRQ = TRUE;
		}
		break;
	case PWM_FALLING_EDGE:
		if(isRising){
			__HAL_TIM_ENABLE_IT(htim, updateEventMask);
			upIRQ = TRUE;
		}
		else {
			__HAL_TIM_ENABLE_IT(htim, interruptCCMask);
			ccIRQ = TRUE;
		}
		break;
	case PWM_BOTH_EDGES:
		__HAL_TIM_ENABLE_IT(htim, interruptCCMask | updateEventMask);
		upIRQ = TRUE;
		ccIRQ = TRUE;
		break;
	}
	if(isAdvTIM){
		if(ccIRQ){
			HAL_NVIC_EnableIRQ(PWM_Map_TIM_IRQ_Num[channel->TimerInstance][0]);
		}
		if(upIRQ){
			HAL_NVIC_EnableIRQ(PWM_Map_TIM_IRQ_Num[channel->TimerInstance][1]);
		}
	}
	else {
		HAL_NVIC_EnableIRQ(PWM_Map_TIM_IRQ_Num[channel->TimerInstance][0]);
	}
	channel->NotificationEnabled = TRUE;
}

void Pwm_DisableNotification (Pwm_ChannelType ChannelNumber){
	if (ChannelNumber >= NUM_CH_IDS){
		return; /* No DET yet ! */
	}

	Pwm_ChannelConfigType* channel = &Pwm_ChannelRunTime[ChannelNumber];

	TIM_HandleTypeDef* htim = &TimerHandle[channel->TimerInstance];

	if(htim->Instance == NULL){
		return; /* No DET yet ! */
	}

	switch (channel->ChannelId){
	case TIM_CHANNEL_1:
		__HAL_TIM_DISABLE_IT(htim, TIM_IT_CC1);
		break;
	case TIM_CHANNEL_2:
		__HAL_TIM_DISABLE_IT(htim, TIM_IT_CC2);
		break;
	case TIM_CHANNEL_3:
		__HAL_TIM_DISABLE_IT(htim, TIM_IT_CC3);
		break;
	case TIM_CHANNEL_4:
		__HAL_TIM_DISABLE_IT(htim, TIM_IT_CC4);
		break;
	default:
		// Do Nothing !
		break;
	}
}
/*********************************************************************************************************************/
/*												Private APIs Definition												 */
/*********************************************************************************************************************/
static inline void Pwm_TimerEnableClock(Pwm_InstanceType InstanceId){

	switch (InstanceId){
	case PWM_TIM1:
		__HAL_RCC_TIM1_CLK_ENABLE();
		break;
	case PWM_TIM2:
		__HAL_RCC_TIM2_CLK_ENABLE();
		break;
	case PWM_TIM3:
		__HAL_RCC_TIM3_CLK_ENABLE();
		break;
	case PWM_TIM4:
		__HAL_RCC_TIM4_CLK_ENABLE();
		break;
	case PWM_TIM5:
		__HAL_RCC_TIM5_CLK_ENABLE();
		break;
	case PWM_TIM8:
		__HAL_RCC_TIM8_CLK_ENABLE();
		break;
	case PWM_TIM9:
		__HAL_RCC_TIM9_CLK_ENABLE();
		break;
	case PWM_TIM10:
		__HAL_RCC_TIM10_CLK_ENABLE();
		break;
	case PWM_TIM11:
		__HAL_RCC_TIM11_CLK_ENABLE();
		break;
	case PWM_TIM12:
		__HAL_RCC_TIM12_CLK_ENABLE();
		break;
	case PWM_TIM13:
		__HAL_RCC_TIM13_CLK_ENABLE();
		break;
	case PWM_TIM14:
		__HAL_RCC_TIM14_CLK_ENABLE();
		break;
	default:
		// Do Nothing
		break;
	}
}

