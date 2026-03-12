/*
 * High_low_beam_swc_rte.h
 *
 *  Created on: Jan 31, 2026
 *      Author: Lenovo X13
 */

#ifndef INC_HIGH_LOW_BEAM_SWC_RTE_H_
#define INC_HIGH_LOW_BEAM_SWC_RTE_H_

#include "rte.h"

#define Rte_read_RP_HighBeamBtn_PressCounter(pValue)					Rte_read_data(HighBeamBtnPressCounter, pValue)
#define Rte_read_RP_LowBeamBtn_PressCounter(pValue)						Rte_read_data(LowBeamBtnPressCounter, pValue)

#define Rte_write_PP_HighBeamDc_HighBeamDc(value)						Rte_write_data(HighBeamDc, value)
#define Rte_write_PP_LowBeamDc_LowBeamDc(value)							Rte_write_data(LowBeamDc, value)
#endif /* INC_HIGH_LOW_BEAM_SWC_RTE_H_ */
