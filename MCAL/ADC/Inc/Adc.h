/*
 * Adc.h
 *
 *  Created on: Jul 26, 2025
 *      Author: HSM
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

/*********************************************************************************************************************/
/*													Includes														 */
/*********************************************************************************************************************/

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_adc.h"
/*********************************************************************************************************************/
/*												Type definitions													 */
/*********************************************************************************************************************/
typedef unsigned char 				boolean;
#define FALSE						(boolean)0x00
#define TRUE						(boolean)0x01

typedef unsigned char				Std_ReturnType;
#define E_NOT_OK					(Std_ReturnType)0x00
#define E_OK						(Std_ReturnType)0x01

typedef uint8_t						ADC_InstanceType;
#define ADC_1						(ADC_InstanceType)0x00 /*ADC1*/
#define ADC_2						(ADC_InstanceType)0x01 /*ADC2*/
#define ADC_3						(ADC_InstanceType)0x02 /*ADC3*/

typedef uint8_t 					Adc_ChannelType; // Numeric ID of an ADC channel.
#define ADC_CH0						(Adc_ChannelType)0x00
#define ADC_CH1						(Adc_ChannelType)0x01
#define ADC_CH2						(Adc_ChannelType)0x02
#define ADC_CH3						(Adc_ChannelType)0x03
#define ADC_CH4						(Adc_ChannelType)0x04
#define ADC_CH5						(Adc_ChannelType)0x05
#define ADC_CH6						(Adc_ChannelType)0x06
#define ADC_CH7						(Adc_ChannelType)0x07
#define ADC_CH8						(Adc_ChannelType)0x08
#define ADC_CH9						(Adc_ChannelType)0x09
#define ADC_CH10					(Adc_ChannelType)0x0A
#define ADC_CH11					(Adc_ChannelType)0x0B
#define ADC_CH12					(Adc_ChannelType)0x0C
#define ADC_CH13					(Adc_ChannelType)0x0D
#define ADC_CH14					(Adc_ChannelType)0x0E
#define ADC_CH15					(Adc_ChannelType)0x0F
#define ADC_NBR_OF_CHANNELS			(Adc_ChannelType)0x10

typedef uint8_t 					Adc_PrescaleType; // Type of clock prescaler factor.
#define ADC_PRESCALER_DIVIDED_BY_2	(Adc_PrescaleType)0x00 /* ADC_CLOCK_SYNC_PCLK_DIV2 */
#define ADC_PRESCALER_DIVIDED_BY_4	(Adc_PrescaleType)0x01 /* ADC_CLOCK_SYNC_PCLK_DIV4 */
#define ADC_PRESCALER_DIVIDED_BY_6	(Adc_PrescaleType)0x02 /* ADC_CLOCK_SYNC_PCLK_DIV6 */
#define ADC_PRESCALER_DIVIDED_BY_8	(Adc_PrescaleType)0x03 /* ADC_CLOCK_SYNC_PCLK_DIV8 */
#define ADC_PRESCALER_SIZE			(Adc_PrescaleType)0x04


typedef uint8_t  					Adc_SamplingTimeType; // Type of sampling time (the time during which the value is sampled)
#define ADC_SAMPLE_TIME_3_CYCLES	(Adc_SamplingTimeType)0x00 /*ADC_SAMPLETIME_3CYCLES*/
#define ADC_SAMPLE_TIME_15_CYCLES	(Adc_SamplingTimeType)0x01 /*ADC_SAMPLETIME_15CYCLES*/
#define ADC_SAMPLE_TIME_28_CYCLES	(Adc_SamplingTimeType)0x02 /*ADC_SAMPLETIME_28CYCLES*/
#define ADC_SAMPLE_TIME_56_CYCLES	(Adc_SamplingTimeType)0x03 /*ADC_SAMPLETIME_56CYCLES*/
#define ADC_SAMPLE_TIME_84_CYCLES	(Adc_SamplingTimeType)0x04 /*ADC_SAMPLETIME_84CYCLES*/
#define ADC_SAMPLE_TIME_112_CYCLES	(Adc_SamplingTimeType)0x05 /*ADC_SAMPLETIME_112CYCLES*/
#define ADC_SAMPLE_TIME_144_CYCLES	(Adc_SamplingTimeType)0x06 /*ADC_SAMPLETIME_144CYCLES*/
#define ADC_SAMPLE_TIME_480_CYCLES	(Adc_SamplingTimeType)0x07 /*ADC_SAMPLETIME_480CYCLES*/

