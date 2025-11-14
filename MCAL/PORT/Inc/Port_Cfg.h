/* AUTO-GENERATED  2025-07-02T02:05:14
 * Edit C:\Users\HSM\STM32CubeIDE\workspace_1.18.1\nucleo-f446re-mcal-draft\Config\Port\PortPins.yaml instead of this file.
 */
#ifndef PORT_CFG_H_
#define PORT_CFG_H_

#include "Port.h"

// POWER SUPPLY PINS
#define PORT_PIN_INPUT_POWER_SUPPLY			0U // PA1 : ADC123_IN1
#define PORT_PIN_OUTPUT_POWER_SUPPLY		1U // PA2 : ADC123_IN2

// DIGITAL OUTPUT PINS
#define PORT_PIN_DO_LAMP					2U // PA5 : Green Internal LED
#define PORT_PIN_DO_FAN						3U
#define PORT_PIN_DO_RI_TI					4U
#define PORT_PIN_DO_LE_TI					5U

// DIGITAL INPUT PINS
#define PORT_PIN_DI_FRI_WIN_BTN				6U // Front Right Button
#define PORT_PIN_DI_FLE_WIN_BTN				7U // Front Left Button
#define PORT_PIN_DI_BRI_WIN_BTN				8U // Back Right Button
#define PORT_PIN_DI_BLE_WIN_BTN				9U // Back Left Button

// PWM OUTPUT PINS
#define PORT_PIN_PWM_HEAD_LAMPS				10U //
#define PORT_PIN_PWM_RIGHT_TI				11U //
#define PORT_PIN_PWM_LEFT_TI				12U //


// ANALOG INPUT PINS
#define PORT_PIN_AIN_TEMP_SENSOR			13U //
#define PORT_PIN_AIN_LUM_SENSOR				14U //


extern const Port_ConfigType Port_Config;

#endif /* PORT_CFG_H_ */
