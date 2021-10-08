#include "findline.h"
#include "MK60_flash.h"
#include "pid.h"
#include "stdlib.h"
#include "dianci.h"

///////////////////确定基准行//////////
int jzh=59,sumMline;
int avrMline;
int zhongxin=39;
int stop_flag = 0;
extern int Plan;
void jizhunhang()
{ 	int a=0;
 zhongxin=avrMline;

	for(x=59;x>56;x--)
{		for(y=zhongxin;y>0;y--)
   {  		 
		if(image_dec[x][y+1]==255&&image_dec[x][y]==0&&y!=Mline[x])
    {
			Lline[x]=y;
		 L_lost_flag[x]=0;
			break;	
		}			
		 else 
		 {	Lline[x]=0;
			  L_lost_flag[x]=1;
		 }
		  
			
   }
	    for(y=zhongxin;y<79;y++)
   {  		 
		if(image_dec[x][y-1]==255&&image_dec[x][y]==0&&y!=Mline[x])
    {
			Rline[x]=y;
	    R_lost_flag[x]=0;
			break;	
		}	
     else
     { Rline[x]=79;	 
			 R_lost_flag[x]=1;
		 }
		
   }
 

 
		   Mline[x]=(Rline[x]+Lline[x])/2;
       sumMline+=Mline[x];
		   a=a+1;
		 
	}
     if(x==56)
		{
     avrMline=sumMline/a;	   
		 a=0;
	   sumMline=0;
	   Mline[57]=avrMline;
		}
						 
}
 
uint8 quanzhi1[30]={
  1,1,1,1,1,//45
	5,5,5,5,5,//40
	10,10,10,20,20,//35
  30,30,40,40,50,//30
  30,20,20,10,5,//25
	5,5,5,5,5,//20
                   };
int Mline_sum1,quanzhi_sum1,avr_Mline1;
int Mline_sum2,quanzhi_sum2,avr_Mline2;
int w_error1,w_error2;
int quan1_x,x1;								 
void jiaquan_error1()
{  

	for(x1=50;x1>yxh;x1--)
 {
		
	Mline_sum1+=(Mline[x1]-39)*quanzhi1[quan1_x];
	quanzhi_sum1+=quanzhi1[quan1_x];
	 quan1_x++;
 }

		
  if(x1==yxh)
	{
	 avr_Mline1=Mline_sum1/quanzhi_sum1;
	 w_error1=avr_Mline1;
	 Mline_sum1=0;
	 quanzhi_sum1=0;
	 quan1_x=0;
	}
	
  
}
uint8 quanzhi2[30]=
{
  0,0,0,0,0,//50
	1,1,1,1,1,//45
	5,5,5,5,5,//40
  20,20,20,20,20,//35
  20,20,30,40,40,//30
	50,50,50,30,10,//25
 };
int quan2_x=0,x2;
void jiaquan_error2(void)
{ 
  for(x2=55;x2>59-yxh;x2--)
	{
		
	Mline_sum2+=(Mline[x2]-39)*quanzhi2[quan2_x];
	quanzhi_sum2+=quanzhi2[quan2_x];
	quan2_x++;
	  
	}

  if(x2==59-yxh)
	{	
	 avr_Mline2=Mline_sum2/quanzhi_sum2;
	 w_error2=avr_Mline2;
	 quan2_x=0;
	 Mline_sum2=0;
	 quanzhi_sum2=0;
	}
	
  
  

}

