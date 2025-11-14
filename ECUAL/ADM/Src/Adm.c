/*
 * Adm.c
 *
 *  Created on: Nov 1, 2025
 *      Author: Lenovo X13
 */


#include "Adm.h"

/* the Adc_Read API returns a on buffer of n*m length but to get the samples of a specific channel in a group we use this API */
static uint16_t Adm_in_out_buffer[ADC_IN_OUT_POWER_SUPPLY_GRP_SAMPLES];
static uint16_t Adm_in_or_out_buffer[ADC_IN_OUT_POWER_SUPPLY_GRP_N_SAMPLES];

static uint16_t Adm_sensor_grp_buffer[ADC_IN_SESNORS_GRP_SAMPLES];
static uint16_t Adm_active_channel_buffer[ADC_IN_SESNORS_GRP_N_SAMPLES];

void Adm_getChannelSamples(uint16_t* buff, uint8_t nSamples, uint8_t nChannles, uint8_t rank, uint16_t* chBuff){
	uint8_t i = 0;
	uint8_t j = 0;
	for(i = rank; i < nSamples; i+= nChannles){
		chBuff[j] = buff[i];
		j++;
	}
}

uint16_t Adm_ReadAverage(uint16_t* buff, uint8_t nSamples){
	uint8_t i = 0;
	uint32_t result = 0;
	for(i = 0; i < nSamples; i++){
		result += buff[i];
	}
	result /= ((uint16_t)nSamples);
	return (uint16_t)result;
}

uint16_t Adm_get_in_out_power_supply_mV(uint8_t direction){

	if (Adc_SetupResultBuffer(ADC_IN_OUT_POWER_SUPPLY_GRP, Adm_in_out_buffer) == E_OK){
	  Adc_StartGroupConversion(ADC_IN_OUT_POWER_SUPPLY_GRP);
	}
	while(Adc_GetGroupStatus(ADC_IN_OUT_POWER_SUPPLY_GRP) != ADC_STREAM_COMPLETED);

	// in_PwS = 0; out_PwS = 1
	if(ADM_PWS_DIRECTION_IN == direction)
	{
		Adm_getChannelSamples(Adm_in_out_buffer, ADC_IN_OUT_POWER_SUPPLY_GRP_SAMPLES, ADC_IN_OUT_POWER_SUPPLY_GRP_N_CHANNELS, ADC_IN_POWER_SUPPLY_CHANNEL, Adm_in_or_out_buffer);
	}
	else if (ADM_PWS_DIRECTION_OUT == direction)
	{
		Adm_getChannelSamples(Adm_in_out_buffer, ADC_IN_OUT_POWER_SUPPLY_GRP_SAMPLES, ADC_IN_OUT_POWER_SUPPLY_GRP_N_CHANNELS, ADC_OUT_POWER_SUPPLY_CHANNEL, Adm_in_or_out_buffer);
	}
	else
	{
		// Do Nothing
	}

	uint16_t adm_in_voltage_raw = Adm_ReadAverage(Adm_in_or_out_buffer, ADC_IN_OUT_POWER_SUPPLY_GRP_N_SAMPLES);

	Adc_StopGroupConversion(ADC_IN_OUT_POWER_SUPPLY_GRP);
	uint32_t result_mV = ((uint32_t)(adm_in_voltage_raw * 3330) / 4095);

	return (uint16_t)(result_mV * 6);
}


uint16_t Adm_ReadSensorGrp_raw(uint8_t activeChannel)
{
	if (Adc_SetupResultBuffer(ADC_IN_SESNORS_GRP, Adm_sensor_grp_buffer) == E_OK){
		Adc_StartGroupConversion(ADC_IN_SESNORS_GRP);
	}

	while(Adc_GetGroupStatus(ADC_IN_SESNORS_GRP) != ADC_STREAM_COMPLETED);

	switch(activeChannel)
	{
		case ADM_TEMPERATURE_SENSOR_CHANNEL :
			Adm_getChannelSamples(Adm_sensor_grp_buffer, ADC_IN_SESNORS_GRP_SAMPLES, ADC_IN_SESNORS_GRP_N_CHANNELS, ADC_TEMPERATUR_SENSOR_CHANNEL, Adm_active_channel_buffer);
			break;
		case ADM_LUMINOSITY_SENSOR_CHANNEL :
			Adm_getChannelSamples(Adm_sensor_grp_buffer, ADC_IN_SESNORS_GRP_SAMPLES, ADC_IN_SESNORS_GRP_N_CHANNELS, ADC_LUMINOSITY_SENSOR_CHANNEL, Adm_active_channel_buffer);
			break;
		default :
			// Do Nothing !!
			break;
	}

	uint16_t Sensor_data = Adm_ReadAverage(Adm_active_channel_buffer, ADC_IN_SESNORS_GRP_N_SAMPLES);

	// TODO : to get meaningful data we need to calibrate our sensor manually and apply the necessary changes to get the right values !!
	Adc_StopGroupConversion(ADC_IN_SESNORS_GRP);

	return Sensor_data;
}

void Adm_Init(void){

	Adc_Init(&Adc_Config);

}

void Adm_Deinit(void){
	// STUB empty Deinit function
}
