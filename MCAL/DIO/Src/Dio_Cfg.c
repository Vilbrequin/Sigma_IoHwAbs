#include "Dio_Cfg.h"

/* Local lookup table – internal linkage */
static const Dio_ChannelConfigType Dio_ChannelCfgs[] =
{
    {GPIOA, GPIO_PIN_5},   /* LED */
    {GPIOC, GPIO_PIN_13}   /* USER button */
};

GPIO_TypeDef* Dio_GpioPortMap[8] = { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH};

const Dio_ConfigType Dio_Config =
{
    .ChannelCfgArr = Dio_ChannelCfgs,
    .NumChannels   = (uint8_t)(sizeof(Dio_ChannelCfgs) /
                               sizeof(Dio_ChannelCfgs[0]))
};

const Dio_ChannelGroupType Dio_ChannelGroup = {
		.Port = GPIOA,
		.GroupMask = 0x20, /* PC14 - PC13*/
		.Offset = 5
};
