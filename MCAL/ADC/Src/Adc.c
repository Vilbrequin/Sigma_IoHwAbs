/*
 * Adc.c
 *
 *  Created on: Jul 26, 2025
 *      Author: HSM
 */

/*********************************************************************************************************************/
/*													Includes														 */
/*********************************************************************************************************************/

#include "Adc.h"
#include "irq_handle.h"

/*********************************************************************************************************************/
/*													Macros															 */
/*********************************************************************************************************************/

#define NUMBER_OF_ADC_IDS		0x03

#define MAX_NUMBER_OF_GROUPS	0x10
/*********************************************************************************************************************/
/*													Sahred Data														 */
/*********************************************************************************************************************/
static ADC_TypeDef*			ADC_MapSymbolicName[NUMBER_OF_ADC_IDS] = {ADC1, ADC2, ADC3};

static uint32_t				ADC_MapStmPrescaler[ADC_PRESCALER_SIZE] = {ADC_CLOCK_SYNC_PCLK_DIV2,
																	ADC_CLOCK_SYNC_PCLK_DIV4,
																	ADC_CLOCK_SYNC_PCLK_DIV6,
																	ADC_CLOCK_SYNC_PCLK_DIV8};

static uint32_t				ADC_MapStmResolution[ADC_RESOLUTION_SIZE] = {ADC_RESOLUTION_12B,
																	ADC_RESOLUTION_10B,
																	ADC_RESOLUTION_8B,
																	ADC_RESOLUTION_6B};


static uint32_t				ADC_MapStmAlign[ADC_ALIGN_SIZE] = {ADC_DATAALIGN_LEFT, ADC_DATAALIGN_RIGHT};

static DMA_Stream_TypeDef* 	ADC_MapDMAStream[NUMBER_OF_ADC_IDS] = {DMA2_Stream0, DMA2_Stream3, DMA2_Stream1};

static uint32_t				ADC_MapDMAChannels[NUMBER_OF_ADC_IDS] = {DMA_CHANNEL_0, DMA_CHANNEL_1, DMA_CHANNEL_2};

static Adc_UnitStateType	mHwUnits[NUMBER_OF_ADC_IDS];

static Adc_UnitStateType*	hwToUnits[NUMBER_OF_ADC_IDS];

static Adc_GroupStateType	mGrpState[MAX_NUMBER_OF_GROUPS];

static ADC_HandleTypeDef 	hadc_arr[NUMBER_OF_ADC_IDS];

static DMA_HandleTypeDef	hdma_arr[NUMBER_OF_ADC_IDS];

static Adc_ModuleStateType 	Adc_module;


static boolean 				ADC_Initialized  = FALSE;

/*********************************************************************************************************************/
/*												Private APIs Prototype												 */
/*********************************************************************************************************************/
static inline void Adc_TimerEnableClock(ADC_InstanceType InstanceId);
static void Adc_DMAConfig(Adc_GroupType Group);
static void adc_dma_ht_handler(Adc_GroupStateType* grp);
static void adc_dma_tc_handler(Adc_GroupStateType* grp);
static void adc_dma_irq_mux(ADC_InstanceType Adc_id);
static void enable_all_irqs();
static void disable_all_irqs();
/*********************************************************************************************************************/
/*													Public APIs														 */
/*********************************************************************************************************************/

/*
 * The Adc_Init() API just set default values of the ADC HW unit.
 * This API copy each group configuration to a runtime array and not map them directly to HW
 * Real per-group values are written inside Adc_StartGroupConversion() when the driver knows which group is next.
 * */
