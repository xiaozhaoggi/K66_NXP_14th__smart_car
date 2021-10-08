#include "steering engine.h"
#include "MK60_ftm.h"
void SE_init()
{
ftm_pwm_init(ftm2,ftm_ch1,300,4100); //4100 ÖÐ   
	//3450 ×ó 
	//4750 ÓÒ

}