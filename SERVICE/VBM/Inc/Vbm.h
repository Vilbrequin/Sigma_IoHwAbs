/*
 * VBM.h
 *
 *  Created on: Nov 1, 2025
 *      Author: Lenovo X13
 */

#ifndef INC_VBM_H_
#define INC_VBM_H_


#include <stdint.h>
/* vbm_vbatt_type : type used for voltage value in mV of power supply rails (input / output PwS) */
typedef uint16_t		vbm_vbatt_type;

/* VBM Battery inputs */
typedef enum {
	VBM_IN_PSW = 0,
	VBM_OUT_PWS,
	VBM_BATT_PWS_NUM
}Vbm_batt_pws;

/* VBM thresholds  */
typedef uint16_t 		vbm_thr_type;

#define VBM_VOLTAGE_THR_5_60		(5600U)
#define VBM_VOLTAGE_THR_8_00		(8000U)
#define VBM_VOLTAGE_THR_16_00		(16000U)
#define VBM_VOLTAGE_THR_19_00		(19000U)

/* VBM ranges */
typedef uint8_t 		vbm_range_type;


#define VBM_UNDER_VOLTAGE			(0x01U)
#define VBM_NORMAL_VOLTAGE			(0x02U)
#define VBM_OVER_VOLTAGE			(0x03U)
#define VBM_EXTRA_OVER_VOLTAGE		(0x04U)


/* VBM Hysteresis */
typedef uint8_t			vbm_hyst_type;

#define VBM_HYST_LOW_MV				(200U) // 200mV under the lower threshold
#define VBM_HYST_HIGH_MV			(200U) // 200mV above the upper threshold



/*****************************************************************************************************/
/*                                  	API Prototypes    											 */
/*****************************************************************************************************/

void vbm_ranges_init(void);
vbm_range_type vbm_get_range(vbm_vbatt_type inVal, Vbm_batt_pws VbattInPwS);








#endif /* INC_VBM_H_ */
