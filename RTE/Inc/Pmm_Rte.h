/*
 * Pmm_Rte.h
 *
 *  Created on: Jan 16, 2026
 *      Author: Lenovo X13
 */

#ifndef INC_PMM_RTE_H_
#define INC_PMM_RTE_H_

#include "rte.h"

#define Rte_read_RP_HighBeamDc_HighBeamDc(pValue)						Rte_read_data(HighBeamDc, pValue)
#define Rte_read_RP_LowBeamDc_LowBeamDc(pValue)							Rte_read_data(LowBeamDc, pValue)
#define Rte_read_RP_WipperDc_WipperDc(pValue)							Rte_read_data(WipperDc, pValue)

#define Rte_read_RP_OutHighBeamAllowed_OutHighBeamAllowed(pValue)		Rte_read_data(OutHighBeamAllowed, pValue)
#define Rte_read_RP_OutLowBeamAllowed_OutLowBeamAllowed(pValue)			Rte_read_data(OutLowBeamAllowed, pValue)
#define Rte_read_RP_OutWiperAllowed_OutWiperAllowed(pValue)				Rte_read_data(OutWiperAllowed, pValue)
#endif /* INC_PMM_RTE_H_ */