int x,y;
int Lline[60],Mline[60],Rline[60];
int L_lost_flag[60],R_lost_flag[60],yxh_flag,yxh;
void findline()
{ yxh_flag=0;

	for(x=56;x>20;x--)
  { if(x>20&&(image_dec[x][Mline[x]-2]==255||image_dec[x][Mline[x]+2]==255||Mline[x]<3||Mline[x]>77))
    yxh_flag=x;       /// 有效行判断  
		   for(y=Mline[x+1];y>0;y--)
   {  		 
		if(image_dec[x][y]==0&&image_dec[x][y+1]==255&&y!=Mline[x])
    {
			Lline[x]=y;
			L_lost_flag[x]=0;
			break;	
		}			
		 else 
		 {	
			Lline[x]=0;
			L_lost_flag[x]=1;
		 }
   }

		    for(y=Mline[x+1];y<79;y++)
   {  		 
		if(image_dec[x][y]==0&&image_dec[x][y-1]==255&&y!=Mline[x])
    {
			Rline[x]=y;
			R_lost_flag[x]=0;
			break;	
		}	
     else
		 {
      Rline[x]=79;	
      R_lost_flag[x]=1;			 
      }
		}
	 
	  Mline[x]=(Lline[x]+Rline[x])/2;
		
  
		
    if(abs(Mline[x]-Mline[x+1])>3&&abs(Mline[x+1]-Mline[x+2])>3)
    Mline[x]=(Mline[x]+Mline[x+1])/2;	///中线防干扰
		
    if(L_lost_flag[x]==1&&R_lost_flag[x]==1)
    Mline[x]=Mline[x+1];
		
   	if(yxh_flag>30)
	  yxh=30;    		
	  else 
		yxh=yxh_flag;      ////有效行限制


	}
  				for(x=57;x>59-yxh;x--)
		{  


			Mline[x] = Mline[x+1]*0.3 + Mline[x]*0.7;
		}
				for(x=59-yxh;x<yxh;x++)
		{  
			Mline[x] = Mline[x-1]*0.3 + Mline[x]*0.7;
		}
    for(x=57;x>20;x--)
		 {
			image_dec[x][Mline[x]]=0;

			}

 
}
	