void Adc_Init(const Adc_ConfigType* ConfigPtr){
	if(ConfigPtr == NULL){
		return; // No DET yet !
	}

	Adc_module.moduleCfg = ConfigPtr;
	Adc_module.moduleUnits = mHwUnits;
	Adc_module.moduleGroups = mGrpState;

	for(uint8_t i = 0; i < ConfigPtr->NumInstances; ++i){
		// Enable the RCC Clock for the ADC HW Unit
		const Adc_InstanceCfgType* hwUnit = &ConfigPtr->AdcInstanceCfg[i];
		Adc_TimerEnableClock(hwUnit->AdcInstance);

		ADC_HandleTypeDef* hadc = &hadc_arr[i];
		DMA_HandleTypeDef* hdma = &hdma_arr[i];

		hadc->Instance = ADC_MapSymbolicName[hwUnit->AdcInstance];
		hadc->Init.ClockPrescaler = ADC_MapStmPrescaler[ConfigPtr->AdcCommon.AdcPrescaler];
		hadc->Init.Resolution = ADC_MapStmResolution[hwUnit->AdcResolution];
		hadc->Init.DataAlign = ADC_MapStmAlign[hwUnit->AdcAlignment];
		hadc->Init.ScanConvMode = ENABLE; // enables multi channel, Conversions are performed in sequence mode
		hadc->Init.ContinuousConvMode = DISABLE;
		hadc->Init.DiscontinuousConvMode = DISABLE;
		hadc->Init.EOCSelection = ADC_EOC_SEQ_CONV;


		Adc_module.moduleUnits[i].unitCfg = hwUnit;
		Adc_module.moduleUnits[i].unitHandle = hadc;
		Adc_module.moduleUnits[i].unitDMAHandle = hdma;
		Adc_module.moduleUnits[i].unitActiveGroup = NULL;
		Adc_module.moduleUnits[i].unitState = HW_UNIT_IDLE;

		/* Map Hardware Unit ADCx to Units at Runtime
		 * in the Shared IRQ Handler after testing which ADC it's the trigger of the interruption
		 * we need to access it's runtime members in O(1)
		 */
		if(ADC_1 == hwUnit->AdcInstance){
			hwToUnits[ADC_1] = &Adc_module.moduleUnits[i];
		}
		else if (ADC_2 == hwUnit->AdcInstance){
			hwToUnits[ADC_2] = &Adc_module.moduleUnits[i];
		}
		else if(ADC_3 == hwUnit->AdcInstance){
			hwToUnits[ADC_3] = &Adc_module.moduleUnits[i];
		}
		else{
			// Do Nothing !
		}


	}

	for(uint8_t j = 0; j < ConfigPtr->NumGroups; ++j){
		Adc_module.moduleGroups[j].grpCfg = &ConfigPtr->AdcGroupCfg[j];
		Adc_module.moduleGroups[j].grpState = ADC_IDLE;
		Adc_module.moduleGroups[j].grpBuff = NULL;
		Adc_module.moduleGroups[j].grpLastValidIdx = 0;
		Adc_module.moduleGroups[j].isStarted = 0;
		Adc_module.moduleGroups[j].firstRoundReady = 0;
		Adc_module.moduleGroups[j].validSalmples = 0;


	}

	/* Enable DMA2 RCC Clock */
	__HAL_RCC_DMA2_CLK_ENABLE();

	/* Set priorities */
	nvic_set_priority(DMA2_Stream0_IRQn,          0);  // ADC shared IRQ
	nvic_set_priority(DMA2_Stream1_IRQn,          1);  // ADC shared IRQ
	nvic_set_priority(DMA2_Stream3_IRQn,          2);  // ADC shared IRQ

	/*  Enable lines */
	enable_all_irqs();


	ADC_Initialized = TRUE;
}


Std_ReturnType Adc_SetupResultBuffer (Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr){

	if (DataBufferPtr == NULL) {

		return E_NOT_OK;
	}

	if (Group >= Adc_module.moduleCfg->NumGroups){
		return E_NOT_OK;
	}

	Adc_GroupStateType* grpState = &Adc_module.moduleGroups[Group];


	if(grpState->grpState == ADC_IDLE){

		grpState->grpBuff = DataBufferPtr;
		grpState->grpLastValidIdx = 0;
		grpState->isStarted = 0;
		grpState->firstRoundReady = 0;

		return E_OK;

	}
	else {
		// report a runtime error ADC_E_BUSY. but not DEM or DET is present
		return E_NOT_OK;
	}


}

