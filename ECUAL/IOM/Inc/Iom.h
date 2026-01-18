/*
 * Iom.h
 *
 *  Created on: May 31, 2025
 *      Author: HSM
 */

#ifndef INC_IOM_H_
#define INC_IOM_H_

#include "Dio.h"

#define IOM_MAX_COUNTER_VALUE 	UINT8_MAX

typedef unsigned char boolean;

#define FALSE	(boolean)0u
#define TRUE	(boolean)1u

typedef uint8_t Iom_LevelType;

#define IOM_LOW		(Iom_LevelType)0u
#define IOM_HIGH	(Iom_LevelType)1u

typedef uint8_t Iom_ChannelId; /* Iom channel logical Name a.k.a Id */

typedef uint8_t Iom_DebouceType;

typedef struct {
	Dio_ChannelType 	DioChannelId;
	boolean 			InvertionFlag;
	Iom_DebouceType 	DebounceTicks; /*in ticks*/
}Iom_InputConfigType;

typedef struct {
	Iom_LevelType 	debounced; /* debounced logical value that can be returned by Iom_ReadChannel at any time !*/
	Iom_LevelType 	prev_debounced; /* raw captured value read by Dio_ReadChannel API */
	uint16_t 		cnt; 		/* Countes how many PrevRawLevel */
	uint16_t 		press_cnt; /* Countes how many click events */
}Iom_ChannelStateType;

typedef uint8_t Iom_OutActiveLevel;

#define IOM_ACTIVE_LOW		(Iom_OutActiveLevel)0u /* Low Side Switching*/
#define IOM_ACTIVE_HIGH		(Iom_OutActiveLevel)1u /* High Side Switching*/

typedef uint8_t Iom_OutLevel;

#define IOM_OUT_OFF			(Iom_OutLevel)0u
#define IOM_OUT_ON			(Iom_OutLevel)1u

typedef struct{
	Dio_ChannelType 	DioChannelId;
	Iom_OutActiveLevel	ActiveLevel;
	Iom_OutLevel		Level;
}Iom_OutputConfigType;

typedef struct {
	const Iom_InputConfigType* 	InputConfig;
	const Iom_OutputConfigType* OutputConfig;
	uint8_t						NumInputs;
	uint8_t						NumOutputs;
}Iom_ConfigType;


/********************************* IOM Public API *********************************/
void Iom_Init(const Iom_ConfigType* CfgPtr);
//Iom_LevelType Iom_ReadChannel(Iom_ChannelId ChannelId);
void Iom_WriteChannel(Iom_ChannelId ChannelId, Iom_OutLevel Level);
void Iom_InTask_5ms(void); // n is the task periodicity in ms !
void Iom_OutTask_5ms(void);


#endif /* INC_IOM_H_ */
