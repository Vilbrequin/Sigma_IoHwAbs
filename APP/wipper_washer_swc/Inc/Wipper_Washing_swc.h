#ifndef WIPPER_WASHING_SWC_H
#define WIPPER_WASHING_SWC_H

#include "Wipper_Washing_rte.h"

// static
void washer_wipper_part1(double * const y1_data, double * const y2_data, double u1_data, double u2_data);
void washer_manger(double * const y1_data, double u1_data, double u2_data);
void pwm_wipper_calc(double * const y1_data, double u1_data);

// global
void Wipper_Washer_runnable(void);

#endif /* WIPPER_WASHING_RTE_H */