void Adc_StartGroupConversion (Adc_GroupType Group){

	if (Group >= Adc_module.moduleCfg->NumGroups){
			return; // No DET Yet !
	}
	ADC_ChannelConfTypeDef sConfig = {0};

	Adc_GroupStateType* grpState = &Adc_module.moduleGroups[Group];

	if (NULL == grpState){
		return;
	}
	const Adc_GroupCfgType*	grp = grpState->grpCfg;

	if (NULL == grp){
		return;
	}
	Adc_UnitStateType* unitState = &Adc_module.moduleUnits[grp->InstanceId];

	if (NULL == unitState){
		return;
	}
	ADC_HandleTypeDef* hadc = unitState->unitHandle;
	if (NULL == hadc){
		return;
	}

	// check  if all groups in the actual group's HW Unit are IDLE
	if (HW_UNIT_BUSY == unitState->unitState) {
		return; // No Queuing mechanism yet !
	}

	/* in single one-shot configuration ADC should stop immediately after the scan */
	boolean iscontinuous = (ADC_CONV_MODE_CONTINUOUS == grp->ConversionMode);
	boolean isSwTrigger = (ADC_TRIGG_SRC_SW == grp->TriggSrc);
	/* TODO
	 *  in case of the 'Streaming access mode + Linear Buffer" configuration we follow this steps to setup the ADC to implicitly stop conversion once
	 * the buffer is full :
	 * continuous conversion mode set to DISABLE
	 * number of channels is the actual number of channels multiply by the number of samples
	 * the trick is instead of n*m different channel we loop m times the same n channel so the config looks like a single one-shot conversion of n*m channel
	 * */

	hadc->Init.ScanConvMode = grp->NumChannels > 1 ? ENABLE : DISABLE;
	hadc->Init.ContinuousConvMode = iscontinuous ? ENABLE : DISABLE;
	hadc->Init.DMAContinuousRequests = ENABLE; // !!!!
	hadc->Init.ExternalTrigConv = isSwTrigger ? ADC_SOFTWARE_START : ADC_EXTERNALTRIGCONV_T1_CC1; // in case of a HW trigger we must set the right one, but as a v1.0.0 we stub it to a default value1
	hadc->Init.NbrOfConversion =  grp->NumChannels;
	hadc->Init.EOCSelection = ADC_EOC_SEQ_CONV;
	HAL_ADC_Init(hadc);
	//__HAL_ADC_ENABLE_IT(hadc, ADC_IT_EOC);


	for(uint8_t i = 0; i < grp->NumChannels; i++){
		  sConfig.Channel = grp->ChannelList[i].ChannelId;
		  sConfig.Rank = grp->ChannelList[i].Rank;
		  sConfig.SamplingTime = grp->ChannelList[i].SampleTime;

		  if (HAL_ADC_ConfigChannel(hadc, &sConfig) != HAL_OK)
		 {
			return;
		 }

	}



	Adc_DMAConfig(Group);

	/* In case of a group with single access mode and continuous conversion mode at every time (unless an explicit stop occurs) the state is always Busy
	 * in this case if we want to read the last coherent scan while busy we gone get incoherent results, so to get rid of this we double the size of the buffer,
	 * instead of n sample (where n is the number of channels), so at any time one slot of size n has the latest coherent scan*/
	boolean isSingleAndContinuous = (ADC_ACCESS_MODE_SINGLE == grp->AccessMode) && (ADC_CONV_MODE_CONTINUOUS == grp->ConversionMode);

	uint32_t buff_size = grp->AccessMode == ADC_ACCESS_MODE_STREAMING ? grp->NumChannels * grp->NumSample : (isSingleAndContinuous ? grp->NumChannels * 2 : grp->NumChannels);

	grpState->isStarted = 1;

	unitState->unitActiveGroup = grpState;

	HAL_ADC_Start_DMA(hadc, (uint32_t *)grpState->grpBuff, buff_size);
}


