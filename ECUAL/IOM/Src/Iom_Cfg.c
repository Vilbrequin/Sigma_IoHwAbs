#include "Dio_Cfg.h"
#include "Iom_Cfg.h"

static const Iom_OutputConfigType Iom_OutputCfgList[IOM_NUM_OUTPUT] = {
		{IOM_CH_WASHER_LED, IOM_ACTIVE_HIGH, IOM_OUT_OFF},
};

static const Iom_InputConfigType Iom_InputCfgList[IOM_NUM_INPUT] = {
		{IOM_CH_HIGH_BEAM_BTN, TRUE, 3},
		{IOM_CH_LOW_BEAM_BTN, FALSE, 3},
		{IOM_CH_WASHER_BTN, FALSE, 3},
};

const Iom_ConfigType Iom_InputCfg = {
		.InputConfig = Iom_InputCfgList,
		.OutputConfig = Iom_OutputCfgList,
		.NumInputs = IOM_NUM_INPUT,
		.NumOutputs = IOM_NUM_OUTPUT
};

Iom_ChannelStateType Iom_ChannelState[IOM_NUM_INPUT] = { {0} };
