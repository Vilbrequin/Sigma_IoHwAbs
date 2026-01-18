/*
 * VBM.c
 *
 *  Created on: Nov 1, 2025
 *      Author: Lenovo X13
 */

/***********************************************************************************************************************/
/*                                  					Includes		    									       */
/************************************************************************************************************************/
#include "Vbm.h"
#include "Vbm_Rte.h"

/***********************************************************************************************************************/
/*                                  				Static Variables    									     	   */
/************************************************************************************************************************/
static const uint16_t vbm_thresholds[4] = {VBM_VOLTAGE_THR_5_60, VBM_VOLTAGE_THR_8_00, VBM_VOLTAGE_THR_16_00, VBM_VOLTAGE_THR_19_00};
/*Used to count how many times we are in a range before performing the state transition for all Power Supply rails*/
static uint8_t counterUnderVoltage[VBM_BATT_PWS_NUM];
static uint8_t counterNormalVoltage[VBM_BATT_PWS_NUM];
static uint8_t counterOverVoltage[VBM_BATT_PWS_NUM];
static uint8_t counterExOverVoltage[VBM_BATT_PWS_NUM];

/*A static global array that keep track of the previous VBATT range for all Power Supply rails*/
static vbm_range_type vbm_prev_vbatt_rng[VBM_BATT_PWS_NUM] = {VBM_NORMAL_VOLTAGE, VBM_NORMAL_VOLTAGE};

void vbm_ranges_init(void) {

	Rte_write_PP_InVoltageRange_InVoltageRange(VBM_NORMAL_VOLTAGE);
	Rte_write_PP_OutVoltageRange_OutVoltageRange(VBM_NORMAL_VOLTAGE);
}


