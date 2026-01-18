/*
 * Vbm_Rte.h
 *
 *  Created on: Jan 16, 2026
 *      Author: Lenovo X13
 */

#ifndef INC_VBM_RTE_H_
#define INC_VBM_RTE_H_

#include "rte.h"

#define Rte_write_PP_InVoltageRange_InVoltageRange(value)		Rte_write_data(InVoltageRang, value)
#define Rte_write_PP_OutVoltageRange_OutVoltageRange(value)		Rte_write_data(OutVoltageRang, value)

#define Rte_read_RP_InPwS_InPwS(pValue)							Rte_read_data(InPwS, pValue)
#define Rte_read_RP_OutPwS_OutPwS(pValue)						Rte_read_data(OutPwS, pValue)

#endif /* INC_VBM_RTE_H_ */