typedef uint8_t 					Adc_ResolutionType; //  Type of channel resolution in number of bits.
#define ADC_RESOLUTION_12_BIT		(Adc_ResolutionType)0x00 /*ADC_RESOLUTION_12B*/
#define ADC_RESOLUTION_10_BIT		(Adc_ResolutionType)0x01 /*ADC_RESOLUTION_10B*/
#define ADC_RESOLUTION_8_BIT		(Adc_ResolutionType)0x02 /*ADC_RESOLUTION_8B*/
#define ADC_RESOLUTION_6_BIT		(Adc_ResolutionType)0x03 /*ADC_RESOLUTION_6B*/
#define ADC_RESOLUTION_SIZE			(Adc_ResolutionType)0x04

typedef uint8_t 					Adc_HwUnitState;
#define HW_UNIT_BUSY				(Adc_HwUnitState)0x00
#define HW_UNIT_IDLE				(Adc_HwUnitState)0x01

typedef uint8_t 	Adc_GroupType; // Numeric ID of an ADC channel group

typedef uint16_t 	Adc_ValueGroupType; // Type for reading the converted values of a channel group (raw, without any further scaling)


typedef uint8_t 	Adc_ConversionTimeType; /* Type of conversion time (the time during which the sampled analogue value is converted
											into digital representation) */

typedef uint8_t 	Adc_GroupPriorityType; //  Priority level of the channel. Lowest priority is 0.

typedef uint16_t 	Adc_StreamNumSampleType; // Type for configuring the number of group conversions in streaming access mode.

typedef uint16_t 	Adc_HwTriggerTimerType; // Type for the reload value of the ADC module embedded timer.

typedef enum {
	ADC_ALIGN_LEFT = 0,
	ADC_ALIGN_RIGHT,
	ADC_ALIGN_SIZE
}Adc_ResultAlignmentType; //  Type for alignment of ADC raw results in ADC result buffer

typedef enum {
	ADC_PRIORITY_NONE = 0u,
	ADC_PRIORITY_HW,
	ADC_PRIORITY_HW_SW
}Adc_PriorityImplementationType; //  Type for configuring the prioritization mechanism

typedef enum {
	 ADC_GROUP_REPL_ABORT_RESTART = 0,
	 ADC_GROUP_REPL_SUSPEND_RESUME
} Adc_GroupReplacementType;  /* Replacement mechanism, which is used on ADC group level, if a group conversion is interrupted by a group
								which has a higher priority.*/

typedef enum {
	ADC_STREAM_BUFFER_LINEAR = 0u,
	ADC_STREAM_BUFFER_CIRCULAR
}Adc_StreamBufferModeType; // Type for configuring the streaming access mode buffer type.

typedef enum {
	ADC_ACCESS_MODE_SINGLE = 0u,
	 ADC_ACCESS_MODE_STREAMING
}Adc_GroupAccessModeType; //  Type for configuring the access mode to group conversion results.

typedef enum {
	ADC_HW_TRIG_RISING_EDGE = 0u,
	ADC_HW_TRIG_FALLING_EDGE,
	ADC_HW_TRIG_BOTH_EDGES
}Adc_HwTriggerSignalType; //  Type for configuring on which edge of the hardware trigger signal the driver should react.

typedef enum {
	 ADC_IDLE = 0u,
	 ADC_BUSY,
	 ADC_COMPLETED,
	 ADC_STREAM_COMPLETED,
	 ADC_INVALIDE_STATUS = 0xFF
}Adc_StatusType; //  Current status of the conversion of the requested ADC Channel group.

typedef enum {
	ADC_TRIGG_SRC_SW = 0u,
	ADC_TRIGG_SRC_HW
}Adc_TriggerSourceType; // Type for configuring the trigger source for an ADC Channel group.

