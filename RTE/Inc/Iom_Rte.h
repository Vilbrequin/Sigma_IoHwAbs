/*
 * Iom_Rte.h
 *
 *  Created on: Jan 15, 2026
 *      Author: Lenovo X13
 */

#ifndef INC_IOM_RTE_H_
#define INC_IOM_RTE_H_

#include "rte.h"

#define Rte_write_PP_HighBeamBtn_Debounced(value)						Rte_write_data(HighBeamBtnDebounced, value)
#define Rte_write_PP_HighBeamBtn_PressCounter(value)					Rte_write_data(HighBeamBtnPressCounter, value)

#define Rte_write_PP_LowBeamBtn_Debounced(value)						Rte_write_data(LowBeamBtnDebounced, value)
#define Rte_write_PP_LowBeamBtn_PressCounter(value)						Rte_write_data(LowBeamBtnPressCounter, value)

#define Rte_write_PP_WasherBtn_Debounced(value)							Rte_write_data(WasherBtnDebounced, value)
#define Rte_write_PP_WasherBtn_PressCounter(value)						Rte_write_data(WasherBtnPressCounter, value)

#define Rte_read_RP_WasherState_WasherState(pValue)						Rte_read_data(WasherState, pValue)

#define Rte_read_RP_InHighBeamAllowed_InHighBeamAllowed(pValue)			Rte_read_data(InHighBeamAllowed, pValue)
#define Rte_read_RP_InLowBeamAllowed_InLowBeamAllowed(pValue)			Rte_read_data(InLowBeamAllowed, pValue)
#define Rte_read_RP_InWasherAllowed_InWasherAllowed(pValue)				Rte_read_data(InWasherAllowed, pValue)
#define Rte_read_RP_OutWasherAllowed_OutWasherAllowed(pValue)			Rte_read_data(OutWasherAllowed, pValue)



#endif /* INC_IOM_RTE_H_ */