Std_ReturnType Adc_ReadGroup (Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr){

	if(NULL == DataBufferPtr){
		return E_NOT_OK;
	}
	if (Group > Adc_module.moduleCfg->NumGroups){
				return E_NOT_OK; // No DET Yet !
	}
	Adc_GroupStateType* 		grpState = &Adc_module.moduleGroups[Group];
	const Adc_GroupCfgType*		grpCfg = grpState->grpCfg;

	if(NULL == grpState->grpBuff){
		return E_NOT_OK; // No DET Yet !
	}

	if(NULL == grpCfg){
		return E_NOT_OK; // No DET Yet !
	}

	/******************************************************* Single access mode ***************************************************
	 * dest buffer <--- grp buffer
	 * No streaming mode is available in this access mode
	 * if Conv Mode = One-shot : take n sample, stop the ADC and wait to the next trigger
	 * if Conv Mode = Continuous : repeated scans overwrite the same n slots (latest values)
	 * then to have a coherent read we must wait until EOS (end of sequence) then copy the group's buffer into destination buffer
	 ******************************************************************************************************************************/

	/* Critical Section that get updated Via ISR so to read all the three members in atomic way we must disable IRQ then Read them then Enable it back*/
	disable_all_irqs();
	Adc_StatusType state = grpState->grpState;

	uint16_t start_idx = grpState->grpLastValidIdx;

	boolean isReady = grpState->firstRoundReady;
	enable_all_irqs();
	/**************************************************************************************************************************************************/
	boolean isContinuous = ( (ADC_ACCESS_MODE_SINGLE == grpCfg->AccessMode) && (ADC_CONV_MODE_CONTINUOUS == grpCfg->ConversionMode) )
						   ||
						   ( (ADC_ACCESS_MODE_STREAMING == grpCfg->AccessMode) && (ADC_STREAM_BUFFER_CIRCULAR == grpCfg->BufferMode) );

	boolean isAutoStop = ( (ADC_ACCESS_MODE_SINGLE == grpCfg->AccessMode) && (ADC_CONV_MODE_ONESHOT == grpCfg->ConversionMode) )
						 ||
						 ( (ADC_ACCESS_MODE_STREAMING == grpCfg->AccessMode) && (ADC_STREAM_BUFFER_LINEAR == grpCfg->BufferMode) );

	if(ADC_IDLE == state && 0 == grpState->isStarted){
		// Report ADC_E_IDLE Dev Error
		return E_NOT_OK; // No DET yet !
	}

	if(!isReady){
		return E_NOT_OK; // No DET yet !
	}
	// Coppy the last coherent round
	for(uint16_t i = 0; i < grpCfg->NumChannels; i++){
		DataBufferPtr[i] = grpState->grpBuff[i + start_idx];
	}

	// Perform state transition
	Adc_StatusType newState = ADC_IDLE;
	if(ADC_STREAM_COMPLETED == state){
		if(isContinuous){
			newState = ADC_BUSY;
		}
		else if(isAutoStop){
			newState = ADC_IDLE;
		}
		else {
			// Do Nothing
		}
	}
	else if(ADC_COMPLETED == state){
		newState = ADC_BUSY;
	}
	else {
		// Do Nothing
	}

	// Critical section 2 : write the state !!! Same Safety mechanism should be applied
	disable_all_irqs();
	grpState->grpState = newState;
	enable_all_irqs();
	return E_OK;
}

Adc_StatusType Adc_GetGroupStatus (Adc_GroupType Group) {

	if (Group >= Adc_module.moduleCfg->NumGroups){
		return ADC_INVALIDE_STATUS; // No DET Yet !
	}

	Adc_GroupStateType* 		grpState = &Adc_module.moduleGroups[Group];

	disable_all_irqs();

	Adc_StatusType state = grpState->grpState;

	enable_all_irqs();

	return state;
}