typedef enum {
	 ADC_CONV_MODE_ONESHOT = 0u,
	 ADC_CONV_MODE_CONTINUOUS
}Adc_GroupConvModeType; // Type for configuring the conversion mode of an ADC Channel group

// Prescaler is common to all ADC instances !
typedef struct {
	Adc_PrescaleType 			AdcPrescaler;
}Adc_CommonCfgType;

typedef struct {
	ADC_InstanceType			AdcInstance; /* ADCx */
	Adc_ResolutionType			AdcResolution;
	Adc_ResultAlignmentType		AdcAlignment;
}Adc_InstanceCfgType;

typedef struct {
    Adc_ChannelType      		ChannelId;  /* ADC_CHx		           */
    Adc_SamplingTimeType 		SampleTime; /* 3 – 480 cycles            */
    uint8_t                		Rank;       /* 1…16 order in sequencer   */
}Adc_ChannelCfgType;

typedef struct {
	uint8_t						InstanceId; // this member is used to map each group to it's ADCx unit so from the group index we can know the unit that we belong to
	Adc_GroupType				GroupId; // this Id must be the index of the group in AdcGroupCfg array so when an an API has a group id as input we can access it directly by its index
	const Adc_ChannelCfgType* 	ChannelList;
	uint8_t						NumChannels;
	Adc_GroupConvModeType		ConversionMode; /* One-Shot / Continuous */
	Adc_TriggerSourceType 		TriggSrc; /* SW / HW */
	Adc_GroupAccessModeType 	AccessMode; /*Single / Streaming */
	Adc_StreamNumSampleType		NumSample; /* in streaming access mode how much history we want to store ? */
	Adc_StreamBufferModeType 	BufferMode; /* Linear / Circular */
}Adc_GroupCfgType;

typedef struct {
	const Adc_CommonCfgType 	AdcCommon; /* Prescaler */
	const Adc_InstanceCfgType*	AdcInstanceCfg;
	const Adc_GroupCfgType*		AdcGroupCfg;
	uint8_t						NumInstances;
	uint8_t						NumGroups;
}Adc_ConfigType;

/*********************************************************************************************************************/
/*											    Runtime Structures													 */
/*********************************************************************************************************************/

// Group level runtime struct

typedef struct {
	const Adc_GroupCfgType*				grpCfg;
	volatile Adc_StatusType				grpState; // changed in ISR/DMA
	Adc_ValueGroupType*					grpBuff;
	volatile uint16_t					grpLastValidIdx; /* last written index (streaming) */
	boolean 							isStarted : 1; // flag that is set when a group is started via the Adc_StartGroupConversion	API
	volatile boolean					firstRoundReady : 1; // flags that is set when the first EOS done and get cleared only when a group is stopped and rested !
	volatile Adc_StreamNumSampleType	validSalmples;
}Adc_GroupStateType;

// Adc level runtime struct

typedef struct {
	const Adc_InstanceCfgType*	unitCfg;
	void* 						unitHandle; /* void* resolved at runtime to be ADC_HandleTypeDef */
	void* 						unitDMAHandle;
	Adc_GroupStateType*			unitActiveGroup;
	Adc_HwUnitState				unitState;
}Adc_UnitStateType;

// Module level runtime struct

typedef struct {
	const Adc_ConfigType*		moduleCfg;
	Adc_UnitStateType*			moduleUnits;
	Adc_GroupStateType*			moduleGroups;
}Adc_ModuleStateType;
/*********************************************************************************************************************/
/*													Public APIs														 */
/*********************************************************************************************************************/
void Adc_Init(const Adc_ConfigType* ConfigPtr);
Std_ReturnType Adc_SetupResultBuffer (Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr);
void Adc_DeInit (void);
void Adc_StartGroupConversion (Adc_GroupType Group);
void Adc_StopGroupConversion (Adc_GroupType Group);
Std_ReturnType Adc_ReadGroup (Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr);
Adc_StatusType Adc_GetGroupStatus (Adc_GroupType Group);
Adc_StreamNumSampleType Adc_GetStreamLastPointer (Adc_GroupType Group, Adc_ValueGroupType** PtrToSamplePtr);


#endif /* INC_ADC_H_ */
