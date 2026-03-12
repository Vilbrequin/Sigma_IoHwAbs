#ifndef DIO_DEMO_CONFIG_H_
#define DIO_DEMO_CONFIG_H_

#include "Dio.h"

// DIGITAL OUTPUT PINS
#define DIO_PIN_DO_WASHER_LED				0U // Green Internal LED

// DIGITAL INPUT PINS
#define DIO_PIN_DI_HIGH_BEAM_BTN			1U // Front Right Button
#define DIO_PIN_DI_LOW_BEAM_BTN				2U // Front Left Button
#define DIO_PIN_DI_WASHER_BTN				3U // Back Right Button


#define DIO_NUM_PORTS						2U
#define DIO_NUM_CHANNELS					4U

extern GPIO_TypeDef* Dio_GpioPortMap[DIO_NUM_PORTS];
extern const Dio_ConfigType Dio_Config;   /* definition lives in .c */
extern const Dio_ChannelGroupType Dio_ChannelGroup;

#endif /* DIO_DEMO_CONFIG_H_ */
