/*
 * Fvr_cfg.h
 *
 *  Created on: Nov 2, 2025
 *      Author: Lenovo X13
 */

#ifndef INC_FVR_CFG_H_
#define INC_FVR_CFG_H_

#include "Fvr.h"

#define FVR_NUM_OUT_CHANNELS				4U
#define FVR_NUM_IN_CHANNELS					7U


extern const uint8_t fvr_out_channels[FVR_NUM_OUT_CHANNELS];

extern const uint8_t fvr_in_channels[FVR_NUM_IN_CHANNELS];

extern const uint8_t fvr_in_action[FVR_NUM_IN_CHANNELS][FVR_NUM_OF_VALID_RANGES];

extern const uint8_t fvr_out_action[FVR_NUM_OUT_CHANNELS][FVR_NUM_OF_VALID_RANGES];

#endif /* INC_FVR_CFG_H_ */
