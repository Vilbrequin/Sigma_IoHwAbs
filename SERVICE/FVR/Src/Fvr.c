/*
 * Fvr.c
 *
 *  Created on: Nov 1, 2025
 *      Author: Lenovo X13
 */

#include "Fvr_cfg.h"
#include "Vbm.h"
#include "Adm.h"
#include "Pmm.h"
#include "Iom.h"



static uint8_t get_in_voltage_range_action(uint16_t Cs);
static uint8_t get_out_voltage_range_action(uint16_t Cs);

static uint8_t input_counter = 0;
static uint8_t output_counter = 0;



void fvr_process_in(uint16_t Cs, uint8_t* Data){
	input_counter = 0;
	if (FVR_OPERATIONEL == get_in_voltage_range_action(Cs)){
		*Data  = Iom_ReadChannel(fvr_in_channels[Cs]);
	}
	else {
		// Do Nothing = ignore the read cmd
	}
}


void fvr_process_out_tor(uint16_t Cs, uint8_t OP){
	output_counter = 0;
	if (FVR_OPERATIONEL == get_out_voltage_range_action(Cs)){
		Iom_WriteChannel(fvr_out_channels[Cs], OP);
	}
	else {
		// Do Nothing = ignore the write cmd
	}
}


void fvr_process_out_pwm(uint16_t Cs, uint8_t OP){
	if (FVR_OPERATIONEL == get_out_voltage_range_action(Cs)){

		if(PMM_HEAD_LAMPS_HIGH_BEAM == Cs){
			if(1 == OP){
				pmm_SetPeriodAndDuty_HighBeam();
			}else {
				pmm_SetOutputToIdleState(PMM_HEAD_LAMPS_CHANNLE);
			}
		}
		else if(PMM_HEAD_LAMPS_LOW_BEAM == Cs){
			if(1 == OP){
				pmm_SetPeriodAndDuty_LowBeam();
			}else {
				pmm_SetOutputToIdleState(PMM_HEAD_LAMPS_CHANNLE);
			}
		}
		else if(PMM_RIGHT_TI == Cs){
			if(1 == OP){
				pmm_SetPeriodAndDuty_RightTI();
			}else {
				pmm_SetOutputToIdleState(PMM_RIGHT_TI_CHANNLE);
			}
		}
		else if(PMM_LEFT_TI == Cs){
			if(1 == OP){
				pmm_SetPeriodAndDuty_LeftTI();
			}else {
				pmm_SetOutputToIdleState(PMM_LEFT_TI_CHANNLE);
			}
		}
		else{
			// Do Nothing
		}
	}
	else {
		// Do Nothing = ignor the write cmd
	}
}


static uint8_t get_in_voltage_range_action(uint16_t Cs){
	uint8_t result = FVR_OPERATIONEL;
	vbm_range_type vRange = VBM_NORMAL_VOLTAGE;
	for (input_counter = 0; input_counter < 100; input_counter ++){
		vRange = vbm_get_range(Adm_get_in_out_power_supply_mV(ADM_PWS_DIRECTION_IN), 0);
	}
	switch(vRange){
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
	vbm_range_type vRange = VBM_NORMAL_VOLTAGE;
	for (output_counter = 0; output_counter < 100; output_counter ++){
		vRange = vbm_get_range(Adm_get_in_out_power_supply_mV(ADM_PWS_DIRECTION_OUT), 1);
	}
	switch(vRange){
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