////////////////////障碍物+断路////////////
int ZAbiaozhi=0;
int DLbiaozhi=0;
void zhangai_duanlu()
{ 
	int z=0,m=0,i,a=0,b=0,c=0,hui=0;
	if(ZAbiaozhi==0 && HDbiaozhi==0 && DLbiaozhi==0)
	{		

	for(i=79;i>0;i--)
	{
		if(image_dec[35][i]==0)
		a++;
		
	}
	

	for(i=49;i>29;i--)
	{
		if(image_dec[15][i]==0)
		b++;
		
	}
	                ///////////////        
	
					 				
	
}
	

	//////////////////////////障碍////////////////////////////////////
//if(distance<=85) 
//if(b==4 && image_dec[15][31]==0 && image_dec[12][38]==0 && image_dec[15][45]==0 && DLbiaozhi==0)	
   
               	             ////////////////////        防止弯道误判
//			
//			if(image_dec[50][25]==255)
//	   	m=m+1;
//    	if(image_dec[50][55]==255)
//	   	m=m+1; 
//    	if(image_dec[30][0]==0)
//	   	m=m+1;
//			if(image_dec[35][0]==0)
//	   	m=m+1;
//    	if(image_dec[30][79]==0)
//	   	m=m+1;
//    	if(image_dec[35][79]==0)
//	   	m=m+1;            			
//               	             ////////////////////        防止弯道误判

      if(distance<80)             //超声波区分		 
	 { 	for(i=57;i>20;i--)
		  {
				if(Mline[i]>32&&Mline[i]<46)
				c++;
			}
		 if( /* m==6 &&*/a<40 && b>15 &&c>27 &&/*&&/* && m==12/* && abs(w_error1<5) &&*/ ZAbiaozhi==0 && DLbiaozhi==0 && HDbiaozhi==0)
		 { 
  
			SE_PID.pwm=3400;
			gpio_set(A6,1);
      ZAbiaozhi=1;		        /////////			 
		 } 


	 }
      
	//////////////////////////////////////////


if(ZAbiaozhi==1)
	 {
    if(image_dec[59][79]==0)		 
		for(i=0;i<79;i++)
		
	  {
			if(image_dec[59][i]==0)
       z++;	
		}
   }	                       ////////////////////////

	   if(z>75&&ZAbiaozhi==1)
   {
			gpio_set(A6,0);
			SE_PID.pwm=4700;
			ZAbiaozhi=2;
			
			 
	 }
if(ZAbiaozhi==2)
		 for(i=79;i>50;i--)
		{ 
		 if(image_dec[59][i]==255)
			 hui++;
			
		}
			
		 
		 
if(a>50 /*&& distance>120 */&& ZAbiaozhi==0 )
	DLbiaozhi=1;
      
		 if(hui>=25 && ZAbiaozhi==2 /*&& (Plan == 0 ||Plan == 1)*/) 
		 {
			ZAbiaozhi=0;                   //障碍终止回归巡线
			stop_flag=1;                   //开始寻找停车线标志位 
		 }
//		 if(hui>=25 && ZAbiaozhi==2 && (Plan == 2 ||Plan == 3)) 
//		 {
//			 ZAbiaozhi=3;
//       stop_flag=1;                   //开始寻找停车线标志位 			 
//		 }
//     if(ZAbiaozhi== 3 && L_AD_value > 800 && M_AD_value > 800 && R_AD_value > 800)		
//      ZAbiaozhi=0;		 
		 if(image_dec[59][10]==255 && image_dec[59][65]==255 &&image_dec[59][30]==255 && image_dec[59][45]==255 && image_dec[59][69]==255 && DLbiaozhi==1)
      DLbiaozhi=0;                  //断路终止回归巡线
  


}
void heixian()
{
   for(x=1;x<59;x+=10)
   {
		 for(y=2;y<75;y++)
		 image_dec[x][y]=0;
		 
	 
	 
	 
	 
	 }

}
////////////////环岛////////////////////////
int HDbiaozhi=0;
void huandao()
{
//	 /////////////左大环岛//////////////////////////////////////////
//	if(HDbiaozhi ==0 && L_AD_value >1000 &&R_AD_value > 2000 && M_AD_value < 1500)
//	HDbiaozhi=1;       // 中心点前	
//	if(HDbiaozhi ==1 && L_AD_value >1450 && R_AD_value > 2200 && M_AD_value > 1850)
//  HDbiaozhi=3;       // 中心点
//	if(HDbiaozhi ==3 && L_AD_value >1850 && R_AD_value < 2200 && M_AD_value < 1850)
//	HDbiaozhi=zuo_huandao;    // 中心点后	 
//	if(HDbiaozhi == zuo_huandao && L_AD_value <1200 && M_AD_value < 800)
//	HDbiaozhi=7;       //环内  
//	if(HDbiaozhi == 7 && L_AD_value > 2000 && M_AD_value >1000)
//	HDbiaozhi=9;	
//	if(HDbiaozhi == 9 && L_AD_value <1000 && R_AD_value < 1000 && M_AD_value <1000)
//	HDbiaozhi=0;  
			 /////////////左环岛//////////////////////////////////////////
//	if(HDbiaozhi ==0 && M_AD_value>1800 && M_AD_value<2200 && (w_error1 <= -3 &&R_AD_value-L_AD_value>400))
//  HDbiaozhi=zuo_huandao;       // 中心点
//	if((HDbiaozhi == zuo_huandao && L_AD_value <1300  && M_AD_value > 800 && M_AD_value < 1100  && R_AD_value<1600 )||( HDbiaozhi == zuo_huandao && M_AD_value<800 && L_AD_value<800 )  /*&& w_error1 <= -10/*&& R_AD_value<1000*/)
//	HDbiaozhi=5;       //环内  
//	if(HDbiaozhi == 5 && L_AD_value > 1800 && M_AD_value > 1700 /*L_AD_value > 1200 && M_AD_value > 1000*/)
//	HDbiaozhi=7;	
//	if(HDbiaozhi == 7 && M_AD_value <1300 && L_AD_value <1300 && R_AD_value <1300)
//	HDbiaozhi=0;  
		 /////////////左小环岛//////////////////////////////////////////
//	if(HDbiaozhi ==0  M_AD_value>1700)
//  HDbiaozhi=zuo_huandao;       // 中心点
////	if(HDbiaozhi ==1 && L_AD_value >1700 && R_AD_value > L_AD_value  && M_AD_value < 1950)
////	HDbiaozhi=zuo_huandao;    // 中心点后	 
//	if(HDbiaozhi == zuo_huandao && L_AD_value <1300 && M_AD_value < 850)
//	HDbiaozhi=5;       //环内  
//	if(HDbiaozhi == 5 && M_AD_value > 1500/*L_AD_value > 1200 && M_AD_value > 1000*/)
//	HDbiaozhi=7;	
//	if(HDbiaozhi == 7 && M_AD_value <900)
//	HDbiaozhi=0;  
	 /////////////右环岛//////////////////////////////////////////

	if(HDbiaozhi ==0 && M_AD_value>2000 && M_AD_value<2500 && w_error1 >= 1 )
  HDbiaozhi=you_huandao;       // 中心点
	if((HDbiaozhi == you_huandao && R_AD_value <1300 && M_AD_value > 800 && M_AD_value < 1100  && L_AD_value<1600 )||(HDbiaozhi == you_huandao && M_AD_value<800 && R_AD_value<800 )/*&&w_error1 >= 10/* && L_AD_value<1000*/)
	HDbiaozhi=6;       //环内  
	if(HDbiaozhi == 6 && R_AD_value > 1800 && M_AD_value > 1700 /*L_AD_value > 1200 && M_AD_value > 1000*/)
	HDbiaozhi=8;	
	if(HDbiaozhi == 8 && M_AD_value <1400 && L_AD_value <1400 && R_AD_value <1400)  ////由于电感值偏大  修改出环标志电感值范围 1300 -> 1400
	HDbiaozhi=0;  
		
	
	
	
	
}
	



