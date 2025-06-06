/* AUTO-GENERATED 2025-06-06T01:37:51 */
#include "Port_Cfg.h"

static const Port_PinConfigType Port_PinConfigs[] = {
    {GPIOA, GPIO_PIN_5, PORT_PIN_MODE_GPIO, PORT_PIN_OUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW},
    {GPIOC, GPIO_PIN_13, PORT_PIN_MODE_GPIO, PORT_PIN_IN, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW},
};

const Port_ConfigType Port_Config = {
    .PinCfgArr = Port_PinConfigs,
    .NumPins   = 2u
};
