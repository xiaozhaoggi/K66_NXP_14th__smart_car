#include "pid.h"
#include "headfile.h"
#include "findline.h"
#include "integer.h"
#include "dianci.h"
struct PID_Control SE_PID;
struct PID_Control Motor_PID;
int Plan=1;    
//0 ：快      
//1 ： 稳   
//2 ：  电磁有环  
//3 ：   电磁无环 

void SE_PID_init(void)
{

	SE_PID.Kp=60;
	SE_PID.Ki=7;
	SE_PID.Kd=10;
	SE_PID.pwm=4100;    //4100

}

void Motor_PID_init(void)
{
	Motor_PID.Kp=80;
	Motor_PID.Ki=10;
	Motor_PID.Kd=0;
	Motor_PID.pwm=2000;
}

int S_e0,S_e1;
int S_kp,S_kd;
int Kp_error;
int Kp_e;
int error;

void SE_control()
{  
	error = w_error1;	
	
  //zhangai_duanlu();
//	if(Plan==0 || Plan==1 || Plan==2 || Plan==3)
//	huandao();
//	dianci_sup();
//	 shizi();	
	
//	 Kp_error=(8*error-2*xielv)/10;   //斜率数值相反 用 - 号  下同
	if(Plan==0)
	{		
	 S_e1 = S_e0;
   S_e0 = error;
	
	 if(abs(S_e0)<=3)
	 {
		 
	  S_kp=30;
    S_kd=50; 
	 }
	 if(abs(S_e0)>=3)
	 {
//		 if(M_nowpoint >30)
//		 {
//			S_kp =60;  
//		  S_kd =20;
//		 }
//		 else
//			 
//		{
		 S_kp=40; 
		 S_kd=40; 
//		}
	 }
	 
	 if(abs(S_e0)>=10 )
 	 {
		 if(M_nowpoint >15)
		 
		 {
	  	S_kp =45;  
		  S_kd =20;
	  	}
		else
			{
	  	S_kp =30;  
		  S_kd =20;
		  }
			
	 }
		
	 	 if(abs(S_e0)>=15)
 	 {
		 if(M_nowpoint >15)
		 
		 {
	  	S_kp =50;  
		  S_kd =20;
	  	}
		 	else
		{	
				
			S_kp =30;  
		  S_kd =20;
			
		}
	 }
	 
	 if(ZAbiaozhi==0 && DLbiaozhi==0 && HDbiaozhi == 0)
   {
	 SE_PID.pwm = S_kp*S_e0 + S_kd*(S_e0-S_e1)+ 4100;  
	 }
	 
	 dianci_out=dianci_kp*error_dc+dianci_kd*(error_dc-last_error);               //电磁pid
	 if(ZAbiaozhi == 0 && (DLbiaozhi == 1  || HDbiaozhi == zuo_huandao || HDbiaozhi == 5 || HDbiaozhi ==7 || HDbiaozhi == you_huandao || HDbiaozhi == 6 || HDbiaozhi ==8 || yangguang_flag == 1))
{	
	if(dianci_out>700)  
		dianci_out=700;
	  if(dianci_out<-700)	
		dianci_out=-700;	 
		SE_PID.pwm=4100+dianci_out;
                                     //断路,十字，环岛电磁寻迹 
}	    
}
		 
	if(Plan == 1)
	{
		 dianci_out=dianci_kp*error_dc+dianci_kd*(error_dc-last_error);               //电磁pid
	 if(ZAbiaozhi == 0)
	 {
		if(dianci_out>700)  
		dianci_out=700;
	  if(dianci_out<-700)	
		dianci_out=-700;	 
		SE_PID.pwm=4100+dianci_out;
	 }
	  if( ZAbiaozhi == 3)
	{
		 		
	 S_e1 = S_e0;
   S_e0 = error;
	
	 if(abs(S_e0)<=3)
	 {
		 
	  S_kp=30;
    S_kd=40; 
	 }
	 if(abs(S_e0)>=3)
	 {
		S_kp=40; 
		S_kd=40; 
	 }
	 
	 if(abs(S_e0)>=10 )
 	 {
		 if(M_nowpoint >20)
		 
		 {
	  	S_kp =45;  
		  S_kd =20;
	  	}
		else
			{
	  	S_kp =30;  
		  S_kd =30;
		  }
			
	 }
		
	 	 if(abs(S_e0)>=15)
 	 {
		 if(M_nowpoint >20)
		 
		 {
	  	S_kp =50;  
		  S_kd =20;
	  	}
		 	else
		{	
				
			S_kp =30;  
		  S_kd =20;
			
		}
	 }
 
	 
	 SE_PID.pwm = S_kp*S_e0 + S_kd*(S_e0-S_e1)+ 4100;  
	 
		
		
		
		}
	}	
if(abs(S_e0)<2 && abs(dianci_out) <5 && DLbiaozhi==0 && ZAbiaozhi==0 && shizi_flag==0 && HDbiaozhi==0 )
	 	SE_PID.pwm = 4100; 

	
	 if(SE_PID.pwm>4800)
		 SE_PID.pwm=4800;
	 
	 if(SE_PID.pwm<3400)
		 SE_PID.pwm=3400;

	 ftm_pwm_duty(ftm2,ftm_ch1,SE_PID.pwm);

}


