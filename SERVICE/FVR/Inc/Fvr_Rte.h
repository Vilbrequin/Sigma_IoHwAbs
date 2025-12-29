/*
 * Fvr_Rte.h
 *
 *  Created on: Nov 8, 2025
 *      Author: Lenovo X13
 */

#ifndef INC_FVR_RTE_H_
#define INC_FVR_RTE_H_

extern void fvr_process_in(uint16_t Cs, uint8_t* Data);
extern void fvr_process_out_tor(uint16_t Cs, uint8_t OP);

#define FRONT_RIGHT_WINDOW_BUTTON					0x00U
#define FRONT_LEFT_WINDOW_BUTTON					0x01U
#define BACK_RIGHT_WINDOW_BUTTON					0x02U
#define FVR_BACK_LEFT_WINDOW_BUTTON					0x03U

#define INTRIOR_LAMP								0x00U
#define HVAC_FAN									0x01U
#define RIGHT_TURN_INDICATOR						0x02U
#define LEFT_TURN_INDICATOR							0x03U

#define CLEAR										0x00
#define SET											0x01

#define STOP										0x00
#define START										0x01



#define Fvr_Front_Right_Window_Button(command)		fvr_process_in(FRONT_RIGHT_WINDOW_BUTTON, command)
#define Fvr_Front_Left_Window_Button(command)		fvr_process_in(FRONT_LEFT_WINDOW_BUTTON, command)
#define Fvr_Back_Right_Window_Button(command)		fvr_process_in(BACK_RIGHT_WINDOW_BUTTON, command)
#define Fvr_Back_Left_Window_Button(command)		fvr_process_in(FVR_BACK_LEFT_WINDOW_BUTTON, command)

#define Fvr_Intrior_Lamp_Set()						fvr_process_out_tor(INTRIOR_LAMP, SET)
#define Fvr_Intrior_Lamp_Clear()					fvr_process_out_tor(INTRIOR_LAMP, CLEAR)

#define Fvr_Hvac_Fan_Start()						fvr_process_out_tor(HVAC_FAN, START)
#define Fvr_Hvac_Fan_Stop()							fvr_process_out_tor(HVAC_FAN, STOP)

#define Fvr_Right_Turn_Indicator_Set()				fvr_process_out_tor(RIGHT_TURN_INDICATOR, SET)
#define Fvr_Right_Turn_Indicator_Clear()			fvr_process_out_tor(RIGHT_TURN_INDICATOR, CLEAR)

#define Fvr_Left_Turn_Indicator_Set()				fvr_process_out_tor(LEFT_TURN_INDICATOR, SET)
#define Fvr_Left_Turn_Indicator_Clear()				fvr_process_out_tor(LEFT_TURN_INDICATOR, CLEAR)

#define Fvr_PWM_High_Beam_Start(dc)					fvr_process_out_pwm(PMM_HEAD_LAMPS_HIGH_BEAM, dc ,START)
#define Fvr_PWM_High_Beam_Stop()					fvr_process_out_pwm(PMM_HEAD_LAMPS_HIGH_BEAM, STOP, 0)

#define Fvr_PWM_Low_Beam_Start(dc)					fvr_process_out_pwm(PMM_HEAD_LAMPS_LOW_BEAM, dc ,START)
#define Fvr_PWM_Low_Beam_Stop()						fvr_process_out_pwm(PMM_HEAD_LAMPS_LOW_BEAM, STOP, 0)

#define Fvr_PWM_Right_TI_Start(dc)					fvr_process_out_pwm(PMM_RIGHT_TI, dc ,START)
#define Fvr_PWM_Right_TI_Stop()						fvr_process_out_pwm(PMM_RIGHT_TI, STOP, 0)

#define Fvr_PWM_Left_TI_Start(dc)					fvr_process_out_pwm(PMM_LEFT_TI, dc ,START)
#define Fvr_PWM_Left_TI_Stop()						fvr_process_out_pwm(PMM_LEFT_TI, STOP, 0)



#endif /* INC_FVR_RTE_H_ */
