/*
 * Fvr_Rte.h
 *
 *  Created on: Nov 8, 2025
 *      Author: Lenovo X13
 */

#ifndef INC_FVR_RTE_H_
#define INC_FVR_RTE_H_

#include "rte.h"


#define Rte_Read_RP_InVoltageRang_InVoltageRang(pValue)					Rte_read_data(InVoltageRang, pValue)
#define Rte_Read_RP_OutVoltageRang_OutVoltageRang(pValue)				Rte_read_data(OutVoltageRang, pValue)


#define Rte_write_PP_InHighBeamAllowed_InHighBeamAllowed(value)			Rte_write_data(InHighBeamAllowed, value)
#define Rte_write_PP_InLowBeamAllowed_InLowBeamAllowed(value)			Rte_write_data(InLowBeamAllowed, value)
#define Rte_write_PP_InWasherAllowed_InWasherAllowed(value)				Rte_write_data(InWasherAllowed, value)
#define Rte_write_PP_InEnginTempAllowed_InEnginTempAllowed(value)		Rte_write_data(InEnginTempAllowed, value)
#define Rte_write_PP_InOilPressAllowed_InOilPressAllowed(value)			Rte_write_data(InOilPressAllowed, value)
#define Rte_write_PP_InBattVoltAllowed_InBattVoltAllowed(value)			Rte_write_data(InBattVoltAllowed, value)
#define Rte_write_PP_InWiperLvlAllowed_InWiperLvlAllowed(value)			Rte_write_data(InWiperLvlAllowed, value)
#define Rte_write_PP_InWiperPosAllowed_InWiperPosAllowed(value)			Rte_write_data(InWiperPosAllowed, value)

#define Rte_write_PP_OutWasherAllowed_OutWasherAllowed(value)			Rte_write_data(OutWasherAllowed, value)
#define Rte_write_PP_OutHighBeamAllowed_OutHighBeamAllowed(value)		Rte_write_data(OutHighBeamAllowed, value)
#define Rte_write_PP_OutLowBeamAllowed_OutLowBeamAllowed(value)			Rte_write_data(OutLowBeamAllowed, value)
#define Rte_write_PP_OutWiperAllowed_OutWiperAllowed(value)				Rte_write_data(OutWiperAllowed, value)
#endif /* INC_FVR_RTE_H_ */
