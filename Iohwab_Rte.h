/*
 * Iohwab_Rte.h
 *
 *  Created on: Nov 8, 2025
 *      Author: Lenovo X13
 */

#ifndef INC_IOHWAB_RTE_H_
#define INC_IOHWAB_RTE_H_


#include "Fvr_Rte.h"

#define IOHWAB_Front_Right_Win_Button_Read(data)            Fvr_Front_Right_Window_Button(command)
#define IOHWAB_Front_Left_Win_Button_Read(data)             Fvr_Front_Left_Window_Button(command)
#define IOHWAB_Back_Right_Win_Button_Read(data)             Fvr_Back_Right_Window_Button(command)
#define IOHWAB_Back_Left_Win_Button_Read(data)              Fvr_Back_Left_Window_Button(command)

#define IOHWAB_Intrior_Lamp_Set()                          	Fvr_Intrior_Lamp_Set()
#define IOHWAB_Intrior_Lamp_Clear()                       	Fvr_Intrior_Lamp_Clear()

#define IOHWAB_Hvac_Fan_Start()                            	Fvr_Hvac_Fan_Start()
#define IOHWAB_Hvac_Fan_Stop()                             	Fvr_Hvac_Fan_Stop()

#define IOHWAB_Right_Turn_Indicator_Set()                  	Fvr_Right_Turn_Indicator_Set()
#define IOHWAB_Right_Turn_Indicator_Clear()                 Fvr_Right_Turn_Indicator_Clear()

#define IOHWAB_Left_Turn_Indicator_Set()                    Fvr_Left_Turn_Indicator_Set()
#define IOHWAB_Left_Turn_Indicator_Clear()                  Fvr_Left_Turn_Indicator_Clear()

#define IOHWAB_PWM_High_Beam_Start()						Fvr_PWM_High_Beam_Start()
#define IOHWAB_PWM_High_Beam_Stop()							Fvr_PWM_High_Beam_Stop()

#define IOHWAB_PWM_Low_Beam_Start()							Fvr_PWM_Low_Beam_Start()
#define IOHWAB_PWM_Low_Beam_Stop()							Fvr_PWM_Low_Beam_Stop()

#define IOHWAB_PWM_Right_TI_Start()                    		Fvr_PWM_Right_TI_Start()
#define IOHWAB_PWM_Right_TI_Stop()                  		Fvr_PWM_Right_TI_Stop()

#define IOHWAB_PWM_Left_TI_Start()                    		Fvr_PWM_Left_TI_Start()
#define IOHWAB_PWM_Left_TI_Stop()                  			Fvr_PWM_Left_TI_Stop()

#endif /* INC_IOHWAB_RTE_H_ */
