/*
 * Health_Monitoring_SWC_rte.h
 *
 *  Created on: Jan 31, 2026
 *      Author: Lenovo X13
 */

#ifndef INC_HEALTH_MONITORING_SWC_RTE_H_
#define INC_HEALTH_MONITORING_SWC_RTE_H_

#include "rte.h"

#define Rte_write_PP_VehicleMode_VehicleMode(value)				Rte_write_data(VehicleMode, value)

#define Rte_read_RP_EnginTemp_EnginTemp(pValue)					Rte_read_data(EnginTemp, pValue)
#define Rte_read_RP_OilPress_OilPress(pValue)					Rte_read_data(OilPress, pValue)
#define Rte_read_RP_BattVoltage_BattVoltage(pValue)				Rte_read_data(BattVoltage, pValue)

#endif /* INC_HEALTH_MONITORING_SWC_RTE_H_ */
