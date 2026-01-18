/*
 * Fvr.c
 *
 *  Created on: Nov 1, 2025
 *      Author: Lenovo X13
 */

#include "Fvr_cfg.h"
#include "Fvr_rte.h"
#include "Vbm.h"
#include "Fvr.h"

static void Fvr_HighBeamBtn(void);
static void Fvr_LowBeamBtn(void);
static void Fvr_WasherBtn(void);
static void Fvr_EnginTemp(void);
static void Fvr_OilPress(void);
static void Fvr_BattVolt(void);
static void Fvr_WiperLvl(void);

static void Fvr_WasherLoad(void);
static void Fvr_HighBeamLoad(void);
static void Fvr_LowBeamLoad(void);
static void Fvr_WiperLoad(void);

static void Fvr_processIn(void);
static void Fvr_ProcessOut(void);

static uint8_t get_in_voltage_range_action(uint16_t Cs);
static uint8_t get_out_voltage_range_action(uint16_t Cs);


static uint8_t get_in_voltage_range_action(uint16_t Cs){
	uint8_t result = FVR_OPERATIONEL;
	vbm_range_type vInRange = VBM_NORMAL_VOLTAGE;

	Rte_Read_RP_InVoltageRang_InVoltageRang(&vInRange);

	switch(vInRange){
		case VBM_UNDER_VOLTAGE:
			result = fvr_in_action[Cs][VBM_UNDER_VOLTAGE - 1];
			break;
		case VBM_NORMAL_VOLTAGE:
			result = fvr_in_action[Cs][VBM_NORMAL_VOLTAGE - 1];
			break;
		case VBM_OVER_VOLTAGE:
			result = fvr_in_action[Cs][VBM_OVER_VOLTAGE - 1];
			break;
		case VBM_EXTRA_OVER_VOLTAGE:
			result = fvr_in_action[Cs][VBM_EXTRA_OVER_VOLTAGE - 1];
			break;
		default :
			break;
	}
	return result;
}


static uint8_t get_out_voltage_range_action(uint16_t Cs){
	uint8_t result = FVR_OPERATIONEL;
	vbm_range_type vOutRange = VBM_NORMAL_VOLTAGE;

	Rte_Read_RP_OutVoltageRang_OutVoltageRang(&vOutRange);

	switch(vOutRange){
		case VBM_UNDER_VOLTAGE:
			result = fvr_out_action[Cs][VBM_UNDER_VOLTAGE - 1];
			break;
		case VBM_NORMAL_VOLTAGE:
			result = fvr_out_action[Cs][VBM_NORMAL_VOLTAGE - 1];
			break;
		case VBM_OVER_VOLTAGE:
			result = fvr_out_action[Cs][VBM_OVER_VOLTAGE -1];
			break;
		case VBM_EXTRA_OVER_VOLTAGE:
			result = fvr_out_action[Cs][VBM_EXTRA_OVER_VOLTAGE - 1];
			break;
		default :
			break;
	}
	return result;
}

// input channels
void Fvr_HighBeamBtn(void){
	uint8_t range = get_in_voltage_range_action(FVR_HIGH_BEAM_IN_CHANNLE);
	if (FVR_OPERATIONEL == range){
		Rte_write_PP_InHighBeamAllowed_InHighBeamAllowed(1);
	}else{
		Rte_write_PP_InHighBeamAllowed_InHighBeamAllowed(0);
	}
}

void Fvr_LowBeamBtn(void){
	uint8_t range = get_in_voltage_range_action(FVR_LOW_BEAM_IN_CHANNLE);
	if (FVR_OPERATIONEL == range){
		Rte_write_PP_InLowBeamAllowed_InLowBeamAllowed(1);
	}else{
		Rte_write_PP_InLowBeamAllowed_InLowBeamAllowed(0);
	}
}

void Fvr_WasherBtn(void){
	uint8_t range = get_in_voltage_range_action(FVR_WASHER_IN_CHANNLE);
	if (FVR_OPERATIONEL == range){
		Rte_write_PP_InWasherAllowed_InWasherAllowed(1);
	}else{
		Rte_write_PP_InWasherAllowed_InWasherAllowed(0);
	}
}