int M_e0,M_e1,M_e2;
int M_kp,M_ki,M_kd;
int16 M_nowpoint;
int16 M_setpoint;
int motor_time=0;
extern int CarSpeed[3];
void Motor_control()
{  
  	motor_time++;
	 
//	 M_kp =Motor_PID.Kp;
//	 M_ki =Motor_PID.Ki;
//   M_kd =Motor_PID.Kd;
	
   M_nowpoint= CarSpeed[2];
if(Plan == 0)

{
//		M_setpoint=35; 	
//	  if(abs(w_error1) >= 3)
//	  M_setpoint=30; 
//	  if(abs(w_error1) >= 10)
	  M_setpoint=15; 
//	  if(abs(w_error1) >= 15)
//  	M_setpoint=15 ;
//		if(abs(w_error1) >= 20)
//	  M_setpoint=10; 		
	/////////////////////////////	
//	  if(DLbiaozhi == 1  )
//	  M_setpoint=15; 	 
//	  if(DLbiaozhi == 1 && abs(dianci_out) >600 )
//	  M_setpoint=7;
//	 if(DLbiaozhi == 1 && abs(dianci_out) >600)
//	 M_setpoint=2; 
//	 if(distance<100)
//	 M_setpoint=7; 
//	 if(ZAbiaozhi!=0  )
//	 M_setpoint=7; 
//	 if(HDbiaozhi !=0 )
//	 M_setpoint=7;
//	 if(HDbiaozhi ==3 || HDbiaozhi ==4 )
//	 M_setpoint=5;
//	 if(yangguang_flag == 1)
//	 M_setpoint=7;
//   if(L_AD_value>2000||R_AD_value>2000)
//	 M_setpoint=3;
	 M_kp =70;
	 M_kd =20;

 }
if(Plan == 1)
{
		M_setpoint=10; 
	
//		if(abs(w_error1) >= 20)
//	  M_setpoint=10; 		
	/////////////////////////////	
//	  if(DLbiaozhi == 1  )
//	  M_setpoint=10; 	 
//	  if(DLbiaozhi == 1 && abs(dianci_out) >600 )
//	  M_setpoint=7;

//	 if(DLbiaozhi == 1 && abs(dianci_out) >600)
//	 M_setpoint=2; 
//	 if(distance<100)
//	 M_setpoint=7; 
//	 if(ZAbiaozhi!=0  )
//	 M_setpoint=7; 
//	 if(HDbiaozhi !=0 )
//	 M_setpoint=7;
//	 if(HDbiaozhi ==3 || HDbiaozhi ==4 )
//	 M_setpoint=5;
//	 if(yangguang_flag == 1)
//	 M_setpoint=7;
//   if(L_AD_value>2000||R_AD_value>2000)
//	 M_setpoint=3;
	 M_kp =60;
	 M_kd =10;
	 
 }
if(Plan == 2 )
{ 
		M_setpoint=60; 
	  if(abs(w_error1) >= 1)
		M_setpoint=45; 	
    if(abs(w_error1) >= 2)
		M_setpoint=40; 	
	  if(abs(w_error1) >= 3)
	  M_setpoint=35; 
	  if(abs(w_error1) >= 10)
	  M_setpoint=25; 
	  if(abs(w_error1) >= 15)
  	M_setpoint=15 ;
//		if(abs(w_error1) >= 20)
//	  M_setpoint=10; 		
	/////////////////////////////	
	  if(DLbiaozhi == 1  )
	  M_setpoint=15; 	 
	  if(DLbiaozhi == 1 && abs(dianci_out) >600 )
	  M_setpoint=7;
//	 if(DLbiaozhi == 1 && abs(dianci_out) >600)
//	 M_setpoint=2; 
	 if(distance<100)
	 M_setpoint=5; 
	 if(ZAbiaozhi!=0  )
	 M_setpoint=7; 
	 if(HDbiaozhi !=0 )
	 M_setpoint=7;
	 if(HDbiaozhi ==3 || HDbiaozhi ==4 )
	 M_setpoint=5;
	 if(yangguang_flag == 1)
	 M_setpoint=7;
   if(L_AD_value>2000||R_AD_value>2000)
	 M_setpoint=3;
	 M_kp =80;
	 M_kd =30;

}
if(Plan ==3)
{
		M_setpoint=60; 
	  if(abs(w_error1) >= 1)
		M_setpoint=45; 	
    if(abs(w_error1) >= 2)
		M_setpoint=40; 	
	  if(abs(w_error1) >= 3)
	  M_setpoint=35; 
	  if(abs(w_error1) >= 10)
	  M_setpoint=30; 
//	  if(abs(w_error1) >= 15)
//  	M_setpoint=20 ;
//		if(abs(w_error1) >= 20)
//	  M_setpoint=10; 		
	/////////////////////////////	
	  if(DLbiaozhi == 1  )
	  M_setpoint=15; 	 
//	  if(DLbiaozhi == 1 && abs(dianci_out) >600 )
//	  M_setpoint=7;
//	 if(DLbiaozhi == 1 && abs(dianci_out) >600)
//	 M_setpoint=2; 
	 if(distance<100)
	 M_setpoint=5; 
	 if(ZAbiaozhi!=0  )
	 M_setpoint=10; 
	 if(HDbiaozhi !=0 )
	 M_setpoint=10;
	 if(HDbiaozhi ==3 || HDbiaozhi ==4 )
	 M_setpoint=5;
	 if(yangguang_flag == 1)
	 M_setpoint=7;
   if(L_AD_value>2000||R_AD_value>2000)
	 M_setpoint=3;
	 M_kp =80;
	 M_kd =30;




}
	 M_e2= M_e1;
	 M_e1 =M_e0;
	 M_e0 =M_setpoint - M_nowpoint;

 if(motor_time==5)
 {   
//	 if(Plan == 0 || Plan == 1 || Plan == 2 || Plan == 3 )
	 Motor_PID.pwm=M_kp*M_e0 + M_kd *(M_e0-M_e1)+1200 ;
//	 else
//	 {
//	 if(abs_error>=20)
//   Motor_PID.pwm=500;
//	 if(abs_error<20)
//	 Motor_PID.pwm=800; 
//   }
//		if(M_nowpoint>=25 && M_e0<=-5 && Plan ==1)
//	   Motor_PID.pwm =-1500;
//		if(M_nowpoint>=30 && M_e0<=-15 )
//	   Motor_PID.pwm =-1500;

	 if(Motor_PID.pwm>4000/*&&M_e0<20*/)
		 Motor_PID.pwm =4000;
	 
	 if(Motor_PID.pwm<-3000)
		 Motor_PID.pwm =-3000;
//	 if(M_e0>=20)
//	   Motor_PID.pwm =4000;
//	 if(M_nowpoint>20	&& M_e0<=-20)
//	   Motor_PID.pwm =-3000;	
	 if(Motor_PID.pwm>=0)
	 {
		 ftm_pwm_duty(ftm0,ftm_ch2,Motor_PID.pwm);
	   ftm_pwm_duty(ftm0,ftm_ch3,0);
	 }
	 else
	 {
     ftm_pwm_duty(ftm0,ftm_ch2,0);
	   ftm_pwm_duty(ftm0,ftm_ch3,abs(Motor_PID.pwm));
	 }
	 motor_time=0;
 }
}
int str_flag,turn_flag,turning_flag;
void motor_speedcontrol()
{ 
	int str1=0,turn1=0,str2=0,turn2=0;
	for(x=50;x>40;x--)
{  if(abs(Mline[x]-39) <=1)
	 str1++;
   else
   turn1++;		
}

	for(x=30;x>20;x--)
{	 if(abs(Mline[x]-39) <=2)
	 str2++;
	 else
	 turn2++;
}
 if(str1 > 7   && str2 > 7)
   str_flag=1;
 else
   str_flag=0;
 
 if(turn1 > 7   && turn2 > 5)
	 turn_flag=1;
 else
	 turn_flag=0;
 
 if(turn1 > 7  && turn2 > 7)
   turning_flag=1;
 else
	 turning_flag=0;
 


}
  /************************************线性回归计算中线斜率************************************/


