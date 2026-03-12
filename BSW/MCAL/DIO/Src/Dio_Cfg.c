#include "Dio_Cfg.h"

/* Local lookup table – internal linkage */
static const Dio_ChannelConfigType Dio_OutChannelCfgs[] =
{
    {GPIOA, GPIO_PIN_5},   	/* 	DO : Washer (G LED)	*/
};
static const Dio_ChannelConfigType Dio_InChannelCfgs[] =
{
    {GPIOC, GPIO_PIN_13},   /* 	DI : High Beam Btn	*/
    {GPIOC, GPIO_PIN_14},   /*	DI : Low Beam Btn 	*/
    {GPIOC, GPIO_PIN_15},   /* 	DI : Washer Btn 	*/
};

GPIO_TypeDef* Dio_GpioPortMap[2] = { GPIOA, GPIOC};

const Dio_ConfigType Dio_Config =
{
    .InChannelCfgArr = Dio_InChannelCfgs,
	.OutChannelCfgArr = Dio_OutChannelCfgs,
    .NumChannels   = DIO_NUM_CHANNELS
};