void Adc_StopGroupConversion (Adc_GroupType Group){

	if (Group >= Adc_module.moduleCfg->NumGroups){
		return; // No DET Yet !
	}
	Adc_GroupStateType* grpState = &Adc_module.moduleGroups[Group];

	if (NULL == grpState){
		return;
	}
	const Adc_GroupCfgType*	grp = grpState->grpCfg;

	if (NULL == grp){
		return;
	}
	Adc_UnitStateType* unitState = &Adc_module.moduleUnits[grp->InstanceId];

	if (NULL == unitState){
		return;
	}
	ADC_HandleTypeDef* hadc = unitState->unitHandle;
	if (NULL == hadc){
		return;
	}

	if (ADC_TRIGG_SRC_HW == grp->TriggSrc){
		return; // No DET Yet !
	}

	if(ADC_IDLE == grpState->grpState){
		return; // No DET Yet !
	}


	HAL_ADC_Stop_DMA(hadc);

	/*Critical Section */
	disable_all_irqs();
	grpState->grpState = ADC_IDLE;
	grpState->grpLastValidIdx = 0;
	grpState->firstRoundReady = FALSE;
	grpState->isStarted = FALSE;
	enable_all_irqs();
}


Adc_StreamNumSampleType Adc_GetStreamLastPointer (Adc_GroupType Group, Adc_ValueGroupType** PtrToSamplePtr){
	if (Group >= Adc_module.moduleCfg->NumGroups){
		return; // No DET Yet !
	}
	Adc_GroupStateType* grpState = &Adc_module.moduleGroups[Group];

	if (NULL == grpState){
		return;
	}
	const Adc_GroupCfgType*	grp = grpState->grpCfg;

	if (NULL == grp){
		return;
	}

	disable_all_irqs();

	Adc_StatusType state = grpState->grpState;

	uint16_t start_idx = grpState->grpLastValidIdx;

	boolean isReady = grpState->firstRoundReady;

	Adc_StreamNumSampleType numValidSmple = grpState->validSalmples;

	enable_all_irqs();

	Adc_StreamNumSampleType retrunValue = 0;

	if(ADC_IDLE == state && 0 == grpState->isStarted){
		// Report ADC_E_IDLE Dev Error
		return; // No DET yet !
	}

	if(!isReady){
		return; // No DET yet !
	}

	Adc_StatusType newState = ADC_IDLE;

	if( (ADC_BUSY == state) || (ADC_IDLE == state) ) {

		PtrToSamplePtr = NULL;
		retrunValue =  0; // In state ADC_BUSY or ADC_IDLE the value 0 is returned
	}
	else if ( (ADC_STREAM_COMPLETED == state) || (ADC_COMPLETED == state)){


		if(ADC_ACCESS_MODE_STREAMING == grp->AccessMode){

			*PtrToSamplePtr = &grpState->grpBuff[start_idx];

			if(ADC_STREAM_COMPLETED == state){

				if (ADC_STREAM_BUFFER_LINEAR == grp->BufferMode){
					newState = ADC_IDLE;
				}

				else if (ADC_STREAM_BUFFER_CIRCULAR == grp->BufferMode){
					newState = ADC_BUSY;
				}
				else {
					// Do Nothing !
				}
			}

			else if (ADC_COMPLETED == state){
				newState = ADC_BUSY;
			}
			else {
				// Do Nothing !
			}

			retrunValue = numValidSmple;
		}
		else if (ADC_ACCESS_MODE_SINGLE == grp->AccessMode){

			if(ADC_CONV_MODE_ONESHOT == grp->ConversionMode){

				PtrToSamplePtr = &grpState->grpBuff;
				if (ADC_COMPLETED == state){
					newState = ADC_BUSY;
				}
			}
			else if (ADC_CONV_MODE_CONTINUOUS == grp->ConversionMode) {
				*PtrToSamplePtr = &grpState->grpBuff[start_idx];
			}
			else {
				// Do Nothing
			}

			retrunValue =  1; //  The return value is 1 for groups with single access mode configuration !
		}
	}
	else {
		// Do Nothing !!1
	}

	disable_all_irqs();

	grpState->grpState = newState;

	enable_all_irqs();

	return retrunValue;
}
/*********************************************************************************************************************/
/*												Private APIs Definition												 */
/*********************************************************************************************************************/
static inline void Adc_TimerEnableClock(ADC_InstanceType InstanceId){
	switch(InstanceId){
		case ADC_1:
			__HAL_RCC_ADC1_CLK_ENABLE();
			break;
		case ADC_2:
			__HAL_RCC_ADC2_CLK_ENABLE();
			break;
		case ADC_3:
			__HAL_RCC_ADC3_CLK_ENABLE();
			break;
		default:
			// Do Nothing
			break;
	}
}