vbm_range_type vbm_get_range(vbm_vbatt_type inVal, Vbm_batt_pws VbattInPwS)
{
	vbm_range_type current_vbatt_rng[VBM_BATT_PWS_NUM]= {VBM_NORMAL_VOLTAGE, VBM_NORMAL_VOLTAGE};

	// Cas 1 : We're in the under voltage range, and we must check if all conditions are met to perform the transition to under voltage state from the actual state
	if ( (inVal >= VBM_VOLTAGE_THR_5_60) && (inVal <= VBM_VOLTAGE_THR_8_00) ){
		if ( (counterUnderVoltage[VbattInPwS] >= 20) && (vbm_prev_vbatt_rng[VbattInPwS] == VBM_NORMAL_VOLTAGE) ) {
			current_vbatt_rng[VbattInPwS] = VBM_UNDER_VOLTAGE;
			counterNormalVoltage[VbattInPwS] = 0;
			counterOverVoltage[VbattInPwS] = 0;
			counterExOverVoltage[VbattInPwS] = 0;
		}

		else if ( (counterUnderVoltage[VbattInPwS] >= 40) && (vbm_prev_vbatt_rng[VbattInPwS] == VBM_OVER_VOLTAGE) ) {
				current_vbatt_rng[VbattInPwS] = VBM_UNDER_VOLTAGE;
				counterNormalVoltage[VbattInPwS] = 0;
				counterOverVoltage[VbattInPwS] = 0;
				counterExOverVoltage[VbattInPwS] = 0;
			}
		else if ( (counterUnderVoltage[VbattInPwS] >= 80) && (vbm_prev_vbatt_rng[VbattInPwS] == VBM_EXTRA_OVER_VOLTAGE) ) {
				current_vbatt_rng[VbattInPwS] = VBM_UNDER_VOLTAGE;
				counterNormalVoltage[VbattInPwS] = 0;
				counterOverVoltage[VbattInPwS] = 0;
				counterExOverVoltage[VbattInPwS] = 0;
			}
		else if (vbm_prev_vbatt_rng[VbattInPwS] == VBM_UNDER_VOLTAGE) {
			// Do Nothing
		}
		else {
			counterUnderVoltage[VbattInPwS] = counterUnderVoltage[VbattInPwS] + 1;
		}

		if (counterNormalVoltage[VbattInPwS] != 0){
			counterNormalVoltage[VbattInPwS] = counterNormalVoltage[VbattInPwS] - 1;
		}
		if (counterOverVoltage[VbattInPwS] != 0){
			counterOverVoltage[VbattInPwS] = counterOverVoltage[VbattInPwS] - 1;
		}
		if (counterExOverVoltage[VbattInPwS] != 0){
			counterExOverVoltage[VbattInPwS] = counterExOverVoltage[VbattInPwS] - 1;
		}
	}

	// Cas 2 : We're in the Normal voltage range, and we must check if all conditions are met to perform the transition to Normal voltage state from the actual state
	else if ( (inVal >= VBM_VOLTAGE_THR_8_00) && (inVal <= VBM_VOLTAGE_THR_16_00) ){
		if ( (counterNormalVoltage[VbattInPwS] >= 20) && (vbm_prev_vbatt_rng[VbattInPwS] == VBM_UNDER_VOLTAGE) ) {
			current_vbatt_rng[VbattInPwS] = VBM_NORMAL_VOLTAGE;
			counterUnderVoltage[VbattInPwS] = 0;
			counterOverVoltage[VbattInPwS] = 0;
			counterExOverVoltage[VbattInPwS] = 0;
		}

		else if ( (counterNormalVoltage[VbattInPwS] >= 40) && (vbm_prev_vbatt_rng[VbattInPwS] == VBM_OVER_VOLTAGE) ) {
				current_vbatt_rng[VbattInPwS] = VBM_NORMAL_VOLTAGE;
				counterUnderVoltage[VbattInPwS] = 0;
				counterOverVoltage[VbattInPwS] = 0;
				counterExOverVoltage[VbattInPwS] = 0;
			}
		else if ( (counterNormalVoltage[VbattInPwS] >= 80) && (vbm_prev_vbatt_rng[VbattInPwS] == VBM_EXTRA_OVER_VOLTAGE) ) {
				current_vbatt_rng[VbattInPwS] = VBM_NORMAL_VOLTAGE;
				counterUnderVoltage[VbattInPwS] = 0;
				counterOverVoltage[VbattInPwS] = 0;
				counterExOverVoltage[VbattInPwS] = 0;
			}
		else if (vbm_prev_vbatt_rng[VbattInPwS] == VBM_NORMAL_VOLTAGE) {
			// Do Nothing
		}
		else {
			counterNormalVoltage[VbattInPwS] = counterNormalVoltage[VbattInPwS] + 1;
		}

		if (counterUnderVoltage[VbattInPwS] != 0){
			counterUnderVoltage[VbattInPwS] = counterUnderVoltage[VbattInPwS] - 1;
		}
		if (counterOverVoltage[VbattInPwS] != 0){
			counterOverVoltage[VbattInPwS] = counterOverVoltage[VbattInPwS] - 1;
		}
		if (counterExOverVoltage[VbattInPwS] != 0){
			counterExOverVoltage[VbattInPwS] = counterExOverVoltage[VbattInPwS] - 1;
		}
	}

	// Cas 3 : We're in the Over voltage range, and we must check if all conditions are met to perform the transition to Over voltage state from the actual state
	else if ( (inVal >= VBM_VOLTAGE_THR_16_00) && (inVal <= VBM_VOLTAGE_THR_19_00) ){
		if ( (counterOverVoltage[VbattInPwS] >= 20) && (vbm_prev_vbatt_rng[VbattInPwS] == VBM_UNDER_VOLTAGE) ) {
			current_vbatt_rng[VbattInPwS] = VBM_OVER_VOLTAGE;
			counterUnderVoltage[VbattInPwS] = 0;
			counterNormalVoltage[VbattInPwS] = 0;
			counterExOverVoltage[VbattInPwS] = 0;
		}

		else if ( (counterOverVoltage[VbattInPwS] >= 40) && (vbm_prev_vbatt_rng[VbattInPwS] == VBM_NORMAL_VOLTAGE) ) {
				current_vbatt_rng[VbattInPwS] = VBM_OVER_VOLTAGE;
				counterUnderVoltage[VbattInPwS] = 0;
				counterNormalVoltage[VbattInPwS] = 0;
				counterExOverVoltage[VbattInPwS] = 0;
			}
		else if ( (counterOverVoltage[VbattInPwS] >= 80) && (vbm_prev_vbatt_rng[VbattInPwS] == VBM_EXTRA_OVER_VOLTAGE) ) {
				current_vbatt_rng[VbattInPwS] = VBM_OVER_VOLTAGE;
				counterUnderVoltage[VbattInPwS] = 0;
				counterNormalVoltage[VbattInPwS] = 0;
				counterExOverVoltage[VbattInPwS] = 0;
			}
		else if (vbm_prev_vbatt_rng[VbattInPwS] == VBM_OVER_VOLTAGE) {
			// Do Nothing
		}
		else {
			counterOverVoltage[VbattInPwS] = counterOverVoltage[VbattInPwS] + 1;
		}

		if (counterUnderVoltage[VbattInPwS] != 0){
			counterUnderVoltage[VbattInPwS] = counterUnderVoltage[VbattInPwS] - 1;
		}
		if (counterNormalVoltage[VbattInPwS] != 0){
			counterNormalVoltage[VbattInPwS] = counterNormalVoltage[VbattInPwS] - 1;
		}
		if (counterExOverVoltage[VbattInPwS] != 0){
			counterExOverVoltage[VbattInPwS] = counterExOverVoltage[VbattInPwS] - 1;
		}
	}

	// Cas 4 : We're in the Extra Over voltage range, and we must check if all conditions are met to perform the transition to Extra Over voltage state from the actual state
	else if ( (inVal >= VBM_VOLTAGE_THR_19_00) ){
		if ( (counterExOverVoltage[VbattInPwS] >= 20) && (vbm_prev_vbatt_rng[VbattInPwS] == VBM_UNDER_VOLTAGE) ) {
			current_vbatt_rng[VbattInPwS] = VBM_EXTRA_OVER_VOLTAGE;
			counterUnderVoltage[VbattInPwS] = 0;
			counterNormalVoltage[VbattInPwS] = 0;
			counterOverVoltage[VbattInPwS] = 0;
		}

		else if ( (counterExOverVoltage[VbattInPwS] >= 40) && (vbm_prev_vbatt_rng[VbattInPwS] == VBM_NORMAL_VOLTAGE) ) {
				current_vbatt_rng[VbattInPwS] = VBM_EXTRA_OVER_VOLTAGE;
				counterUnderVoltage[VbattInPwS] = 0;
				counterNormalVoltage[VbattInPwS] = 0;
				counterOverVoltage[VbattInPwS] = 0;
			}
		else if ( (counterExOverVoltage[VbattInPwS] >= 80) && (vbm_prev_vbatt_rng[VbattInPwS] == VBM_OVER_VOLTAGE) ) {
				current_vbatt_rng[VbattInPwS] = VBM_EXTRA_OVER_VOLTAGE;
				counterUnderVoltage[VbattInPwS] = 0;
				counterNormalVoltage[VbattInPwS] = 0;
				counterOverVoltage[VbattInPwS] = 0;
			}
		else if (vbm_prev_vbatt_rng[VbattInPwS] == VBM_EXTRA_OVER_VOLTAGE) {
			// Do Nothing
		}
		else {
			counterExOverVoltage[VbattInPwS] = counterExOverVoltage[VbattInPwS] + 1;
		}

		if (counterUnderVoltage[VbattInPwS] != 0){
			counterUnderVoltage[VbattInPwS] = counterUnderVoltage[VbattInPwS] - 1;
		}
		if (counterNormalVoltage[VbattInPwS] != 0){
			counterNormalVoltage[VbattInPwS] = counterNormalVoltage[VbattInPwS] - 1;
		}
		if (counterOverVoltage[VbattInPwS] != 0){
			counterOverVoltage[VbattInPwS] = counterOverVoltage[VbattInPwS] - 1;
		}
	}
	else {
		// Do Nothing
	}

	/*change segment and apply hysteresis */
	if(current_vbatt_rng[VbattInPwS] > vbm_prev_vbatt_rng[VbattInPwS]){
		// the check here is done in order to set the right prev range in order to apply the correct hysteresis
		if (current_vbatt_rng[VbattInPwS] - vbm_prev_vbatt_rng[VbattInPwS] > 1){

			vbm_prev_vbatt_rng[VbattInPwS] = current_vbatt_rng[VbattInPwS] - 1;

		}
		else {
			// Do Nothing
		}

		// Apply Hyst : V_in < its_range_lower_limit + hyst_value then the current range should not change (i.e current <-- prev)
		if (inVal < vbm_thresholds[current_vbatt_rng[VbattInPwS] - 1] + VBM_HYST_HIGH_MV){
			current_vbatt_rng[VbattInPwS] = vbm_prev_vbatt_rng[VbattInPwS];
		}

		else {
			// Do Nothing !
		}

	}

	else if(current_vbatt_rng[VbattInPwS] < vbm_prev_vbatt_rng[VbattInPwS]){
		// the check here is done in order to set the right prev range in order to apply the correct hysteresis
		if (vbm_prev_vbatt_rng[VbattInPwS] - current_vbatt_rng[VbattInPwS] > 1){

			vbm_prev_vbatt_rng[VbattInPwS] = current_vbatt_rng[VbattInPwS] + 1;

		}
		else {
			// Do Nothing
		}

		// Apply Hyst : V_in > its_range_upper_limit - hyst_value then the current range should not change (i.e current <-- prev)
		if (inVal > vbm_thresholds[vbm_prev_vbatt_rng[VbattInPwS] - 1] - VBM_HYST_LOW_MV){
			current_vbatt_rng[VbattInPwS] = vbm_prev_vbatt_rng[VbattInPwS];
		}

		else {
			// Do Nothing !
		}
	}
	else {
		// Do Nothing
	}

	vbm_prev_vbatt_rng[VbattInPwS] = current_vbatt_rng[VbattInPwS];
	return current_vbatt_rng[VbattInPwS];
}


void Vbm_ProcessIn(void) {
	vbm_range_type inRange;
	vbm_vbatt_type inVBatt;

	Rte_read_RP_InPwS_InPwS(&inVBatt);
	inRange = vbm_get_range(inVBatt, VBM_IN_PSW);

	Rte_write_PP_InVoltageRange_InVoltageRange(inRange);
}

void Vbm_ProcessOut(void) {
	vbm_range_type inRange;
	vbm_vbatt_type inVBatt;

	Rte_read_RP_InPwS_InPwS(&inVBatt);
	inRange = vbm_get_range(inVBatt, VBM_IN_PSW);

	Rte_write_PP_InVoltageRange_InVoltageRange(inRange);
}

void Vbm_Init(void){
	vbm_ranges_init();
}

void Vbm_Task_10ms(void){
	Vbm_ProcessIn();
	Vbm_ProcessOut();
}
