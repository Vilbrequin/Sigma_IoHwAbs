/*
 * Wipper_Washing_rte.h
 *
 *  Created on: Jan 30, 2026
 *      Author: Lenovo X13
 */

#ifndef INC_WIPPER_WASHING_RTE_H_
#define INC_WIPPER_WASHING_RTE_H_

#include "rte.h"

#define Rte_read_RP_WasherBtn_PressCounter(pValue)						Rte_read_data(WasherBtnPressCounter, pValue)
#define Rte_read_RP_WasherBtn_WasherBtnDebounced(pValue)				Rte_read_data(WasherBtnDebounced, pValue)
#define Rte_write_PP_WasherBtn_PressCounter(value)						Rte_write_data(WasherBtnPressCounter, value)

#define Rte_read_RP_WipperLevel_WipperLevel(pValue)						Rte_read_data(WipperLevel, pValue)
#define Rte_read_RP_VehicleMode_VehicleMode(pValue)						Rte_read_data(VehicleMode, pValue)
#define Rte_read_RP_WipperPos_WipperPos(pValue)						Rte_read_data(WipperPos, pValue)

#define Rte_write_PP_WasherState_WasherState(value)						Rte_write_data(WasherState, value)
#define Rte_write_PP_WipperDc_WipperDc(value)							Rte_write_data(WipperDc, value)

#define Rte_write_RP_VehicleMode_VehicleMode(pValue)					Rte_read_data(VehicleMode, pValue)

#endif /* INC_WIPPER_WASHING_RTE_H_ */