static void Adc_DMAConfig(Adc_GroupType Group){

	// Access mode ==> where and how every new result is written in RAM
	// Single = One storage slot per channel
	// Streaming = Keep history of "m" sample per channel

	// Conversion Mode ==> When ADC takes the next measurement round
	// One-shot = one scan after each trigger
	// Continuous = scan restart automatically after the 1st trigger


	const Adc_GroupCfgType* grp = &Adc_module.moduleCfg->AdcGroupCfg[Group];
	Adc_UnitStateType* unit  = &Adc_module.moduleUnits[grp->InstanceId];

	DMA_HandleTypeDef* hdma = unit->unitDMAHandle;
	ADC_HandleTypeDef* hadc = unit->unitHandle;

	boolean isContinuous = ( (ADC_ACCESS_MODE_SINGLE == grp->AccessMode) && (ADC_CONV_MODE_CONTINUOUS == grp->ConversionMode) )
						   ||
						   ( (ADC_ACCESS_MODE_STREAMING == grp->AccessMode) /*&& (ADC_STREAM_BUFFER_CIRCULAR == grp->BufferMode)*/ );

	boolean isSingleOneShot = ( (ADC_ACCESS_MODE_SINGLE == grp->AccessMode) && (ADC_CONV_MODE_ONESHOT == grp->ConversionMode) );

	//HAL_DMA_DeInit(hdma); // DMA stream must be fully disabled and reset before change DMA core parameters !
	__HAL_DMA_DISABLE(hdma);

	hdma->Instance = ADC_MapDMAStream[grp->InstanceId];
	hdma->Init.Channel = ADC_MapDMAChannels[grp->InstanceId];
	hdma->Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma->Init.PeriphInc = DMA_PINC_DISABLE;
	hdma->Init.MemInc = DMA_MINC_ENABLE;
	hdma->Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	hdma->Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	hdma->Init.Mode = isContinuous ? DMA_CIRCULAR : DMA_NORMAL;
	hdma->Init.Priority = DMA_PRIORITY_LOW;
	hdma->Init.FIFOMode = DMA_FIFOMODE_DISABLE;

    if (HAL_DMA_Init(hdma) != HAL_OK)
    {
    	return; // No DET Yet !
    }

    if (!isSingleOneShot){

    	__HAL_DMA_ENABLE_IT(hdma, DMA_IT_HT);   // Half-transfer interrupt
    }

    __HAL_DMA_ENABLE_IT(hdma, DMA_IT_TC);   // Transfer-complete interrupt

    __HAL_LINKDMA(hadc,DMA_Handle,*hdma);
}

/*********************************************************************************************************************/
/*												IRQ Handler (ISR)													 */
/*********************************************************************************************************************/

// ADC 1 DMA 2 Stream IRQ Handler
void DMA2_Stream0_IRQHandler(void){
	adc_dma_irq_mux(ADC_1);
}

// ADC 3 DMA 2 Stream IRQ Handler
void DMA2_Stream1_IRQHandler(void){
	adc_dma_irq_mux(ADC_3);
}

// ADC 2 DMA 2 Stream IRQ Handler
void DMA2_Stream3_IRQHandler(void){
	adc_dma_irq_mux(ADC_2);
}
/*********************************************************************************************************************/
/*												ISRs Helpers													 	 */
/*********************************************************************************************************************/