int xielv;
void hgzhixian()
{  int x;
	int sumX=0,sumY=0,avrX=0,avrY=0,endline,startline;
	int num=0,kk_up1=0,kk_up2=0,kk_up,kk_down;
		endline=55;
    startline=30;
	for(x=startline;x<=endline;x++)
	{
		num++;
		sumX+=x;
		sumY+=Mline[x];
	}
	avrX=sumX*10/num;
	avrY=sumY*10/num;
	kk_up=0;
	kk_down=0;
	for(x=startline;x<=endline;x++)
	{
		kk_up1=(int)(Mline[x]-avrY/10);
		kk_up2=x-avrX/10;
		kk_up+=(int)(10*(kk_up1*kk_up2));
		kk_down+=(int)(10*((x-avrX/10)*(x-avrX/10)));
	}
	if(kk_down==0) 
		xielv=0;
	else 
		xielv=kk_up*16/kk_down;
  if(xielv>20)
		xielv=20;
	if(xielv<-20)
		xielv=-20;
}
int CarSpeed[3],SPEED_FIFO[1][10];
void SPEED_Filter(int16 Speed) 
 {  
    uint8 i;
    
    for(i=1;i<10;i++)//婊戝姩鍧囧�兼护娉㈡硶
   {
      SPEED_FIFO[0][i-1] = SPEED_FIFO[0][i];//宸︾紪鐮佸櫒
    }
    SPEED_FIFO[0][9] = Speed;//宸︾紪鐮佸櫒
    
    //Speed_L=Speed_R =0;
    
    SPEED_FIFO[0][9] = 0.33*SPEED_FIFO[0][9]+0.33*SPEED_FIFO[0][8]+0.33*SPEED_FIFO[0][7];
  
    CarSpeed[0] = CarSpeed[1];
    CarSpeed[1] = CarSpeed[2];
    CarSpeed[2] = ( SPEED_FIFO[0][0]+
                    SPEED_FIFO[0][1]+
                    SPEED_FIFO[0][2]+
                    SPEED_FIFO[0][3]+
                    SPEED_FIFO[0][4]+
                    SPEED_FIFO[0][5]+
                    SPEED_FIFO[0][6]+
                    SPEED_FIFO[0][7]+
                    SPEED_FIFO[0][8]+
                    SPEED_FIFO[0][9] )/100;
    
    CarSpeed[2] = 0.85*CarSpeed[2]+0.1*CarSpeed[1]+0.05*CarSpeed[0];
    
    
   
 }

