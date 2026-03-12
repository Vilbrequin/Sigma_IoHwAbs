#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "Wipper_Washing_swc.h"
double z2_data = 0;
double z19_data = 0;

void Wipper_reader(int * prev_status , int raw_value){
  switch(*prev_status)
        {
            case 0:
                if(raw_value > 1400)
                    *prev_status = 1;
                break;

            case 1:
                if(raw_value < 1200)
                    *prev_status = 0;
                else if(raw_value > 2800)
                    *prev_status = 2;
                break;

            case 2:
                if(raw_value < 2600)
                    *prev_status = 1;
                break;
        }
}
void washer_wipper_part1(double * const y1_data, double * const y2_data, double u1_data, double u2_data) {
  double tmp1_data, tmp2_data, tmp3_data, tmp4_data, tmp5_data, tmp8_data, tmp9_data, tmp10_data, tmp11_data, tmp12_data; 
  double tmp13_data, tmp14_data; 
  double tmp15_data = 0.0; 
  double tmp16_data, tmp17_data, tmp18_data, tmp19_data, tmp20_data, tmp21_data, tmp22_data, tmp23_data, tmp24_data, tmp25_data; 
  double tmp26_data, tmp27_data, tmp28_data, tmp29_data; 
  
  // Source.sci(2:13-55):  emx_func_file('washer_wipper_part1_t1.c')
  // Source.sci(3:2-12):  tmp9 = z2;
  tmp9_data = z2_data; 
  
  // Source.sci(4:5-16):  tmp4 = z19;
  tmp4_data = z19_data; 
  
  // Source.sci(5:5-15):  tmp8  = 1;
  tmp8_data = 1.0; 
  
  // Source.sci(6:5-15):  tmp12 = 0;
  tmp12_data = 0.0; 
  
  // Source.sci(7:5-15):  tmp17 = 1;
  tmp17_data = 1.0; 
  
  // Source.sci(9:5-28):  [tmp15] = get_v_mode(1)
  Rte_write_RP_VehicleMode_VehicleMode(&tmp15_data);
  
  // Source.sci(11:5-15):  tmp13 = 2;
  tmp13_data = 2.0; 
  
  // Source.sci(13:5-15):  tmp18 = 0;
  tmp18_data = 0.0; 
  
  // Source.sci(14:5-15):  tmp19 = 0;
  tmp19_data = 0.0; 
  
  // Source.sci(16:5-15):  tmp20 = 1;
  tmp20_data = 1.0; 
  
  // Source.sci(17:5-15):  tmp21 = 0;
  tmp21_data = 0.0; 
  
  // Source.sci(19:5-15):  tmp25 = 0;
  tmp25_data = 0.0; 
  
  // Source.sci(21:5-34):  tmp10 = double(tmp8 == tmp9);
  tmp10_data = (double )((tmp8_data == tmp9_data)); 
  
  // Source.sci(22:5-33):  tmp11 = double(u1 == tmp12);
  tmp11_data = (double )((u1_data == tmp12_data)); 
  
  // Source.sci(23:5-33):  tmp14 = double(tmp13 == u2);
  tmp14_data = (double )((tmp13_data <= u2_data)); 
  
  // Source.sci(24:5-33):  tmp22 = double(u1 == tmp19);
  tmp22_data = (double )((u1_data == tmp19_data)); 
  
  // Source.sci(26:5-13):  y1 = u1;
  *y1_data = u1_data; 
  
  // Source.sci(28:5-35):  tmp5  = double(tmp10 & tmp11);
  tmp5_data = (double )(((bool )(tmp10_data) && (bool )(tmp11_data))); 
  
  // Source.sci(29:5-35):  tmp16 = double(tmp15 & tmp14);
  tmp16_data = (double )(((bool )(tmp15_data) && (bool )(tmp14_data))); 
  
  // Source.sci(31-35):  if tmp16 > 2 then
  if (tmp16_data >= 1.0) {
    // Source.sci(32:9-22):  tmp1 = tmp17;
    tmp1_data = tmp17_data; 
  } else {
    // Source.sci(34:9-19):  tmp1 = u2;
    tmp1_data = u2_data; 
  } 
  
  // Source.sci(37:5-27):  tmp23 = double(~tmp5);
  tmp23_data = (double )(( ! tmp5_data)); 
  
  // Source.sci(38:5-33):  tmp29 = double(tmp5 | tmp4);
  tmp29_data = (double )(((bool )(tmp5_data) || (bool )(tmp4_data))); 
  
  // Source.sci(40:5-34):  tmp24 = double(tmp1 > tmp18);
  tmp24_data = (double )((tmp1_data > tmp18_data)); 
  
  // Source.sci(42-46):  if tmp29 >= 1 then
  if (tmp29_data >= 1.0) {
    // Source.sci(43:9-23):  tmp26 = tmp20;
    tmp26_data = tmp20_data; 
  } else {
    // Source.sci(45:9-23):  tmp26 = tmp21;
    tmp26_data = tmp21_data; 
  } 
  
  // Source.sci(48:5-43):  tmp27 = double(tmp23 & tmp22 & tmp24);
  tmp27_data = (double )(((bool )(tmp23_data) && (bool )(tmp22_data) && (bool )(tmp24_data))); 
  
  // Source.sci(50:5-25):  tmp3 = tmp4 + tmp26;
  tmp3_data = tmp4_data + tmp26_data; 
  
  // Source.sci(52-56):  if tmp3 > 4 then
  if (tmp3_data > 6.0) {
    // Source.sci(53:9-22):  tmp2 = tmp25;
    tmp2_data = tmp25_data; 
  } else {
    // Source.sci(55:9-21):  tmp2 = tmp3;
    tmp2_data = tmp3_data; 
  } 
  
  // Source.sci(58-62):  if tmp27 >= 1 then
  if (tmp27_data >= 1.0) {
    // Source.sci(59:9-22):  tmp28 = tmp1;
    tmp28_data = tmp1_data; 
  } else {
    // Source.sci(61:9-22):  tmp28 = tmp2;
    tmp28_data = (bool)tmp2_data; 
  } 
  
  // Source.sci(64:5-16):  y2 = tmp28;
  *y2_data = tmp28_data; 
  
  // Source.sci(65:5-16):  z19 = tmp2;
  z19_data = tmp2_data; 
  
  // Source.sci(66:5-13):  z2 = u1;
  z2_data = u1_data; 
 
} 


