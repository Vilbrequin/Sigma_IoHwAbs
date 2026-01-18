/*
 * Adm.c
 *
 *  Created on: Nov 1, 2025
 *      Author: Lenovo X13
 */


#include "Adm.h"
#include "Adm_Rte.h"

/* the Adc_Read API returns a on buffer of n*m length but to get the samples of a specific channel in a group we use this API */
//static uint16_t Adm_in_out_buffer[ADC_IN_OUT_POWER_SUPPLY_GRP_SAMPLES];
//static uint16_t Adm_in_or_out_buffer[ADC_IN_OUT_POWER_SUPPLY_GRP_N_SAMPLES];
//
//static uint16_t Adm_sensor_grp_buffer[ADC_IN_SESNORS_GRP_SAMPLES];
//static uint16_t Adm_active_channel_buffer[ADC_IN_SESNORS_GRP_N_SAMPLES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static uint16_t Adm_Pws_buffer[ADC_IN_OUT_POWER_SUPPLY_GRP_N_CHANNELS];
static uint16_t Adm_Pws_channel_in_samples[ADM_DEBOUNCE_AVG];
static uint16_t Adm_Pws_channel_out_samples[ADM_DEBOUNCE_AVG];

static uint16_t Adm_Sensor_buffer[ADC_IN_SESNORS_GRP_N_CHANNELS];
static uint16_t Adm_Sensor_channel_1_samples[ADM_DEBOUNCE_AVG];
static uint16_t Adm_Sensor_channel_2_samples[ADM_DEBOUNCE_AVG];
static uint16_t Adm_Sensor_channel_3_samples[ADM_DEBOUNCE_AVG];
static uint16_t Adm_Sensor_channel_4_samples[ADM_DEBOUNCE_AVG];

static uint16_t Adm_Sensor_grp_val[ADC_IN_SESNORS_GRP_N_CHANNELS] = {0};
static uint16_t Adm_PwS_grp_val[ADC_IN_OUT_POWER_SUPPLY_GRP_N_CHANNELS] = {0};

static uint8_t iterator_PwS = 0;
static uint8_t iterator_Sensor = 0;

static uint32_t PwS_in_mv = 0;
static uint32_t PwS_out_mv = 0;

void Adm_SensorGrp(void)
{

	uint8_t isAllowed = 0;

	if(iterator_Sensor < ADM_DEBOUNCE_AVG)
	{
		Adc_StartGroupConversion(ADC_IN_SESNORS_GRP);
		Adm_Sensor_channel_1_samples[iterator_Sensor] = Adm_Sensor_buffer[0];
		Adm_Sensor_channel_2_samples[iterator_Sensor] = Adm_Sensor_buffer[1];
		Adm_Sensor_channel_3_samples[iterator_Sensor] = Adm_Sensor_buffer[2];
		Adm_Sensor_channel_4_samples[iterator_Sensor] = Adm_Sensor_buffer[3];

		iterator_Sensor ++;
	}
	else
	{
		Adm_Sensor_grp_val[0] = Adm_ReadAverage(Adm_Sensor_channel_1_samples, ADM_DEBOUNCE_AVG);
		Adm_Sensor_grp_val[1] = Adm_ReadAverage(Adm_Sensor_channel_2_samples, ADM_DEBOUNCE_AVG);
		Adm_Sensor_grp_val[2] = Adm_ReadAverage(Adm_Sensor_channel_3_samples, ADM_DEBOUNCE_AVG);
		Adm_Sensor_grp_val[3] = Adm_ReadAverage(Adm_Sensor_channel_4_samples, ADM_DEBOUNCE_AVG);

		iterator_Sensor = 0;

		Rte_read_RP_InWiperLvlAllowed_InWiperLvlAllowed(&isAllowed);
		if(isAllowed){
			Rte_write_PP_WipperLevel_WipperLevel(Adm_Sensor_grp_val[0]);
		}

		Rte_read_RP_InEnginTempAllowed_InEnginTempAllowed(&isAllowed);
		if(isAllowed){
			Rte_write_PP_EnginTemp_EnginTemp(Adm_Sensor_grp_val[1]);
		}

		Rte_read_RP_InOilPressAllowed_InOilPressAllowed(&isAllowed);
		if(isAllowed){
			Rte_write_PP_OilPress_OilPress(Adm_Sensor_grp_val[2]);
		}
		Rte_read_RP_InBattVoltAllowed_InBattVoltAllowed(&isAllowed);
		if(isAllowed){
			Rte_write_PP_BattVoltage_BattVoltage(Adm_Sensor_grp_val[3]);
		}
	}
}

