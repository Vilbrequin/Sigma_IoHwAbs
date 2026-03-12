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
#define PORT_PIN_DO_WASHER_LED				2U // PA5 : Washer (G LED)

// DIGITAL INPUT PINS
#define PORT_PIN_DI_HIGH_BEAM_BTN			3U // PC13 : Front Right Button
#define PORT_PIN_DI_LOW_BEAM_BTN			4U // PC14 : Front Left Button
#define PORT_PIN_DI_WASHER_BTN				5U // PC15 : Back Right Button

// PWM OUTPUT PINS
#define PORT_PIN_PWM_HIGH_BEAM				6U // PB4 : HBeam Out
#define PORT_PIN_PWM_LOW_BEAM				7U // PB5 : LBeam Out
#define PORT_PIN_PWM_WIPER					8U // PC8 : Wiper Out


// ANALOG INPUT PINS
#define PORT_PIN_AIN_WIPER_BTN				9U //
#define PORT_PIN_AIN_TEMP_SENSOR			10U //
#define PORT_PIN_AIN_OIL_SENSOR				11U //
#define PORT_PIN_AIN_VBATT_SENSOR			12U //
#define PORT_WIPP_POS_SENSOR				13U //


extern const Port_ConfigType Port_Config;

#endif /* PORT_CFG_H_ */