double z1_data_3 = 0.0;
double z8_data_3 = 0.0;
double z16_data_3 = 0.0;

void washer_manger(double * const y1_data, double u1_data, double u2_data) {
  double tmp3_data, tmp4_data, tmp5_data, tmp6_data, tmp7_data, tmp8_data; 
  int32_t tmp10_data; 
  double tmp11_data, tmp12_data, tmp13_data, tmp16_data, tmp17_data, tmp18_data; 
  int32_t tmp19_data; 
  double tmp20_data; 
  int32_t tmp21_data; 
  double tmp22_data, tmp23_data, tmp24_data; 
  

  tmp16_data = z1_data_3; 
  
  // Source.sci(21:5-15):  tmp3 = z8;
  tmp3_data = z8_data_3; 
  
  // Source.sci(22:5-17):  tmp11 = z16;
  tmp11_data = z16_data_3; 
  
  // Source.sci(25:5-15):  tmp8  = 0;
  tmp8_data = 0.0; 
  
  // Source.sci(26:5-15):  tmp13 = 0;
  tmp13_data = 0.0; 
  
  // Source.sci(27:5-15):  tmp12 = 1;
  tmp12_data = 1.0; 
  
  // Source.sci(30:5-15):  tmp22 = 0;
  tmp22_data = 0.0; 
  
  // Source.sci(32:5-35):  tmp10 = double(tmp16 >= tmp9);
  tmp10_data = (int32_t )((tmp16_data >= 1.0)); 
  
  // Source.sci(33:5-32):  tmp6  = double(u1 == tmp8);
  tmp6_data = (double )((u1_data == tmp8_data)); 
  
  // Source.sci(34:5-31):  tmp21 = double(u1 | tmp3);
  tmp21_data = (int32_t )(((bool )(u1_data) || (bool )(tmp3_data))); 
  
  // Source.sci(36-40):  if u1 > 0 then
  if (u1_data > 0.0) {
    // Source.sci(37:9-20):  tmp24 = u1;
    tmp24_data = u1_data; 
  } else {
    // Source.sci(39:9-22):  tmp24 = tmp3;
    tmp24_data = tmp3_data; 
  } 
  
  // Source.sci(42:5-34):  tmp17 = double(tmp10 & tmp6);
  tmp17_data = (double )(((bool )(tmp10_data) && (bool )(tmp6_data))); 
  
  // Source.sci(43:5-31):  tmp5  = double(u2 & tmp6);
  tmp5_data = (double )(((bool )(u2_data) && (bool )(tmp6_data))); 
  
  // Source.sci(45-49):  if tmp21 > 0 then
  if (tmp21_data > 0) {
    // Source.sci(46:9-23):  tmp23 = tmp24;
    tmp23_data = tmp24_data; 
  } else {
    // Source.sci(48:9-23):  tmp23 = tmp22;
    tmp23_data = tmp22_data; 
  } 
  
  // Source.sci(51:5-35):  tmp19 = double(tmp17 | tmp11);
  tmp19_data = (int32_t )(((bool )(tmp17_data) || (bool )(tmp11_data))); 
  
  // Source.sci(53-57):  if tmp5 > 0 then
  if (tmp5_data > 0.0) {
    // Source.sci(54:9-22):  tmp4 = tmp15;
    tmp4_data = 0.0; 
  } else {
    // Source.sci(56:9-22):  tmp4 = tmp23;
    tmp4_data = tmp23_data; 
  } 
  
  // Source.sci(59-63):  if tmp19 >= 1 then
  if (tmp19_data >= 1) {
    // Source.sci(60:9-23):  tmp20 = tmp12;
    tmp20_data = tmp12_data; 
  } else {
    // Source.sci(62:9-23):  tmp20 = tmp13;
    tmp20_data = tmp13_data; 
  } 
  
  // Source.sci(65-69):  if tmp5 > 0 then
  if (tmp5_data > 0.0) {
    // Source.sci(66:9-22):  tmp7 = tmp14;
    tmp7_data = 0.0; 
  } else {
    // Source.sci(68:9-22):  tmp7 = tmp20;
    tmp7_data = tmp20_data; 
  } 
  
  // Source.sci(71-75):  if tmp7 > 0 then
  if (tmp7_data > 0.0) {
    // Source.sci(72:9-22):  tmp18 = tmp4;
    tmp18_data = tmp4_data; 
  } else {
    // Source.sci(74:9-20):  tmp18 = u1;
    tmp18_data = u1_data; 
  } 
  
  z1_data_3 = u1_data;
  z8_data_3 = tmp4_data;
  z16_data_3 = tmp7_data;
  // Source.sci(70:5-16):  y1 = tmp18;
  *y1_data = tmp18_data; 
} 