void Adm_PwSGrp(void)
{


	if(iterator_PwS < ADM_DEBOUNCE_AVG)
	{
		Adc_StartGroupConversion(ADC_IN_OUT_POWER_SUPPLY_GRP);
		Adm_Pws_channel_in_samples[iterator_PwS] = Adm_Pws_buffer[0];
		Adm_Pws_channel_out_samples[iterator_PwS] = Adm_Pws_buffer[1];

		iterator_PwS ++;
	}
	else
	{
		Adm_PwS_grp_val[0] = Adm_ReadAverage(Adm_Pws_channel_in_samples, ADM_DEBOUNCE_AVG);
		Adm_PwS_grp_val[1] = Adm_ReadAverage(Adm_Pws_channel_out_samples, ADM_DEBOUNCE_AVG);

		PwS_in_mv = ((uint32_t)(Adm_PwS_grp_val[0] * 3330) / 4095);
		PwS_out_mv = ((uint32_t)(Adm_PwS_grp_val[1] * 3330) / 4095);

		iterator_PwS = 0;

		Rte_write_PP_InPwS_InPwS((uint16_t)(PwS_in_mv * 6));
		Rte_write_PP_OutPwS_OutPwS((uint16_t)(PwS_out_mv * 6));
	}
}
//void Adm_getChannelSamples(uint16_t* buff, uint8_t nSamples, uint8_t nChannles, uint8_t rank, uint16_t* chBuff){
//	uint8_t i = 0;
//	uint8_t j = 0;
//	for(i = rank; i < nSamples; i+= nChannles){
//		chBuff[j] = buff[i];
//		j++;
//	}
//}

uint16_t Adm_ReadAverage(uint16_t* buff, uint8_t nSamples){
	uint8_t i = 0;
	uint32_t result = 0;
	for(i = 0; i < nSamples; i++){
		result += buff[i];
	}
	result /= ((uint16_t)nSamples);
	return (uint16_t)result;
}

//uint16_t Adm_get_in_out_power_supply_mV(uint8_t direction){
//
//	if (Adc_SetupResultBuffer(ADC_IN_OUT_POWER_SUPPLY_GRP, Adm_in_out_buffer) == E_OK){
//	  Adc_StartGroupConversion(ADC_IN_OUT_POWER_SUPPLY_GRP);
//	}
//	while(Adc_GetGroupStatus(ADC_IN_OUT_POWER_SUPPLY_GRP) != ADC_STREAM_COMPLETED);
//
//	// in_PwS = 0; out_PwS = 1
//	if(ADM_PWS_DIRECTION_IN == direction)
//	{
//		Adm_getChannelSamples(Adm_in_out_buffer, ADC_IN_OUT_POWER_SUPPLY_GRP_SAMPLES, ADC_IN_OUT_POWER_SUPPLY_GRP_N_CHANNELS, ADC_IN_POWER_SUPPLY_CHANNEL, Adm_in_or_out_buffer);
//	}
//	else if (ADM_PWS_DIRECTION_OUT == direction)
//	{
//		Adm_getChannelSamples(Adm_in_out_buffer, ADC_IN_OUT_POWER_SUPPLY_GRP_SAMPLES, ADC_IN_OUT_POWER_SUPPLY_GRP_N_CHANNELS, ADC_OUT_POWER_SUPPLY_CHANNEL, Adm_in_or_out_buffer);
//	}
//	else
//	{
//		// Do Nothing
//	}
//
//	uint16_t adm_in_voltage_raw = Adm_ReadAverage(Adm_in_or_out_buffer, ADC_IN_OUT_POWER_SUPPLY_GRP_N_SAMPLES);
//
//	Adc_StopGroupConversion(ADC_IN_OUT_POWER_SUPPLY_GRP);
//	uint32_t result_mV = ((uint32_t)(adm_in_voltage_raw * 3330) / 4095);
//
//	return (uint16_t)(result_mV * 6);
//}


//uint16_t Adm_ReadSensorGrp_raw(uint8_t activeChannel)
//{
//	if (Adc_SetupResultBuffer(ADC_IN_SESNORS_GRP, Adm_sensor_grp_buffer) == E_OK){
//		Adc_StartGroupConversion(ADC_IN_SESNORS_GRP);
//	}
//
//	while(Adc_GetGroupStatus(ADC_IN_SESNORS_GRP) != ADC_STREAM_COMPLETED);
//
//	switch(activeChannel)
//	{
//		case ADM_TEMPERATURE_SENSOR_CHANNEL :
//			Adm_getChannelSamples(Adm_sensor_grp_buffer, ADC_IN_SESNORS_GRP_SAMPLES, ADC_IN_SESNORS_GRP_N_CHANNELS, ADC_TEMPERATUR_SENSOR_CHANNEL, Adm_active_channel_buffer);
//			break;
//		case ADM_LUMINOSITY_SENSOR_CHANNEL :
//			Adm_getChannelSamples(Adm_sensor_grp_buffer, ADC_IN_SESNORS_GRP_SAMPLES, ADC_IN_SESNORS_GRP_N_CHANNELS, ADC_LUMINOSITY_SENSOR_CHANNEL, Adm_active_channel_buffer);
//			break;
//		default :
//			// Do Nothing !!
//			break;
//	}
//
//	uint16_t Sensor_data = Adm_ReadAverage(Adm_active_channel_buffer, ADC_IN_SESNORS_GRP_N_SAMPLES);
//
//	// TODO : to get meaningful data we need to calibrate our sensor manually and apply the necessary changes to get the right values !!
//	Adc_StopGroupConversion(ADC_IN_SESNORS_GRP);
//
//	return Sensor_data;
//}

void Adm_Init(void){

	Adc_Init(&Adc_Config);

	Adc_SetupResultBuffer(ADC_IN_OUT_POWER_SUPPLY_GRP, Adm_Pws_buffer);

	Adc_SetupResultBuffer(ADC_IN_SESNORS_GRP, Adm_Sensor_buffer);
}

void Adm_task_5ms(void){

	Adm_SensorGrp();
	Adm_PwSGrp();
}
void Adm_Deinit(void){
	// STUB empty Deinit function
}
