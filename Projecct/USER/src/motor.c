#include "motor.h"
#include "MK60_ftm.h"
void motor_init()
{
 ftm_pwm_init(ftm0,ftm_ch2,16000,0);  //·´
 ftm_pwm_init(ftm0,ftm_ch3,16000,0);  //Õý
	
}

void motor_zhuan()
{ 
	motor_init();
  
 ftm_pwm_duty(ftm0,ftm_ch2,0);	
 ftm_pwm_duty(ftm0,ftm_ch3,0);	



}

