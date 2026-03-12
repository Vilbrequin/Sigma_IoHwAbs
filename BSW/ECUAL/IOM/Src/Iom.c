/*
 * Iom.c
 *
 *  Created on: Jun 1, 2025
 *      Author: HSM
 */


#include "Iom.h"
#include "Iom_Cfg.h"
#include "Iom_Rte.h"

/****************************************************************************************
 * 							Private functions declaration
 ****************************************************************************************/
static void Iom_Process_In(Iom_ChannelId ChannelId);

/****************************************************************************************
 * 							Private functions Implementation
 ****************************************************************************************/
static void Iom_Process_In(Iom_ChannelId ChannelId){
	const Iom_InputConfigType* cfg = &Iom_InputCfg.InputConfig[ChannelId];
	uint8_t raw_value = (uint8_t)Dio_ReadChannel(cfg->DioChannelId);

	if (cfg->InvertionFlag){
		raw_value ^= 1u;
	}

	// Integrator de-bouncing algo
	// a state is valid only if cnt == 0 (realesed) or cnt == max ticks (pressed)
	if(raw_value == 0){
		if(Iom_ChannelState[ChannelId].cnt > 0){
			Iom_ChannelState[ChannelId].cnt--;
		}
		else {
			Iom_ChannelState[ChannelId].cnt = 0;
		}
	}
	else if (raw_value == 1){
		if(Iom_ChannelState[ChannelId].cnt < cfg->DebounceTicks){
 			Iom_ChannelState[ChannelId].cnt++;
		}
		else {
			Iom_ChannelState[ChannelId].cnt = cfg->DebounceTicks;
		}
	}
	else {
		// Do Nothing
	}

	if (Iom_ChannelState[ChannelId].cnt == 0) {
		Iom_ChannelState[ChannelId].debounced = 0;
	}
	else if (Iom_ChannelState[ChannelId].cnt == cfg->DebounceTicks) {

		Iom_ChannelState[ChannelId].debounced = 1;
	}
	else {
		Iom_ChannelState[ChannelId].debounced = Iom_ChannelState[ChannelId].prev_debounced;
	}

	if( (Iom_ChannelState[ChannelId].prev_debounced == 0) && (Iom_ChannelState[ChannelId].debounced == 1) ){
		Iom_ChannelState[ChannelId].press_cnt++;
	}
	Iom_ChannelState[ChannelId].prev_debounced = Iom_ChannelState[ChannelId].debounced;
}

/****************************************************************************************
 * 							Public functions Implementation
 ****************************************************************************************/

void Iom_Init(const Iom_ConfigType *CfgPtr) {
	if (CfgPtr == NULL) {
		/* No DET yet!*/
		return;
	}
	// Input init
	Iom_ChannelStateType ChannelInitState = {0};
	for (uint8_t ChIn = 0; ChIn < CfgPtr->NumInputs; ++ChIn) {
		const Iom_InputConfigType *iomInCfg = &CfgPtr->InputConfig[ChIn];
		// Initialize the init state of the channel

		uint8_t raw_value = (uint8_t)Dio_ReadChannel(iomInCfg->DioChannelId);
		if (iomInCfg->InvertionFlag) {
			raw_value ^= 1u; // 1 ^ 1 = 0, 0 ^ 1 = 1 ==> Input inversion
		}
		ChannelInitState.debounced = raw_value;
		ChannelInitState.prev_debounced = raw_value;
		ChannelInitState.cnt = raw_value ? iomInCfg->DebounceTicks : 0; // to match the de-bounce logic
		ChannelInitState.press_cnt = 0;
		Iom_ChannelState[ChIn] = ChannelInitState;
	}

	// Output Init
	for(uint8_t ChOut = 0; ChOut < CfgPtr->NumOutputs; ++ChOut){
		const Iom_OutputConfigType *iomOutCfg = &CfgPtr->OutputConfig[ChOut];
		Dio_LevelType dioLevel = (iomOutCfg->ActiveLevel == IOM_ACTIVE_HIGH) ? STD_LOW : STD_HIGH; // set all output to their inactive state
		Dio_WriteChannel(iomOutCfg->DioChannelId, dioLevel);
	}

}

void Iom_WriteChannel(Iom_ChannelId ChannelId, Iom_OutLevel Level){
	if (ChannelId >= IOM_NUM_OUTPUT){
		return;
	}
	const Iom_OutputConfigType* iomOutCfg = &Iom_InputCfg.OutputConfig[ChannelId];
	Dio_LevelType dioLevel = STD_LOW;

	if (IOM_OUT_ON == Level){
		dioLevel = (iomOutCfg->ActiveLevel == IOM_ACTIVE_HIGH) ? STD_HIGH : STD_LOW;
	}
	else if (IOM_OUT_OFF == Level){
		dioLevel = (iomOutCfg->ActiveLevel == IOM_ACTIVE_HIGH) ? STD_LOW : STD_HIGH;
	}
	else {
		/* Misra-C Rule 14.10 Compliant*/
	}

	Dio_WriteChannel(iomOutCfg->DioChannelId, dioLevel);
}

void Iom_InTask_5ms(void){
	uint8_t isAllowed = 0;
	for (uint8_t ch = 0; ch < IOM_NUM_INPUT; ch++){
		Iom_Process_In(ch);
		switch (ch) {
			case IOM_CH_HIGH_BEAM_BTN:
				Rte_read_RP_InHighBeamAllowed_InHighBeamAllowed(&isAllowed);
				if(isAllowed)
				{
					Rte_write_PP_HighBeamBtn_Debounced(Iom_ChannelState[ch].debounced);
					Rte_write_PP_HighBeamBtn_PressCounter(Iom_ChannelState[ch].press_cnt);
				}
//
				break;
			case IOM_CH_LOW_BEAM_BTN:
				Rte_read_RP_InLowBeamAllowed_InLowBeamAllowed(&isAllowed);
				if(isAllowed)
				{
					Rte_write_PP_LowBeamBtn_Debounced(Iom_ChannelState[ch].debounced);
					Rte_write_PP_LowBeamBtn_PressCounter(Iom_ChannelState[ch].press_cnt);
				}
				break;
			case IOM_CH_WASHER_BTN:
				Rte_read_RP_InWasherAllowed_InWasherAllowed(&isAllowed);
				if(isAllowed)
				{
					Rte_write_PP_WasherBtn_Debounced(Iom_ChannelState[ch].debounced);
					Rte_write_PP_WasherBtn_PressCounter(Iom_ChannelState[ch].press_cnt);
				}
				break;
			default:
				break;
		}
	}
}

void Iom_OutTask_5ms(void){
	Iom_OutLevel level = 0;
	uint8_t isAllowed = 0;
	Rte_read_RP_OutWasherAllowed_OutWasherAllowed(&isAllowed);
	if(isAllowed)
	{
		Rte_read_RP_WasherState_WasherState(&level);
		Iom_WriteChannel(IOM_CH_WASHER_LED, level);
	}
}
