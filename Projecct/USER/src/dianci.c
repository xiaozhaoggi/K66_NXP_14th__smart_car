#include "dianci.h"
#include <string.h>
#include "findline.h"
#define total_cters 11
int L_AD_value,R_AD_value,M_AD_value,L_sum,R_sum,M_sum,R_L_delta;
float error_dc,abs_error,last_error,dianci_out,dianci_kp,dianci_kd;
void adc_config(void)
{
	adc_init(adc_chR);
	adc_init(adc_chL);
	adc_init(adc_chM);
	dianci_kp=25;
	dianci_kd=4;

}


void dianci(void)
{
	int8 i,j,k;
	//static  int init_induct=0; 
	int L_Temp[20],R_Temp[20],M_Temp[20],temp0;
	memset(L_Temp,0,sizeof(L_Temp));
	memset(R_Temp,0,sizeof(R_Temp));
	memset(R_Temp,0,sizeof(M_Temp));
	L_sum=0;
	R_sum=0;
	M_sum=0;
	
	
	for(i=0;i<20;i++)//0~18 9  
	{
		
		L_Temp[i]= adc_once(adc_chL,ADC_12bit);
		R_Temp[i]= adc_once(adc_chR,ADC_12bit);
		M_Temp[i]= adc_once(adc_chM,ADC_12bit);
	
		
/************限幅加中值**************************************/
		//--限幅
/*		if(i>0)
		{
			if(abs(L_Temp[i]-L_Temp[i-1])>300)
			{
				  L_Temp[i]=L_Temp[i-1];
			}
			if(abs(R_Temp[i]<R_Temp[i-1])>300)
			{
				R_Temp[i]=R_Temp[i-1];  
			}
		}      
*/		
	}
//--中值	
/*	for(j=0;j<10;j++)
	{
		for(k=0;k<(10-j);k++)//j=1,k<10,k=9,j=10,11-10=1,0he1 j=11,k<0
		{
			if(L_Temp[k]>L_Temp[k+1])
			{
				temp0=L_Temp[k+1];
				L_Temp[k+1]=L_Temp[k];
				L_Temp[k]=temp0; 
			}
	
		}
	}	
	L_AD_value=L_Temp[5];
	R_AD_value=R_Temp[5];
*/	
/***************中位值平均法****************************************/	
	//去最大和最小
	for(j=0;j<20;j++)
	{
		for(k=0;k<(20-j);k++)
		{
			if(L_Temp[k]>L_Temp[k+1])
			{
				temp0=L_Temp[k+1];
				L_Temp[k+1]=L_Temp[k];
				L_Temp[k]=temp0; 
			}
	
		}
	}
		for(j=0;j<20;j++)
	{
		for(k=0;k<(20-j);k++)
		{
			if(R_Temp[k]>R_Temp[k+1])
			{
				temp0=R_Temp[k+1];
				R_Temp[k+1]=R_Temp[k];
				R_Temp[k]=temp0; 
			}
	
		}
	}
		for(j=0;j<20;j++)
	{
		for(k=0;k<(20-j);k++)
		{
			if(M_Temp[k]>M_Temp[k+1])
			{
				temp0=M_Temp[k+1];
				M_Temp[k+1]=M_Temp[k];
				M_Temp[k]=temp0; 
			}
	
		}
	}
	//算术平均值


	for(j=1;j<20;j++)
	{
		

		L_sum+=L_Temp[j];
		R_sum+=R_Temp[j];
	  M_sum+=M_Temp[j];
	}
	L_AD_value=L_sum/19;
	R_AD_value=R_sum/19;
  M_AD_value=M_sum/19;
	if((L_AD_value + R_AD_value)!=0)
	{
		error_dc=(float)(R_AD_value-L_AD_value)/(float)(L_AD_value+R_AD_value)*100;
		
	}
	
		if((L_AD_value + R_AD_value)!=0 && HDbiaozhi ==zuo_huandao  )
	{
		error_dc=(float)(M_AD_value-L_AD_value)/(float)(L_AD_value+M_AD_value)*100;
			if(error_dc>-5)
			error_dc=-5;
		
	}       	                                 ///左环岛
	
			if((L_AD_value + R_AD_value)!=0 && HDbiaozhi ==you_huandao )
	{
		error_dc=(float)(R_AD_value-M_AD_value)/(float)(R_AD_value+M_AD_value)*100;
			if(error_dc<5)
			error_dc=5;
		                                          ///右环岛
	}
				if((L_AD_value + R_AD_value)!=0 && HDbiaozhi ==5 )
	{
		error_dc=(float)(R_AD_value-L_AD_value)/(float)(R_AD_value+L_AD_value)*100;
			if(error_dc>-5)
			error_dc=-5;
		                                          ///左环岛内
	}
				if((L_AD_value + R_AD_value)!=0 && HDbiaozhi ==6 )
	{
		error_dc=(float)(R_AD_value-L_AD_value)/(float)(R_AD_value+L_AD_value)*100;
			if(error_dc<5)
			error_dc=5;
		                                          ///右环岛内
	}
			if((L_AD_value + R_AD_value)!=0 && HDbiaozhi ==7 )
	{
		error_dc=(float)(R_AD_value-M_AD_value)/(float)(R_AD_value+M_AD_value)*100;
		                                          ///出左环岛
	}
				if((L_AD_value + R_AD_value)!=0 && HDbiaozhi ==8 )
	{
		error_dc=(float)(M_AD_value-L_AD_value)/(float)(M_AD_value+L_AD_value)*100;
		                                          ///出右环岛
	}
	R_L_delta=abs(R_AD_value-L_AD_value);
	if(error_dc>75)   {ftm_pwm_duty(ftm2,ftm_ch1,(4100+650));}
	if(error_dc<(-75)){ftm_pwm_duty(ftm2,ftm_ch1,(4100-650));}
	abs_error=abs(error_dc);
	
//#if 0	
//	if(die_value==8)
//	{
//		if(((L_AD_value + R_AD_value)/2)>=(init_induct*2))
//		{		//1600+1600/2=1600							//1600/2=800*2=1600
//			dianci_kp=40;
//			dianci_out=dianci_kp*(-error_dc);
//			if(dianci_out>650){ftm_pwm_duty(ftm2,ftm_ch1,(4100+650));}//5000 ~-45    10000~45   111~1°
//			if(dianci_out<-650){ftm_pwm_duty(ftm2,ftm_ch1,(4100-650));}
//			else {ftm_pwm_duty(ftm2,ftm_ch1,(4100+dianci_out));}
//			gpio_turn(D2);
//			lcd_showint16(60,8,init_induct);
//			return ;
//		}	
//	}
//	
//#endif	

	if(abs_error>70)
	{
		dianci_kp=10;
		dianci_kd=10;
	}     //30 27 24 
	
	else if((abs_error<=70)&&(abs_error>40)){
		dianci_kp=15;
		dianci_kd=10;
	}
	else if((abs_error<=40)&&(abs_error>20)){
		dianci_kp=15;
		dianci_kd=20;
	}//25
	
	else if((abs_error<=20)&&(abs_error>4))
	{
		dianci_kp=10;
		dianci_kd=30;
	} //20
	else if(abs_error<=4)
	{	dianci_kp=0;
		dianci_kd=20;
	}
	
	if(HDbiaozhi ==zuo_huandao || HDbiaozhi ==you_huandao)
	{
		dianci_kp=70;
		dianci_kd=0;
	}
	if( HDbiaozhi ==5|| HDbiaozhi ==6 ||HDbiaozhi ==7|| HDbiaozhi ==8)
  {
		dianci_kp=25;
		dianci_kd=10;
	}
	
											//1666.6 ~30°  833~15°

//	if(flag_l==1){ftm_pwm_duty(ftm2,ftm_ch1,(7500-2000));flag_l==0;}
//	if(flag_r==1){ftm_pwm_duty(ftm2,ftm_ch1,(7500+2000));flag_r==0;}
//	
//	if(dianci_out>650){ftm_pwm_duty(ftm2,ftm_ch1,(4100+650));}
//	if(dianci_out<-650){ftm_pwm_duty(ftm2,ftm_ch1,(4100-650));}
//	else { ftm_pwm_duty(ftm2,ftm_ch1,(4100+dianci_out));}
	  if(dianci_out>650)  
		dianci_out=650;
	  if(dianci_out<-650)	
		dianci_out=-650;	 
	  last_error=error_dc; 
	


}

