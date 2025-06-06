/*
 * Iom.c
 *
 *  Created on: Jun 1, 2025
 *      Author: HSM
 */


#include "Iom.h"
#include "Iom_Cfg.h"

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

	if( raw_value == Iom_ChannelState[ChannelId].PrevRawLevel){
		// Test if the counter value still in uint8_t
		if (Iom_ChannelState[ChannelId].Counter < IOM_MAX_COUNTER_VALUE){
			Iom_ChannelState[ChannelId].Counter++;
		}
	}
	else {
		Iom_ChannelState[ChannelId].PrevRawLevel = raw_value;
		Iom_ChannelState[ChannelId].Counter = 1u;
	}
	if ((Iom_ChannelState[ChannelId].Counter >= cfg->DebounceTicks)
			&& (Iom_ChannelState[ChannelId].StableLevel != Iom_ChannelState[ChannelId].PrevRawLevel))
	{
		Iom_ChannelState[ChannelId].StableLevel = Iom_ChannelState[ChannelId].PrevRawLevel;
		Iom_ChannelState[ChannelId].Counter = 0;
	}
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
			raw_value ^= 1u; // 1 ^ 1 = 0, 0 ^ 1 = 0 ==> Input inversion
		}
		ChannelInitState.StableLevel = raw_value;
		ChannelInitState.PrevRawLevel = raw_value;
		ChannelInitState.Counter = 0;
		Iom_ChannelState[ChIn] = ChannelInitState;
	}

	// Output Init
	for(uint8_t ChOut = 0; ChOut < CfgPtr->NumOutputs; ++ChOut){
		const Iom_OutputConfigType *iomOutCfg = &CfgPtr->OutputConfig[ChOut];
		Dio_LevelType dioLevel = (iomOutCfg->ActiveLevel == IOM_ACTIVE_HIGH) ? STD_LOW : STD_HIGH; // set all output to thier inactive state
		Dio_WriteChannel(iomOutCfg->DioChannelId, dioLevel);
	}

}

Iom_LevelType Iom_ReadChannel(Iom_ChannelId ChannelId){
	if( ChannelId >= IOM_NUM_INPUTS){
		return IOM_LOW; /* No DET yet ! */
	}
	return Iom_ChannelState[ChannelId].StableLevel;
}

void Iom_InTask_nms(void){
	for (uint8_t ch = 0; ch < IOM_NUM_INPUTS; ++ch){
		Iom_Process_In(ch);
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



















