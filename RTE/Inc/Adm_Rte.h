/*
 * Adm_Rte.h
 *
 *  Created on: Jan 15, 2026
 *      Author: Lenovo X13
 */

#ifndef INC_ADM_RTE_H_
#define INC_ADM_RTE_H_

#include "rte.h"

#define Rte_write_PP_WipperLevel_WipperLevel(value)						Rte_write_data(WipperLevel, value)
#define Rte_write_PP_EnginTemp_EnginTemp(value)							Rte_write_data(EnginTemp, value)
#define Rte_write_PP_OilPress_OilPress(value)							Rte_write_data(OilPress, value)
#define Rte_write_PP_BattVoltage_BattVoltage(value)						Rte_write_data(BattVoltage, value)
#define Rte_write_PP_WipperPos_WipperPos(value)							Rte_write_data(WipperPos, value)

#define Rte_write_PP_InPwS_InPwS(value)									Rte_write_data(InPwS, value)
#define Rte_write_PP_OutPwS_OutPwS(value)								Rte_write_data(OutPwS, value)

#define Rte_read_RP_InEnginTempAllowed_InEnginTempAllowed(pValue)		Rte_read_data(InEnginTempAllowed, pValue)
#define Rte_read_RP_InOilPressAllowed_InOilPressAllowed(pValue)			Rte_read_data(InOilPressAllowed, pValue)
#define Rte_read_RP_InBattVoltAllowed_InBattVoltAllowed(pValue)			Rte_read_data(InBattVoltAllowed, pValue)
#define Rte_read_RP_InWiperLvlAllowed_InWiperLvlAllowed(pValue)			Rte_read_data(InWiperLvlAllowed, pValue)
#define Rte_read_RP_InWiperPosAllowed_InWiperPosAllowed(pValue)			Rte_read_data(InWiperPosAllowed, pValue)

#endif /* INC_ADM_RTE_H_ */
