#include "Dio_Cfg.h"
#include "Iom_Cfg.h"

static const Iom_InputConfigType Iom_InputCfgList[IOM_NUM_INPUTS] =
{
    { DIO_CHANNEL_BTN, TRUE,  4u, FALSE}
};

static const Iom_OutputConfigType Iom_OutputCfgList[IOM_NUM_OUTPUT] = {
		{DIO_CHANNEL_LED, IOM_ACTIVE_HIGH, IOM_OUT_OFF}
};

const Iom_ConfigType Iom_InputCfg = {
		.InputConfig = Iom_InputCfgList,
		.OutputConfig = Iom_OutputCfgList,
		.NumInputs = IOM_NUM_INPUTS,
		.NumOutputs = IOM_NUM_OUTPUT
};

Iom_ChannelStateType Iom_ChannelState[IOM_NUM_INPUTS] = { {0} };
