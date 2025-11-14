#include "Dio_Cfg.h"

/* Local lookup table – internal linkage */
static const Dio_ChannelConfigType Dio_ChannelCfgs[] =
{
    {GPIOA, GPIO_PIN_5},   /* LED */
    {GPIOC, GPIO_PIN_10},   /* LED */
    {GPIOC, GPIO_PIN_11},   /* LED */
    {GPIOC, GPIO_PIN_12},   /* LED */

    {GPIOC, GPIO_PIN_13},   /* LED */
    {GPIOC, GPIO_PIN_14},   /* LED */
    {GPIOC, GPIO_PIN_15},   /* LED */
    {GPIOH, GPIO_PIN_0},   /* LED */
};

GPIO_TypeDef* Dio_GpioPortMap[3] = { GPIOA, GPIOC, GPIOH};

const Dio_ConfigType Dio_Config =
{
    .ChannelCfgArr = Dio_ChannelCfgs,
    .NumChannels   = DIO_NUM_CHANNELS
};