double z2_data_4 =1;
double z8_data_4 =0;


void pwm_wipper_calc(double * const y1_data, double u1_data) {
double tmp1_data, tmp2_data, tmp4_data, tmp5_data, tmp6_data, tmp7_data, tmp8_data, tmp9_data, tmp10_data; 

  tmp2_data = z2_data_4; 
  
  // Source.sci(15:5-15):  tmp8 = z8;
  tmp8_data = z8_data_4; 
  
  // Source.sci(17:5-15):  tmp5 = -1;
  tmp5_data = -1.0;
  
  // Source.sci(18:5-14):  tmp7 = 1;
  tmp7_data = 1.0;
  
  // Source.sci(19:5-23):  tmp4 = tmp2 .* u1;
  tmp4_data = tmp2_data * u1_data; 
  
  // Source.sci(20:5-24):  tmp1 = tmp8 + tmp4;
  tmp1_data = tmp8_data + tmp4_data; 
  
  // Source.sci(22-26):  if tmp1 >= 180 then
  if (tmp1_data >= 180.0) {
    // Source.sci(23:9-21):  tmp6 = tmp5;
    tmp6_data = tmp5_data; 
  } else {
    // Source.sci(25:9-21):  tmp6 = tmp2;
    tmp6_data = tmp2_data; 
  } 
  
  // Source.sci(28-32):  if tmp1 > 0 then
  if (tmp1_data > 0.0) {
    // Source.sci(29:9-22):  tmp10 = tmp1;
    tmp10_data = tmp1_data; 
  } else {
    // Source.sci(31:9-20):  tmp10 = u1;
    tmp10_data = u1_data; 
  } 
  
  // Source.sci(34-38):  if tmp1 > 0 then
  if (tmp1_data > 0.0) {
    // Source.sci(35:9-21):  tmp9 = tmp6;
    tmp9_data = tmp6_data; 
  } else {
    // Source.sci(37:9-21):  tmp9 = tmp7;
    tmp9_data = tmp7_data; 
  } 
  
  // Source.sci(39:2-12):  z2 = tmp9;
  z2_data_4 = tmp9_data; 
  
  // Source.sci(40:2-12):  z8 = tmp1;
  //z8_data_4 = tmp1_data; 
  
  // Source.sci(41:5-16):  y1 = tmp10;
  if (u1_data == 0)
  {
    /* code */
    z8_data_4 = 0.0;
    *y1_data = 0.0;
  }else
  {
    z8_data_4 = tmp1_data; 
    *y1_data = tmp10_data; 
  }
}
uint16_t counter = 1000;

void  Wipper_Washer_runnable(void)
{
    // inputs
    double u1_data;
    double u2_data;
    double u3_data;
    static int prev_status = 0; 
    Rte_read_RP_WasherBtn_PressCounter(&u1_data);
    Rte_read_RP_WipperLevel_WipperLevel(&u2_data);
    Rte_read_RP_WipperPos_WipperPos(&u3_data);
    double tmp0 , tmp1 , tmp2 , tmp_3 , tmp4;
    Wipper_reader(&prev_status, (int)u2_data);
    washer_wipper_part1(&tmp_3, &tmp1, u1_data, prev_status); 
    washer_manger(&tmp2, tmp1, u3_data);
    pwm_wipper_calc(&tmp4, tmp2);
    Rte_write_PP_WasherState_WasherState(tmp_3);
    Rte_write_PP_WipperDc_WipperDc(tmp4);
}
