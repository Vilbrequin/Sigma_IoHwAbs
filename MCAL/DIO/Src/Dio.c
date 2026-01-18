/*
 * Dio.c
 *
 *  Created on: May 25, 2025
 *      Author: HSM
 */


#include "Dio_Cfg.h"
#include "Dio.h"

#define TO_SET(current, desired) 	((~current) & desired)
#define TO_RESET(current, desired)	(current & (~desired))

static const Dio_ConfigType *Dio_Cfg = &Dio_Config;

void Dio_Init(const Dio_ConfigType *CfgPtr)
{
    if (CfgPtr != NULL) { Dio_Cfg = CfgPtr; }
}

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ch)
{
    if (ch >= Dio_Cfg->NumChannels) { return STD_LOW; }

    const Dio_ChannelConfigType *c = &Dio_Cfg->InChannelCfgArr[ch];
    return (HAL_GPIO_ReadPin(c->Port, c->PinMask) == GPIO_PIN_SET) ? STD_HIGH : STD_LOW;
}

void Dio_WriteChannel(Dio_ChannelType ch, Dio_LevelType lvl)
{
    if (ch >= Dio_Cfg->NumChannels) { return; }

    const Dio_ChannelConfigType *c = &Dio_Cfg->OutChannelCfgArr[ch];
    HAL_GPIO_WritePin(c->Port, c->PinMask, (lvl == STD_HIGH) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

Dio_LevelType Dio_FlipChannel(Dio_ChannelType ch)
{
    if (ch >= Dio_Cfg->NumChannels) { return STD_LOW; }

    const Dio_ChannelConfigType *c = &Dio_Cfg->OutChannelCfgArr[ch];

    uint32_t odr = c->Port->ODR;
    uint32_t pin = c->PinMask;

    if (odr & pin) {
        c->Port->BSRR = (uint32_t)pin << 16u;   /* reset bit */
        return STD_LOW;
    } else {
        c->Port->BSRR = pin;                    /* set bit   */
        return STD_HIGH;
    }
}

Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId)
{
    if (PortId >= DIO_MAX_PORT_NUMBER) { return (Dio_PortLevelType)0u; }

	return (Dio_PortLevelType)(Dio_GpioPortMap[PortId]->IDR & 0xFFFFu);
}


void Dio_WritePort (Dio_PortType PortId, Dio_PortLevelType Level)
{
	if (PortId >= DIO_MAX_PORT_NUMBER) { return; }

	volatile GPIO_TypeDef* port = Dio_GpioPortMap[PortId];

	uint32_t desired = Level & 0xFFFFu;
	uint32_t current = (port->ODR) & 0xFFFFu;

	uint32_t to_set = TO_SET(current, desired);
	uint32_t to_reset = TO_RESET(current, desired);

	port->BSRR = ((to_reset << 16) | (to_set));
}
Dio_PortLevelType Dio_ReadChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr)
{
	if (ChannelGroupIdPtr == NULL) { return 0u; }

	volatile GPIO_TypeDef* port = ChannelGroupIdPtr->Port;
	uint32_t mask  = (uint32_t)ChannelGroupIdPtr->GroupMask;
	uint32_t offset = (uint32_t)ChannelGroupIdPtr->Offset;

	if (0 == mask){ return 0u; }

	return (Dio_PortLevelType)((port->IDR & mask) >> offset);
}
/*
 * [SWS_Dio_00091]:
 * The function Dio_WriteChannelGroup shall do the shifting so
 * that the values written by the function are aligned to the LSB.
 * means that bit 0 of Level always represents the least-significant pin in the group,
 * no matter where that pin sits inside the port.
 * */
void Dio_WriteChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level)
{
	if (ChannelGroupIdPtr == NULL) { return; }

	volatile GPIO_TypeDef* port = ChannelGroupIdPtr->Port;
	uint32_t mask  = (uint32_t)ChannelGroupIdPtr->GroupMask;
	uint32_t offset = (uint32_t)ChannelGroupIdPtr->Offset;

	if (0 == mask){ return; }

	uint32_t current = (port->ODR) & mask;
	uint32_t desired = ((uint32_t)Level << offset) & mask;

	uint32_t to_set = TO_SET(current, desired);
	uint32_t to_reset = TO_RESET(current, desired);

	port->BSRR = ((to_reset << 16) | (to_set));
}

void Dio_MaskedWritePort (Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask)
{
	if(0 == Mask) { return; }

	if (PortId >= DIO_MAX_PORT_NUMBER) { return; }

	volatile GPIO_TypeDef* port = Dio_GpioPortMap[PortId];

	uint32_t pos   = __builtin_ctz((uint32_t)Mask);
	uint32_t current = (port->ODR) & (uint32_t)Mask;
	uint32_t desired = ((uint32_t)Level << pos) & (uint32_t)Mask;

	uint32_t to_set = TO_SET(current, desired);
	uint32_t to_reset = TO_RESET(current, desired);

	port->BSRR = ((to_reset << 16) | (to_set));

}