int shizi_flag;
int shizi_times=0;
void shizi()
{   int SZ_lost=0;
	 if(shizi_flag==0)
 { 
	 for(x=55;x>20;x--)
	{  
		
    if(image_dec[x][0]==255&&image_dec[x][79]==255)		
		 SZ_lost++;
	}   
 }
 //入十字寻迹标志
    if(HDbiaozhi==0 && SZ_lost>20 && shizi_flag==0)
		{
			shizi_flag=1;
	//		gpio_init(A6,GPO,1);    
		}
		
//十字内		
		if(shizi_flag==1 && abs(error)>=3)
		{
			shizi_flag = 2;		         
   //   gpio_init(A6,GPO,0);			
		}
		
//出十字		
		if(shizi_flag==2)
		{	 for(x=55;x>20;x--)
	{  
		
    if(image_dec[x][0]==255&&image_dec[x][79]==255)		
		 SZ_lost++;
	}  
		}
   if( SZ_lost>20 && shizi_flag == 2)		
		shizi_flag=3;
	 
//完全出十字
	 if(shizi_flag==3)
		{	 for(x=55;x>20;x--)
	{  
		
    if(image_dec[x][0]==255&&image_dec[x][79]==255)		
		 SZ_lost++;
	}  
		}		 
   	  if( SZ_lost<15 && shizi_flag == 3)		
		shizi_flag=0;
	 
		
}
int dianci_sup_flag;
void dianci_sup()
{   int bai=0;
	
   for(x=55;x>20;x--)
	{  
		
    if(image_dec[x][0]==255||image_dec[x][79]==255)		
		 bai++;
	}   
    if(HDbiaozhi==0 && bai>25 )
		{
			dianci_sup_flag=1;
			gpio_init(A6,GPO,1); 	
			
		}
	 else 
	 { 
		 dianci_sup_flag=0;	 
	   gpio_init(A6,GPO,0);
	 }
		
}

int dx_biaozhi;
void lost_control()
{ int lost;
	lost=0;
  for(x=59;x>20;x--)
	{
 if(image_dec[x][0]==0&&image_dec[x][79]==0)
	 lost++;
	}
	if(lost>20)
	 dx_biaozhi=1;
	else
	 dx_biaozhi=0;
	



}

int yangguang_flag=0;
void yangguang()
{  
	int x59=0,x58=0,x57=0;
	
	for(y=0;y<79;y++)
  { 
	 if(image_dec[59][y]==0)
		 x59++;
	 if(image_dec[58][y]==0)
		 x58++;
	 if(image_dec[57][y]==0)
	   x57++;
 }
	if(x59>30 && ( x58-x59>5 ||x57-x59>5 || x57-x58>5)  )
		yangguang_flag=1;
	else
		yangguang_flag=0;
	 
   


}


void Check_stop(void)// 起跑线检测
{
  uint8 temp=0,temp_tu=0;
  for( x=57;x>=52;x--)
  {
    for( y=6;y<73;y++)
    {
      if(image_dec[x][y] !=image_dec[x][y-1])
      {
        temp_tu++;
        y++;
      }  
    }
    if(temp_tu>jump_point)
      temp++;
    temp_tu=0;
  }
  if(temp>=jump_point_row)
  {
    stop_flag=2;
  }
	if(stop_flag == 2)          //////比赛赛道  横断后标志位为1  开始寻找停止线
	{                           ////// 找到后标志位为2   pwm输出为0
		ftm_pwm_duty(ftm0,ftm_ch2,0);
	  ftm_pwm_duty(ftm0,ftm_ch3,500);
	}
	
}


