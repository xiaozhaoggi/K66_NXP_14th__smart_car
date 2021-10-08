#ifndef _DIANCI_H_
#define _DIANCI_H_
#include "headfile.h"
#include "common.h"
#include "misc.h"

#define adcn    ADC1
#define adc_chR			ADC1_SE10				//B4           
#define adc_chL			ADC1_SE9			//B1
#define adc_chM			ADC1_SE8       //B0

									//ADC1_SE11,      // B5			
                              // 8    //B0
//extern int init_induct;							  
extern int L_AD_value,R_AD_value,M_AD_value,L_sum,R_sum,M_sum,R_L_delta;
extern float error_dc,abs_error,last_error,dianci_out,dianci_kp,dianci_kd;
void adc_config(void);
void dianci(void);
void recursive(void);
#endif
