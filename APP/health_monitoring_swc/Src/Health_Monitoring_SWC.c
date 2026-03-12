#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "Health_Monitoring_SWC_rte.h"

void Health_Monitoring_SWC_runnable(void)
{
    // inputs
    double u1_data;
    double u2_data;
    double u3_data;
    Rte_read_RP_EnginTemp_EnginTemp(&u1_data);
    Rte_read_RP_OilPress_OilPress(&u2_data);
    Rte_read_RP_BattVoltage_BattVoltage(&u3_data);
    int32_t tmp7_data, tmp8_data, tmp9_data, tmp10_data, tmp12_data;
    double tmp14_data, tmp16_data, tmp18_data, tmp20_data, tmp21_data, tmp22_data, tmp23_data, tmp24_data, tmp25_data;
    
    // Source.sci(2:13-63):  emx_func_file('Health_Monitoring_SWC_runnable.c')
    // Source.sci(13:1-16):  tmp14 = 5 * u1;
    tmp14_data = 5.0 * u1_data;
    
    // Source.sci(14:1-16):  tmp16 = 5 * u2;
    tmp16_data = 5.0 * u2_data;
    
    // Source.sci(15:1-16):  tmp18 = 5 * u3;
    tmp18_data = 5.0 * u3_data;
    
    // Source.sci(17:1-24):  tmp20 = tmp14 ./ tmp15;
    tmp20_data = tmp14_data / 4095.0;
    
    // Source.sci(18:1-24):  tmp22 = tmp16 ./ tmp17;
    tmp22_data = tmp16_data / 4095.0;
    
    // Source.sci(19:1-24):  tmp24 = tmp18 ./ tmp19;
    tmp24_data = tmp18_data / 4095.0;
    
    // Source.sci(21:1-21):  tmp21 = 100 * tmp20;
    tmp21_data = 100.0 * tmp20_data;
    
    // Source.sci(22:1-21):  tmp23 = 100 * tmp22;
    tmp23_data = 100.0 * tmp22_data;
    
    // Source.sci(23:1-21):  tmp25 = 100 * tmp24;
    tmp25_data = 100.0 * tmp24_data;
    
    // Source.sci(25:1-30):  tmp8 = double(tmp21 >= tmp4);
    tmp8_data = (int32_t )((tmp21_data >= 110.0));
    
    // Source.sci(26:1-30):  tmp7 = double(tmp23 <= tmp5);
    tmp7_data = (int32_t )((tmp23_data <= 112.0));
    
    // Source.sci(27:1-30):  tmp9 = double(tmp25 <= tmp6);
    tmp9_data = (int32_t )((tmp25_data <= 6.0));
    
    // Source.sci(29:1-36):  tmp10 = double(tmp8 & tmp7 & tmp9);
    tmp10_data = (int32_t )(((bool )(tmp8_data) || (bool )(tmp7_data) || (bool )(tmp9_data)));
    
    // Source.sci(31-35):  if tmp10 >= 1 then
    if (tmp10_data >= 1) {
    // Source.sci(32:5-19):  tmp12 = tmp13;
    tmp12_data = 0;
    } else {
    // Source.sci(34:5-19):  tmp12 = tmp11;
    tmp12_data = 1;
    }
    
    // Source.sci(37:1-12):  y1 = tmp12;
    Rte_write_PP_VehicleMode_VehicleMode(tmp12_data);
}