void Fvr_EnginTemp(void){
	uint8_t range = get_in_voltage_range_action(FVR_ENGINE_TEMPERATURE_CHANNEL);
	if (FVR_OPERATIONEL == range){
		Rte_write_PP_InEnginTempAllowed_InEnginTempAllowed(1);
	}else{
		Rte_write_PP_InEnginTempAllowed_InEnginTempAllowed(0);
	}
}

void Fvr_OilPress(void){
	uint8_t range = get_in_voltage_range_action(FVR_OIL_PRESSURE_CHANNEL);
	if (FVR_OPERATIONEL == range){
		Rte_write_PP_InOilPressAllowed_InOilPressAllowed(1);
	}else{
		Rte_write_PP_InOilPressAllowed_InOilPressAllowed(0);
	}
}

void Fvr_BattVolt(void){
	uint8_t range = get_in_voltage_range_action(FVR_BATTERY_VOLTAGE_CHANNEL);
	if (FVR_OPERATIONEL == range){
		Rte_write_PP_InBattVoltAllowed_InBattVoltAllowed(1);
	}else{
		Rte_write_PP_InBattVoltAllowed_InBattVoltAllowed(0);
	}
}

void Fvr_WiperLvl(void){
	uint8_t range = get_in_voltage_range_action(FVR_WIPER_LEVEL_CHANNEL);
	if (FVR_OPERATIONEL == range){
		Rte_write_PP_InWiperLvlAllowed_InWiperLvlAllowed(1);
	}else{
		Rte_write_PP_InWiperLvlAllowed_InWiperLvlAllowed(0);
	}
}

// Output channels
void Fvr_WasherLoad(void){
	uint8_t range = get_out_voltage_range_action(FVR_WASHER_OUT_CHANNLE);
	if (FVR_OPERATIONEL == range){
		Rte_write_PP_OutWasherAllowed_OutWasherAllowed(1);
	}else{
		Rte_write_PP_OutWasherAllowed_OutWasherAllowed(0);
	}
}
void Fvr_HighBeamLoad(void){
	uint8_t range = get_out_voltage_range_action(FVR_HIGH_BEAM_OUT_CHANNLE);
	if (FVR_OPERATIONEL == range){
		Rte_write_PP_OutHighBeamAllowed_OutHighBeamAllowed(1);
	}else{
		Rte_write_PP_OutHighBeamAllowed_OutHighBeamAllowed(0);
	}
}
void Fvr_LowBeamLoad(void){
	uint8_t range = get_out_voltage_range_action(FVR_LOW_BEAM_OUT_CHANNLE);
	if (FVR_OPERATIONEL == range){
		Rte_write_PP_OutLowBeamAllowed_OutLowBeamAllowed(1);
	}else{
		Rte_write_PP_OutLowBeamAllowed_OutLowBeamAllowed(0);
	}
}
void Fvr_WiperLoad(void){
	uint8_t range = get_out_voltage_range_action(FVR_WIPER_OUT_CHANNLE);
	if (FVR_OPERATIONEL == range){
		Rte_write_PP_OutWiperAllowed_OutWiperAllowed(1);
	}else{
		Rte_write_PP_OutWiperAllowed_OutWiperAllowed(0);
	}
}


void Fvr_processIn(void)
{
	Fvr_HighBeamBtn();
	Fvr_LowBeamBtn();
	Fvr_WasherBtn();
	Fvr_EnginTemp();
	Fvr_OilPress();
	Fvr_BattVolt();
	Fvr_WiperLvl();
}

void Fvr_ProcessOut(void)
{
	Fvr_HighBeamLoad();
	Fvr_LowBeamLoad();
	Fvr_WiperLoad();
	Fvr_WasherLoad();
}


void Fvr_InTask_10ms(void)
{
	Fvr_processIn();
}

void Fvr_OutTask_10ms(void)
{
	Fvr_ProcessOut();
}







































