#ifndef DIO_H_
#define DIO_H_

#include "stm32f4xx_hal.h"

typedef uint8_t  Dio_ChannelType;

typedef uint8_t  Dio_LevelType;

typedef enum
{
    DIO_PORT_A = 0u,
    DIO_PORT_B,
    DIO_PORT_C,
    DIO_PORT_D,
    DIO_PORT_E,
    DIO_PORT_F,
    DIO_PORT_G,
    DIO_PORT_H,
	DIO_MAX_PORT_NUMBER
} Dio_PortType;


typedef uint16_t Dio_PortLevelType;

#define STD_LOW   (Dio_LevelType)0u
#define STD_HIGH  (Dio_LevelType)1u

typedef struct {
    GPIO_TypeDef *Port;     /* GPIOA … GPIOH */
    uint16_t     PinMask;  /* GPIO_PIN_x */
} Dio_ChannelConfigType;

typedef struct {
	GPIO_TypeDef *Port;		 /* GPIOA … GPIOH */
	uint16_t	 GroupMask; /* GPIO_PIN_x | GPIO_PIN_y | ...*/
    uint8_t		 Offset;   /* The position of the Channel Group on the port counted from the LSB */
}Dio_ChannelGroupType;

typedef struct {
    const Dio_ChannelConfigType *InChannelCfgArr;
    const Dio_ChannelConfigType *OutChannelCfgArr;
    uint8_t                      NumChannels;
} Dio_ConfigType;

/* ----------------------------- Public API ----------------------------- */
void           Dio_Init(const Dio_ConfigType *CfgPtr);
Dio_LevelType  Dio_ReadChannel(Dio_ChannelType ChannelId);
void           Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);
Dio_LevelType  Dio_FlipChannel(Dio_ChannelType ChannelId);
Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId);
void Dio_WritePort (Dio_PortType PortId, Dio_PortLevelType Level);
Dio_PortLevelType Dio_ReadChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr);
void Dio_WriteChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level);
void Dio_MaskedWritePort (Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask);

/* One global config handle declared in the cfg header */
extern const Dio_ChannelGroupType Dio_ChannelGroup;
extern const Dio_ConfigType Dio_Config;

#endif /* DIO_H_ */
