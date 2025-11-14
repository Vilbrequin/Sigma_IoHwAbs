/*
 * Adm.h
 *
 *  Created on: Nov 1, 2025
 *      Author: Lenovo X13
 */

#ifndef INC_ADM_H_
#define INC_ADM_H_

#include "Adc.h"
#include "Adc_Cfg.h"


/***************************************************************************************************************************************/
/*														 POWER SUPPLY GRP															   */
/***************************************************************************************************************************************/

#define ADM_PWS_DIRECTION_IN					0U
#define ADM_PWS_DIRECTION_OUT					1U


/***************************************************************************************************************************************/
/*														 		SENSORS GRP															   */
/***************************************************************************************************************************************/
#define ADM_TEMPERATURE_SENSOR_CHANNEL			0U
#define ADM_LUMINOSITY_SENSOR_CHANNEL			1U

/***************************************************************************************************************************************/
/*														 	API PROTOTYPE															   */
/***************************************************************************************************************************************/
/* the Adc_Read API returns a on buffer of n*m length but to get the samples of a specific channel in a group we use this API */
void Adm_getChannelSamples(uint16_t* buff, uint8_t nSamples, uint8_t nChannles, uint8_t rank, uint16_t* chBuff);

uint16_t Adm_ReadAverage(uint16_t* buff, uint8_t nSamples);

uint16_t Adm_get_in_out_power_supply_mV(uint8_t direction);

uint16_t Adm_ReadSensorGrp(uint8_t activeChannel);

void Adm_Init(void);

void Adm_Deinit(void);

#endif /* INC_ADM_H_ */
