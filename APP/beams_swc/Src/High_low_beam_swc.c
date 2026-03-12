/* Code g�n�r� automatiquement */
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "High_low_Beam_swc.h"

void High_low_Beam_runnable(void)
{
    // inputs
    double u1_data;
    double u2_data;
    Rte_read_RP_HighBeamBtn_PressCounter(&u1_data);
    Rte_read_RP_LowBeamBtn_PressCounter(&u2_data);
    int32_t tmp7_data, tmp8_data;
    
    // Source.sci(2:13-59):  emx_func_file('SWC_High_low_Beam_runnable.c')
    // Source.sci(9-13):  if u1 >= 1 then
    if (u1_data >= 1.0) {
    // Source.sci(10:9-21):  tmp7 = tmp3;
    tmp7_data = 90;
    } else {
    // Source.sci(12:9-21):  tmp7 = tmp4;
    tmp7_data = 0;
    }
    
    // Source.sci(14-18):  if u2 >= 1 then
    if (u2_data >= 1.0) {
    // Source.sci(15:9-21):  tmp8 = tmp5;
    tmp8_data = 60;
    } else {
    // Source.sci(17:9-21):  tmp8 = tmp6;
    tmp8_data = 0;
    }
    
    // Source.sci(19:5-15):  y1 = tmp7;
    Rte_write_PP_HighBeamDc_HighBeamDc((tmp7_data));
    
    // Source.sci(20:5-15):  y2 = tmp8;
    Rte_write_PP_LowBeamDc_LowBeamDc((tmp8_data));
}
