#ifndef DIO_DEMO_CONFIG_H_
#define DIO_DEMO_CONFIG_H_

#include "Dio.h"

// DIGITAL OUTPUT PINS
#define DIO_PIN_DO_LAMP					    0U // Green Internal LED
#define DIO_PIN_DO_FAN						1U
#define DIO_PIN_DO_RI_TI					2U
#define DIO_PIN_DO_LE_TI					3U

// DIGITAL INPUT PINS
#define DIO_PIN_DI_FRI_WIN_BTN				4U // Front Right Button
#define DIO_PIN_DI_FLE_WIN_BTN				5U // Front Left Button
#define DIO_PIN_DI_BRE_WIN_BTN				6U // Back Right Button
#define DIO_PIN_DI_BLE_WIN_BTN				7U // Back Left Button

#define DIO_NUM_PORTS						3U
#define DIO_NUM_CHANNELS					8U

extern GPIO_TypeDef* Dio_GpioPortMap[DIO_NUM_PORTS];
extern const Dio_ConfigType Dio_Config;   /* definition lives in .c */
extern const Dio_ChannelGroupType Dio_ChannelGroup;

#endif /* DIO_DEMO_CONFIG_H_ */
