/*
 * rte.h
 *
 *  Created on: Jan 15, 2026
 *      Author: Lenovo X13
 */

#ifndef INC_RTE_H_
#define INC_RTE_H_

#include <stdint.h>

typedef struct {
	// DI
	uint8_t 	HighBeamBtnDebounced;
	uint16_t 	HighBeamBtnPressCounter;

	uint8_t 	LowBeamBtnDebounced;
	uint16_t 	LowBeamBtnPressCounter;

	uint8_t 	WasherBtnDebounced;
	uint16_t 	WasherBtnPressCounter;

	// AI
	uint16_t	WipperLevel;
	uint16_t	EnginTemp;
	uint16_t	OilPress;
	uint16_t	BattVoltage;

	uint16_t	InPwS;
	uint16_t	OutPwS;

	// PWM DC
	uint8_t		HighBeamDc;
	uint8_t		LowBeamDc;
	uint8_t		WipperDc;

	// DO
	uint8_t		WasherState;

	// In/Out voltage ranges
	uint8_t		InVoltageRang;
	uint8_t		OutVoltageRang;

	// FVR In Validity
    uint8_t     InHighBeamAllowed;
    uint8_t     InLowBeamAllowed;
    uint8_t     InWasherAllowed;
    uint8_t     InEnginTempAllowed;
    uint8_t     InOilPressAllowed;
    uint8_t     InBattVoltAllowed;
    uint8_t     InWiperLvlAllowed;

    // FVR Out Validity
    uint8_t     OutWasherAllowed;
    uint8_t     OutHighBeamAllowed;
    uint8_t     OutLowBeamAllowed;
    uint8_t     OutWiperAllowed;

}StructRteType;

extern volatile StructRteType StructRte;

#define Rte_write_data(dataElement, value)		(StructRte.dataElement = (value))
#define Rte_read_data(dataElement, pValue)		(*(pValue) = StructRte.dataElement)

#endif /* INC_RTE_H_ */
