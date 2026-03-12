/*
 * Port.c
 *
 *  Created on: May 25, 2025
 *      Author: HSM
 */


#include "Port.h"
#include "Port_Cfg.h"

/* ------------------------- Enable GPIO clock once per port ------------------------- */
static void Port_EnableClock(GPIO_TypeDef *port)
{
    if      (port == GPIOA) { __HAL_RCC_GPIOA_CLK_ENABLE(); }
    else if (port == GPIOB) { __HAL_RCC_GPIOB_CLK_ENABLE(); }
    else if (port == GPIOC) { __HAL_RCC_GPIOC_CLK_ENABLE(); }
    else if (port == GPIOD) { __HAL_RCC_GPIOD_CLK_ENABLE(); }
    else if (port == GPIOE) { __HAL_RCC_GPIOE_CLK_ENABLE(); }
    else if (port == GPIOF) { __HAL_RCC_GPIOF_CLK_ENABLE(); }
    else if (port == GPIOG) { __HAL_RCC_GPIOG_CLK_ENABLE(); }
    else if (port == GPIOH) { __HAL_RCC_GPIOH_CLK_ENABLE(); }
}

void Port_Init(const Port_ConfigType *CfgPtr)
{
    if (CfgPtr == NULL) { return; } /* No DET yet !*/

    for (uint8_t i = 0u; i < CfgPtr->NumPins; ++i) {
        const Port_PinConfigType *pcfg = &CfgPtr->PinCfgArr[i];
        uint32_t mode = GPIO_MODE_INPUT; /* Default mode after reset */
        uint32_t alternate = 0;

        /* Enable the GPIO AHB clock */
        Port_EnableClock(pcfg->Port);

        switch(pcfg->Mode){
        case PORT_PIN_MODE_GPIO:
        	mode = (pcfg->Direction == PORT_PIN_OUT) ? GPIO_MODE_OUTPUT_PP : GPIO_MODE_INPUT;
        	break;
        case PORT_PIN_MODE_ANALOG:
        	mode = GPIO_MODE_ANALOG;
        	break;
        default:
        	// TODO: handle the case where the Mode is out of range (set the default value to Input as after Reset)!
        	mode = GPIO_MODE_AF_PP;
        	/* GPIO_InitTypeDef.Alternate is defined as uint32_t and Port_PinModeType is an enum generally an int type chosen by the compiler
        	 * Misra-C prohibits implicit conversions for signed to unsigned and vice-versa (Rule 10.1)
        	 * The Mask guarantees that the alternate value is 4-bits, so no undefined behaviour */
        	alternate = (uint32_t)(pcfg->Mode - PORT_PIN_MODE_AF0) & 0xF;
        	break;
        }


        /* 2) Prepare HAL structure */
        GPIO_InitTypeDef init = {
            .Pin   = pcfg->PinMask,
            .Mode  = mode,
            .Pull  = pcfg->Pull,
            .Speed = pcfg->Speed,
			.Alternate = alternate
        };

        /* 3) Call HAL */
        HAL_GPIO_Init(pcfg->Port, &init);
    }
}

void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
    if (Pin >= Port_Config.NumPins) { return; }

    volatile GPIO_TypeDef *port  = Port_Config.PinCfgArr[Pin].Port;
    uint32_t      mask  		 = Port_Config.PinCfgArr[Pin].PinMask;
    uint32_t      pos            = __builtin_ctz(mask); /* Returns the number of trailing 0-bits in x, starting at the least significant bit position*/

    /* Set Direction using MODER Register */
    uint32_t moder = port->MODER;
    moder &= ~(0x3u << (pos * 2u));
    moder |= ((Direction == PORT_PIN_OUT) ? 0x1u : 0x0u) << (pos * 2u);
    port->MODER = moder;
}

void Port_RefreshPortDirection (void){

	for (uint8_t i = 0u; i < Port_Config.NumPins; ++i){
		const Port_PinConfigType 		*pcfg 		= &Port_Config.PinCfgArr[i];
		GPIO_TypeDef 					*port 		= pcfg->Port;
		uint32_t      					pos   		= __builtin_ctz(pcfg->PinMask);

		uint32_t moder = port->MODER;
		moder &= ~(0x3u << (pos * 2u));
		moder |= ((pcfg->Direction == PORT_PIN_OUT) ? 0x1u : 0x0u) << (pos * 2u);
		port->MODER = moder;
	}
}


void Port_SetPinMode (Port_PinType Pin, Port_PinModeType Mode)
{

	const Port_PinConfigType *pcfg = &Port_Config.PinCfgArr[Pin];

	uint32_t mode = GPIO_MODE_INPUT;
	uint32_t alternate = 0;

	switch(Mode){
	case PORT_PIN_MODE_GPIO:
		mode = (pcfg->Direction == PORT_PIN_OUT) ? GPIO_MODE_OUTPUT_PP : GPIO_MODE_INPUT;
		break;
	case PORT_PIN_MODE_ANALOG:
		mode = GPIO_MODE_ANALOG;
		break;
	default:
		// TODO: handle the case where the Mode is out of range (set the default value to Input as after Reset)!
		mode = GPIO_MODE_AF_PP;
		alternate = (Mode - PORT_PIN_MODE_AF0);
		break;
	}

	GPIO_InitTypeDef init = {
		.Pin   = pcfg->PinMask,
		.Mode  = mode,
		.Pull  = pcfg->Pull,
		.Speed = pcfg->Speed,
		.Alternate = alternate
	};

	HAL_GPIO_Init(pcfg->Port, &init);
}
