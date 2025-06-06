#ifndef PORT_H_
#define PORT_H_

#include "stm32f4xx_hal.h"

typedef uint8_t  Port_PinType;

typedef enum {
    PORT_PIN_IN  = 0u,
    PORT_PIN_OUT = 1u
} Port_PinDirectionType;

typedef enum {

    PORT_PIN_MODE_GPIO = 0u,
	PORT_PIN_MODE_ANALOG,
	PORT_PIN_MODE_AF0,
	PORT_PIN_MODE_AF1,
	PORT_PIN_MODE_AF2,
	PORT_PIN_MODE_AF3,
	PORT_PIN_MODE_AF4,
	PORT_PIN_MODE_AF5,
	PORT_PIN_MODE_AF6,
	PORT_PIN_MODE_AF7,
	PORT_PIN_MODE_AF8,
	PORT_PIN_MODE_AF9,
	PORT_PIN_MODE_AF10,
	PORT_PIN_MODE_AF11,
	PORT_PIN_MODE_AF12,
	PORT_PIN_MODE_AF13,
	PORT_PIN_MODE_AF14,
	PORT_PIN_MODE_AF15
} Port_PinModeType;

/* One pin description */
typedef struct {
    GPIO_TypeDef*          Port;     /* GPIOA … GPIOH */
    uint16_t               PinMask;  /* GPIO_PIN_x */
    Port_PinModeType       Mode;     /* only GPIO for now                */
    Port_PinDirectionType  Direction;/* in / out                         */
    uint32_t               Pull;     /* GPIO_NOPULL / PULLUP / PULLDOWN  */
    uint32_t               Speed;    /* GPIO_SPEED_FREQ_xx               */
    /*TODO:  add this field DirectionChangeable */
} Port_PinConfigType;

/* Whole configuration object */
typedef struct {
    const Port_PinConfigType* PinCfgArr;
    uint8_t                   NumPins;
} Port_ConfigType;

/* ------------ Public API ------------------ */
void Port_Init(const Port_ConfigType *CfgPtr);
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
void Port_RefreshPortDirection (void);
void Port_SetPinMode (Port_PinType Pin, Port_PinModeType Mode);

/* You will export the single configuration object from the cfg header */
extern const Port_ConfigType Port_Config;

#endif /* PORT_H_ */