static void adc_dma_irq_mux(ADC_InstanceType Adc_id){
	Adc_UnitStateType* unit = hwToUnits[Adc_id];
	if (NULL == unit) {
		return;
	}

	Adc_GroupStateType* activgrp = unit->unitActiveGroup;
	if (NULL == activgrp) {
		return;
	}

	DMA_HandleTypeDef* hdma = unit->unitDMAHandle;
	if (NULL == hdma) {
		return;
	}

	uint32_t ht_flag = (Adc_id == ADC_1) ? DMA_FLAG_HTIF0_4 : (Adc_id == ADC_2) ? DMA_FLAG_HTIF3_7 :  DMA_FLAG_HTIF1_5;
	if(__HAL_DMA_GET_FLAG(hdma, ht_flag)){
		__HAL_DMA_CLEAR_FLAG(hdma, ht_flag);
		adc_dma_ht_handler(activgrp);
	}

	uint32_t tc_flag = (Adc_id == ADC_1) ? DMA_FLAG_TCIF0_4 : (Adc_id == ADC_2) ? DMA_FLAG_TCIF3_7 :  DMA_FLAG_TCIF1_5;
	if(__HAL_DMA_GET_FLAG(hdma, tc_flag)){
		__HAL_DMA_CLEAR_FLAG(hdma, tc_flag);
		adc_dma_tc_handler(activgrp);
	}

}
static void adc_dma_ht_handler(Adc_GroupStateType* grp){
	const Adc_GroupCfgType* grpCfg = grp->grpCfg;
	if (grpCfg == NULL) {
		return;
	}

	boolean isSingle = ((ADC_ACCESS_MODE_SINGLE == grpCfg->AccessMode) && (ADC_CONV_MODE_CONTINUOUS == grpCfg->ConversionMode));

	uint8_t nChannels =  grpCfg->NumChannels;
	Adc_StreamNumSampleType nSamples =  isSingle ? 2 : grpCfg->NumSample;
	uint16_t BufferSize = nChannels * nSamples;


	grp->firstRoundReady = 1;
	grp->grpLastValidIdx = ((BufferSize % 2) == 0) ? ((BufferSize/2) - 1) * nChannels : (((BufferSize - 1)/2) - 1) * nChannels;
	grp->grpState = ADC_COMPLETED;
	grp->validSalmples = ((BufferSize % 2) == 0) ? ((BufferSize/2) - 1) : (((BufferSize - 1)/2) - 1);
}

static void adc_dma_tc_handler(Adc_GroupStateType* grp){
	const Adc_GroupCfgType* grpCfg = grp->grpCfg;
	if (grpCfg == NULL) {
		return;
	}

	Adc_UnitStateType* unit  = &Adc_module.moduleUnits[grpCfg->InstanceId];
	if (NULL == unit) {
		return;
	}

	DMA_HandleTypeDef* hadc = unit->unitHandle;
	if (NULL == hadc) {
		return;
	}

	boolean isSingle = ((ADC_ACCESS_MODE_SINGLE == grpCfg->AccessMode) && (ADC_CONV_MODE_CONTINUOUS == grpCfg->ConversionMode));

	uint8_t nChannels =  grpCfg->NumChannels;
	Adc_StreamNumSampleType nSamples =  isSingle ? 2 : grpCfg->NumSample;
	uint16_t BufferSize = nChannels * nSamples;

	boolean isLinearStreaming = ( (ADC_ACCESS_MODE_STREAMING == grpCfg->AccessMode) && (ADC_STREAM_BUFFER_LINEAR == grpCfg->BufferMode) );

	if(TRUE == isLinearStreaming){
		HAL_ADC_Stop_DMA(hadc);
	}
	grp->grpLastValidIdx = BufferSize - nChannels;
	grp->grpState = isLinearStreaming ? ADC_STREAM_COMPLETED : ADC_COMPLETED;
	grp->validSalmples = nSamples - 1;
}


static void enable_all_irqs(void){
	nvic_enable_irq(DMA2_Stream0_IRQn);
	nvic_enable_irq(DMA2_Stream1_IRQn);
	nvic_enable_irq(DMA2_Stream3_IRQn);
}

static void disable_all_irqs(void){
	nvic_disable_irq(DMA2_Stream0_IRQn);
	nvic_disable_irq(DMA2_Stream1_IRQn);
	nvic_disable_irq(DMA2_Stream3_IRQn);
}
