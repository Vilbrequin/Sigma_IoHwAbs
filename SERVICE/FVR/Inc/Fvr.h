/*
 * Fvr.h
 *
 *  Created on: Nov 1, 2025
 *      Author: Lenovo X13
 */

#ifndef INC_FVR_H_
#define INC_FVR_H_

#include <stdint.h>

#define FVR_NUM_OF_VALID_RANGES			4U

/*FVR Valid Ranges*/
#define FVR_OFF							0U
#define FVR_IGNORED						1U
#define FVR_OPERATIONEL					2U

void fvr_process_in(uint16_t Cs, uint8_t* Data);
void fvr_process_out_tor(uint16_t CS, uint8_t OP);
void fvr_process_out_pwm(uint16_t Cs, uint8_t OP);


#endif /* INC_FVR_H_ */