void recursive(void)
{
	int cter1=total_cters,cter2;
	static int flag_r=0,flag_l=0;
	static int L_Temp[20]={0},R_Temp[20]={0};
	const int coe[total_cters]={1,3,5,7,9,11,13,15,17,19,21};
	const int sum_coe=1+3+5+7+9+11+13+15+17+19+21;
	L_sum=0;R_sum=0;
	L_Temp[cter1]= adc_once(adc_chL,ADC_8bit);//第12次的值
	R_Temp[cter1]= adc_once(adc_chR,ADC_8bit);//0-10
	for(cter1=0;cter1<(total_cters);cter1++)//0-9   0-10   11ge
	{
		
					//0-10  0 <- 1  1<- 2   9<-10 
		
		L_Temp[cter1]=L_Temp[cter1+1];  //0-10 10<- 11
		R_Temp[cter1]=R_Temp[cter1+1];
		L_sum+=L_Temp[cter1]*coe[cter1];
		R_sum+=R_Temp[cter1]*coe[cter1];	
	}
	L_AD_value=L_sum/sum_coe;
	R_AD_value=R_sum/sum_coe;
	if((L_AD_value + R_AD_value)!=0)
	{
		error_dc=(float)(R_AD_value-L_AD_value)/(float)(L_AD_value+R_AD_value)*100;
	}
	
	dianci_out=dianci_kp*error_dc;              //p控制
	
//	if((L_Temp[5]>200)&&(flag_r==1)){flag_r=0;}
//	if((R_Temp[5]>200)&&(flag_l==1)){flag_l=0;}
	if((L_AD_value<200)&&(R_AD_value>=200)){flag_r=1;}
	if((R_AD_value<200)&&(L_AD_value>=200)){flag_l=1;}
	
	if(dianci_out>2200){dianci_out=2200;}
	if(dianci_out<-2200){dianci_out=-2200;}
	if(flag_l==1){ftm_pwm_duty(ftm2,ftm_ch1,(7500-2200));flag_l=0;}
	if(flag_r==1){ftm_pwm_duty(ftm2,ftm_ch1,(7500+2200));flag_r=0;}
	else {ftm_pwm_duty(ftm2,ftm_ch1,(7500+dianci_out));}
	last_error=error_dc;


}	


