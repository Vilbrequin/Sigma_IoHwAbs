/*
 * Adc_Cfg.c
 *
 *  Created on: Jul 26, 2025
 *      Author: HSM
 */

#include "Adc_Cfg.h"

static const Adc_CommonCfgType commonPrescaler = {.AdcPrescaler = ADC_PRESCALER_DIVIDED_BY_8 };

static Adc_InstanceCfgType Instatces[] = {
		{.AdcInstance = ADC_1, .AdcResolution = ADC_RESOLUTION_12_BIT, .AdcAlignment = ADC_ALIGN_RIGHT},
		{.AdcInstance = ADC_2, .AdcResolution = ADC_RESOLUTION_12_BIT, .AdcAlignment = ADC_ALIGN_RIGHT}
};

static const Adc_ChannelCfgType channles_grp_1_adc_1[] = {
		{.ChannelId = ADC_CH1, .SampleTime = ADC_SAMPLE_TIME_3_CYCLES, .Rank = 1},
		{.ChannelId = ADC_CH4, .SampleTime = ADC_SAMPLE_TIME_3_CYCLES, .Rank = 2}
};

static const Adc_ChannelCfgType channles_grp_1_adc_2[] = {
		{.ChannelId = ADC_CH12, .SampleTime = ADC_SAMPLE_TIME_15_CYCLES, .Rank = 1},
		{.ChannelId = ADC_CH13, .SampleTime = ADC_SAMPLE_TIME_15_CYCLES, .Rank = 2},
		{.ChannelId = ADC_CH14, .SampleTime = ADC_SAMPLE_TIME_15_CYCLES, .Rank = 3},
		{.ChannelId = ADC_CH15, .SampleTime = ADC_SAMPLE_TIME_15_CYCLES, .Rank = 4},
};




static const Adc_GroupCfgType groupes []  = {
		// PwS ADC Grp
		{
			.InstanceId = 0,
			.GroupId = ADC_IN_OUT_POWER_SUPPLY_GRP,
			.ChannelList = channles_grp_1_adc_1,
			.NumChannels = ADC_IN_OUT_POWER_SUPPLY_GRP_N_CHANNELS,
			.ConversionMode = ADC_CONV_MODE_ONESHOT,
			.TriggSrc = ADC_TRIGG_SRC_SW,
			.AccessMode = ADC_ACCESS_MODE_SINGLE,
			.NumSample = ADC_IN_OUT_POWER_SUPPLY_GRP_N_SAMPLES,
			.BufferMode = ADC_STREAM_BUFFER_LINEAR
		},
		// Sensors ADc Grp
		{
			.InstanceId = 1,
			.GroupId = ADC_IN_SESNORS_GRP,
			.ChannelList = channles_grp_1_adc_2,
			.NumChannels = ADC_IN_SESNORS_GRP_N_CHANNELS,
			.ConversionMode = ADC_CONV_MODE_ONESHOT,
			.TriggSrc = ADC_TRIGG_SRC_SW,
			.AccessMode = ADC_ACCESS_MODE_SINGLE,
			.NumSample = ADC_IN_SESNORS_GRP_N_SAMPLES,
			.BufferMode = ADC_STREAM_BUFFER_LINEAR
		}
};

const Adc_ConfigType Adc_Config = {
		.AdcCommon = commonPrescaler,
		.AdcInstanceCfg = Instatces,
		.NumInstances = 2,
		.AdcGroupCfg = groupes,
		.NumGroups = 2
};