/////////////////////////求根/////////////////////
//unsigned int sqrt(unsigned int x)
//{
//UCHAR ans=0,p=0x80;
//while(p!=0)
//{
//ans+=p;
//if(ans*ans>x)
//ans-=p;
//p=(UCHAR)(p/2);
//}
//return(ans);
//}
////////////////////////计算曲率////////////////
//void qulv()
//{
//int x1,x2,x3,y1,y2,y3;
//unsigned int length1,length2,length3;
//int S,K,Kr,Center_Average;
//y1=5;
//y2=10;
//y3=15;
//x1=Mline[2];
//x2=Mline[1];
//x3=Mline[0];
//S=abs((y2-y1)*(x3-x1)-(y3-y1)*(x2-x1));
//length1=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
//length2=sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1));
//length3=sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
//if(S<1)
//S=1;
//K=abs(S/(length1*length2*length3));
//Kr=abs((length1*length2*length3)/S);//曲率的倒数，即曲率半径
////Center_Average=mid(Center[0],Center[1],Center[2]);
//}



//void hgzhixian()
//{
// int FinalLine,BasedLine,MiddleLine,m,AvaliableLines,SumX,SumY,SumUp,SumDown,AverageX,AverageY;
// BasedLine=55;
// FinalLine=20;
// 
// AvaliableLines=FinalLine-BasedLine; // FinalLine 为终止行//BasedLine 为基准行
// MiddleLine=(BasedLine+FinalLine)/2; 
// SumX=0;
// SumY=0;

// for(m=BasedLine;m>FinalLine;m--) 
// {
// SumX+=m;
// SumY+=Mline[m];
// }
// AverageX=10*SumX/AvaliableLines;
// AverageY=10*SumY/AvaliableLines;
// SumUp=0;
// SumDown=0;
// for(m=BasedLine;m>FinalLine;m--) 
// {
// SumUp+=(Mline[m]-AverageY/10)*(m-AverageX/10);
// SumDown+=(m-AverageX/10)*(m-AverageX/10);
// } 
// if(SumDown==0) xielv=0;
// else xielv=SumUp/SumDown;
//// piancha=(SumY-xielv*SumX)/AvaliableLines;

// 
//}
