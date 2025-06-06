#ifndef DIO_DEMO_CONFIG_H_
#define DIO_DEMO_CONFIG_H_

#include "Dio.h"

/* Application-level symbolic names */
#define DIO_CHANNEL_LED   0u   /* maps to PA5  */
#define DIO_CHANNEL_BTN   1u   /* maps to PC13 */

extern GPIO_TypeDef* Dio_GpioPortMap[8];
extern const Dio_ConfigType Dio_Config;   /* definition lives in .c */
extern const Dio_ChannelGroupType Dio_ChannelGroup;

#endif /* DIO_DEMO_CONFIG_H_ */
