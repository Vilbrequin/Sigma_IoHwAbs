/*
 * Pmm.c
 *
 *  Created on: Jul 8, 2025
 *      Author: HSM
 */

#include "Pmm.h"
#include "Pmm_Rte.h"


static uint16_t PMM_HIGH_BEAM_DUTY_CYCLE = 0;
static uint16_t PMM_LOW_BEAM_DUTY_CYCLE = 0;
static uint16_t PMM_WIPER_DUTY_CYCLE = 0;

void Pmm_Init(void){
	Pwm_Init(&Pwm_Config);
	Pmm_SetOutputToIdleState();

}

void Pmm_SetOutputToIdleState(void){
	Pwm_SetOutputToIdle(PMM_HIGH_BEAM_CHANNLE);
	Pwm_SetOutputToIdle(PMM_LOW_BEAM_CHANNLE);
	Pwm_SetOutputToIdle(PMM_WIPER_CHANNLE);
}

void Pmm_SetDutyCycle_HighBeam(void){
	uint8_t HighBeamDc = 0;
	uint8_t isAllowed = 0;
	// 1 read the app duty cycle
	Rte_read_RP_HighBeamDc_HighBeamDc(&HighBeamDc);

	// 2 Adapt the duty cycle to 0x0000 - 0x8000 range :
	PMM_HIGH_BEAM_DUTY_CYCLE = PMM_ADAPT_DUTY_CYCLE(HighBeamDc);

	// 3 Set duty cycle
	Rte_read_RP_OutHighBeamAllowed_OutHighBeamAllowed(&isAllowed);
	if(isAllowed){
		Pwm_SetDutyCycle(PMM_HIGH_BEAM_CHANNLE, PMM_HIGH_BEAM_DUTY_CYCLE);
	}
}

void Pmm_SetDutyCycle_LowBeam(void){
	uint8_t LowBeamDc = 0;
	uint8_t isAllowed = 0;
	// 1 read the app duty cycle
	Rte_read_RP_LowBeamDc_LowBeamDc(&LowBeamDc);

	// 2 Adapt the duty cycle to 0x0000 - 0x8000 range :
	PMM_LOW_BEAM_DUTY_CYCLE = PMM_ADAPT_DUTY_CYCLE(LowBeamDc);

	// 3 Set duty cycle
	Rte_read_RP_OutLowBeamAllowed_OutLowBeamAllowed(&isAllowed);
	if(isAllowed){
		Pwm_SetDutyCycle(PMM_LOW_BEAM_CHANNLE, PMM_LOW_BEAM_DUTY_CYCLE);
	}
}

void Pmm_SetDutyCycle_Wipper(void){
	uint8_t WipperDc = 0;
	uint8_t isAllowed = 0;
	uint32_t pulse_len = 0;
	uint8_t pulse_percent = 0;

	// 1 read the app duty cycle
	Rte_read_RP_WipperDc_WipperDc(&WipperDc);

	pulse_len = 100 + (WipperDc * (500 - 100) / 180);
	pulse_percent = (pulse_len - 20)/40;
	// 2 Adapt the duty cycle to 0x0000 - 0x8000 range :
	PMM_WIPER_DUTY_CYCLE= PMM_ADAPT_DUTY_CYCLE(pulse_percent);

	// 3 Set duty cycle
	Rte_read_RP_OutWiperAllowed_OutWiperAllowed(&isAllowed);
	if(isAllowed){
		Pwm_SetDutyCycle(PMM_WIPER_CHANNLE, PMM_WIPER_DUTY_CYCLE);
	}
}


void Pmm_Task_10ms(void)
{
	Pmm_SetDutyCycle_HighBeam();
	Pmm_SetDutyCycle_LowBeam();
	Pmm_SetDutyCycle_Wipper();
}
//void pmm_SetOutputToIdleState(uint8_t channelId){
//	Pwm_SetOutputToIdle(channelId);
//}

//void pmm_SetPeriodAndDuty_HighBeam(void){
//	uint16_t duty_cycle = PMM_ADAPT_DUTY_CYCLE(PMM_HEAD_LAMPS_HIGH_BEAM_DC);
//	Pwm_SetPeriodAndDuty(PMM_HEAD_LAMPS_CHANNLE, PMM_FREQ_HEAD_LAMPS, duty_cycle);
//}
//
//void pmm_SetPeriodAndDuty_LowBeam(void){
//	uint16_t duty_cycle = PMM_ADAPT_DUTY_CYCLE(PMM_HEAD_LAMPS_LOW_BEAM_DC);
//	Pwm_SetPeriodAndDuty(PMM_HEAD_LAMPS_CHANNLE, PMM_FREQ_HEAD_LAMPS, duty_cycle);
//}
//
//void pmm_SetPeriodAndDuty_RightTI(void){
//	uint16_t duty_cycle = PMM_ADAPT_DUTY_CYCLE(PMM_RL_TI_DC);
//	Pwm_SetPeriodAndDuty(PMM_RIGHT_TI_CHANNLE, PMM_FREQ_RIGHT_TI, duty_cycle);
//}
//
//void pmm_SetPeriodAndDuty_LeftTI(void){
//	uint16_t duty_cycle = PMM_ADAPT_DUTY_CYCLE(PMM_RL_TI_DC);
//	Pwm_SetPeriodAndDuty(PMM_LEFT_TI_CHANNLE, PMM_FREQ_LEFT_TI, duty_cycle);
//}

void pmm_SetDuty(Pwm_ChannelType ChID, uint16_t DutyCycle)
{
	uint16_t adapted_dc = PMM_ADAPT_DUTY_CYCLE(DutyCycle);
	Pwm_SetDutyCycle(ChID, adapted_dc);
}
