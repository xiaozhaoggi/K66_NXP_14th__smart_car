#include "key.h"
#include "findline.h"
#include "SEEKFREE_OLED.h"
#include "pid.h"
#include "dianci.h"
#include "SEEKFREE_OLED.h"

uint8 gRetValue_KEY1,gRetValue_KEY2,gRetValue_KEY3,gRetValue_KEY4,gRetValue_KEY5,gRetValue_KEY6;
uint8 Key_papar=1,Key_hang=1,motor_flag=2;
uint8	b8,b4,b2,b1;
uint8 bb8,bb4,bb2,bb1;
uint8 boma_value;
extern int Plan;
/*定义按键功能    k1 选择画面  k4 移动 
                 k2 加        k5 减
					  	   k3 存flash   k6 电机开关
*/	
void paper1()
{
			          dis_bmp(60,80,image_dec[0],0x7F);
                OLED_Print_Num2(90,1,w_error1);  //        w_error1
                OLED_Print_Num2(90,2,w_error2);  //        w_error2
                OLED_Print_Num2(90,3,distance);  
                OLED_Print_Num2(80,3,xielv);  	  //xielv           distance
                OLED_Print_Num2(90,4,avrMline);	 
				        OLED_Print_Num2(80,4,shizi_flag);	//shizi_flag      avrMline
	              OLED_Print_Num2(80,5,HDbiaozhi); 	
          			OLED_Print_Num2(94,5,SE_PID.pwm); //HDbiaozhi	      SE_PID.pwm
                OLED_Print_Num2(108,6,yxh_flag);
                OLED_Print_Num2(80,6,ZAbiaozhi); 
				        OLED_Print_Num2(94,6,DLbiaozhi); //ZAbiaozhi   DLbiaozhi   yxh_flag


//                OLED_Print_Num2(80,7,L_lost);                 				
//                OLED_Print_Num2(102,7,R_lost);				
                OLED_P6x8Str(86,1,"/");
                OLED_P6x8Str(86,2,"/"); 
//				        OLED_P6x8Str(86,6,"/"); 
                OLED_P6x8Str(108,1,"/"); 	
                OLED_P6x8Str(108,2,"/"); 	
//                OLED_P6x8Str(108,6,"/");

}
void paper2()
{
                  OLED_P6x8Str(16,2,"SE_P");
									OLED_P6x8Str(16,3,"Kp_a");
									OLED_P6x8Str(16,4,"Kp_e");
									OLED_P6x8Str(16,5,"SE_D");
									OLED_P6x8Str(16,6,"Plan");
				          OLED_P6x8Str(16,7,"MOTOR");
				          OLED_Print_Num2(50,2,S_kp);
				          OLED_Print_Num2(50,3,SE_PID.Kp);                         
                  OLED_Print_Num2(50,4,Kp_e);  
				          OLED_Print_Num2(50,5,SE_PID.Kd);
	                OLED_Print_Num2(50,6,Plan);
                  OLED_P6x8Str(0,1,"------------");    
                  OLED_P6x8Str(95,3,"\\");
				          OLED_P6x8Str(95,4,"\\");
				          OLED_P6x8Str(95,5,"\\");
				          OLED_P6x8Str(95,6,"\\");
				          OLED_P6x8Str(95,7,"\\");
				          OLED_P6x8Str(95,1,"\\");
				          OLED_P6x8Str(88,2,"\\");
				          OLED_P6x8Str(83,3,"\\"); 
				          OLED_P6x8Str(102,2,"\\");
				          OLED_P6x8Str(107,3,"\\");


}
void paper3()
{
		              OLED_P6x8Str(16,1,"L_AD_");					
                  OLED_P6x8Str(16,2,"R_AD");	
									OLED_P6x8Str(16,3,"M_AD");	
                  OLED_P6x8Str(16,4,"error");	
									OLED_P6x8Str(16,5,"out");
                	OLED_Print_Num2(50,1,L_AD_value);
                  OLED_Print_Num2(50,2,R_AD_value);
									OLED_Print_Num2(50,3,M_AD_value);
                  OLED_Print_Num2(50,4,error_dc);
                  OLED_Print_Num2(50,5,dianci_out);									
									
	
}
void paper4()
{
                OLED_P6x8Str(16,1,"M_Kp");	
				        OLED_P6x8Str(16,2,"M_Ki");
								OLED_P6x8Str(16,3,"Now");
								OLED_P6x8Str(16,4,"Set");
								OLED_P6x8Str(16,5,"Pwm");
				        OLED_Print_Num2(50,1,M_kp);
								OLED_Print_Num2(50,2,M_kd);
								OLED_Print_Num2(50,3,M_nowpoint);
								OLED_Print_Num2(50,4,M_setpoint);
								OLED_Print_Num2(50,5,Motor_PID.pwm);
	              OLED_Print_Num2(20,6,str_flag);
								OLED_Print_Num2(40,6,turn_flag);
								OLED_Print_Num2(60,6,turning_flag);
                


}
void saveflash()
{
	        FLASH_EraseSector(250);		
          FLASH_EraseSector(249);		
          FLASH_EraseSector(248);
          FLASH_EraseSector(247);		
          FLASH_EraseSector(246);		
          FLASH_EraseSector(245);	
          FLASH_EraseSector(244);		
					FLASH_WriteSector(250, (const uint8*)(&SE_PID.Kp),4, 0);						
					FLASH_WriteSector(249, (const uint8*)(&SE_PID.Kd),4, 0);
					FLASH_WriteSector(248, (const uint8*)(&Motor_PID.pwm),4, 0);
				  FLASH_WriteSector(247, (const uint8*)(&Kp_e),4, 0);
          FLASH_WriteSector(246, (const uint8*)(&Motor_PID.Kp),4, 0);						
					FLASH_WriteSector(245, (const uint8*)(&Motor_PID.Kd),4, 0);
	        FLASH_WriteSector(244, (const uint8*)(&Plan),4, 0);
}
void rowflag()
{
		if(Key_papar==2)
		{ 
				switch(Key_hang)
			{
				case 1 : 
					       OLED_P6x8Str(0,2,"->");break;
				case 2 : 
				         OLED_P6x8Str(0,3,"->");break;
				case 3 : 
				         OLED_P6x8Str(0,4,"->");break;
				case 4 : 
					       OLED_P6x8Str(0,5,"->");break;
				case 5 : 
					       OLED_P6x8Str(0,6,"->");break;
				case 6 : 
					       OLED_P6x8Str(0,7,"->");
				         OLED_Print_Num2(50,7,Motor_PID.pwm);
                 OLED_Print_Num2(65,6,M_nowpoint);            break;
				default: Key_hang=1;         
                 OLED_P6x8Str(0,2,"->");break;
			
			}	
		}
		
				if(Key_papar==4)
		{ 
				switch(Key_hang)
			{
				case 1 : 
					       OLED_P6x8Str(0,1,"->");break;
				case 2 : 
				         OLED_P6x8Str(0,2,"->");break;
//				case 3 : 
//				         OLED_P6x8Str(0,3,"->");break;
//				case 4 : 
//					       OLED_P6x8Str(0,4,"->");break;
//				case 5 : 
//					       OLED_P6x8Str(0,5,"->");break;
				default : Key_hang=1;           
				          OLED_P6x8Str(0,1,"->"); break;
					                  
			
			}	
		}



}


void key(void)
{ 
//	gpio_init(A25,GPO,0); //左
//	gpio_init(A26,GPO,0); //上
//	gpio_init(A27,GPO,0); //中
//	gpio_init(A29,GPO,0); //下
//	gpio_init(A28,GPO,0); //右
	gpio_init(A16,GPO,1);  //1
	gpio_init(A15,GPO,1);  //2
	gpio_init(A17,GPO,1);  //4
	gpio_init(A24,GPO,1);  //8
	port_init (A7, ALT1 | PULLUP );//白

while(1)
 { 
   	boma();
		KEY_Scan();
////////////////////////////////////////////////////////////////////////////////////////		
		if(boma_value==0&&gRetValue_KEY6==KEY6_SINGLE)
		{  
			OLED_Fill(0);
			Key_papar++;	 
		}	
		if(motor_flag==2)  ///电机开启后关闭oled
		{	  switch(Key_papar)
			{ 
				case 1:  paper1();   break;	
				case 2: if(motor_flag==2)paper2();   break;						       				         					                                                                	
				case 3:	if(motor_flag==2)paper3();   break;		                                                            
				case 4: if(motor_flag==2)paper4();   break;                                                             
				case 5:  Key_papar=1 ;      break;					
									
			}
		}
////////////////////////////////////////////////////////////////////////////////////////		
		if(boma_value==8&&gRetValue_KEY6==KEY6_SINGLE&&Key_papar==2)
	{ switch(Key_hang)
			{
				//case 1:SE_PID.Kp--; break;
				case 2:SE_PID.Kp--; break;
				case 3:Kp_e--;  break;
	    	case 4:SE_PID.Kd--;  break;
				case 5:Plan--;break;
			  case 6:Motor_PID.pwm-=100; break;
				
		 	}

		}			
////////////////////////////////////////////////////////////////////////////////////////					
		if(boma_value==8&&gRetValue_KEY6==KEY6_SINGLE&&Key_papar==4)
		{ switch(Key_hang)
			{
				case 1:Motor_PID.Kp--; break;
				case 2:Motor_PID.Kd--; break;			
		 	}						
	
		}
////////////////////////////////////////////////////////////////////////////////////////			
		  if(boma_value==2&&gRetValue_KEY6==KEY6_SINGLE)
		{ 
			  saveflash();		 	      //存flash
		}
////////////////////////////////////////////////////////////////////////////////////////		
    if(boma_value==12&&gRetValue_KEY6==KEY6_SINGLE&&(Key_papar==2||Key_papar==4))
    {  Key_hang++;	
			 OLED_Fill(0);
       rowflag();
		}		
////////////////////////////////////////////////////////////////////////////////////////		
			if(boma_value==4&&gRetValue_KEY6==KEY6_SINGLE&&Key_papar==2)
		{ switch(Key_hang)
			{
  	//	case 1:SE_PID.Kp++; break;
		  	case 2:SE_PID.Kp++; break;
				case 3:Kp_e++;  break;
				case 4:SE_PID.Kd++;  break;
	  		case 5:Plan++;break;
			  case 6:Motor_PID.pwm+=100; break;
		 	}		
			if(Plan>3)
				Plan=0;			
////////////////////////////////////////////////////////////////////////////////////////				
			}
			if(boma_value==4&&gRetValue_KEY6==KEY6_SINGLE&&Key_papar==4)
		{ switch(Key_hang)
			{
  		  case 1:Motor_PID.Kp++; break;
		  	case 2:Motor_PID.Kd++; break;

		 	}
						
		}				
////////////////////////////////////////////////////////////////////////////////////////					
			if(boma_value==1&&gRetValue_KEY6==KEY6_SINGLE)
			{   
					 OLED_Fill(0);
					 motor_flag++;											 //电机开关			
			}
//	    	switch(motor_flag)
//		{ 
//					case 1:    Motor_control();  break;                             	                             					
//				  case 2:  	 //M_setpoint=0 ;    break;                                 												
//		}
//			
	///////////////////////////////////////////////////////////////		
				switch(motor_flag)	
				{
					case 1: 								 
//								 OLED_P6x8Str(64,7,"ON");
	//						 Motor_control();                
	//             ftm_pwm_duty(ftm0,ftm_ch2,Motor_PID.pwm);
	//						 ftm_pwm_duty(ftm0,ftm_ch3,0);                    					
															  									break;
				
					case 2:if(Key_papar==2&&Key_hang!=6)
								 OLED_P6x8Str(60,7,"OFF");
								 ftm_pwm_duty(ftm0,ftm_ch2,0);
								 ftm_pwm_duty(ftm0,ftm_ch3,0);
																									 break;
					
					case 3:motor_flag=1;                     break;
				}						
    
		                 
	}
	}


   


//////////////////////////////////////////flash
				
				
void Flash_Read(void)			
{
  SE_PID.Kp=flash_read(250,0,int);
	SE_PID.Kd=flash_read(249,0,int);
  Motor_PID.pwm=flash_read(248,0,int);
  Kp_e=flash_read(247,0,int);
	Motor_PID.Kp=flash_read(246,0,int);
	Motor_PID.Ki=flash_read(245,0,int);
	Plan=flash_read(244,0,int);
}	
				


//////////////////////////////////////////////////////* 按键扫描程序 */
//void KEY1_Scan(void)
//{
//    static KEY_Status status = kKEY1_Idle;
//    switch(status)
//    {
//        case kKEY1_Idle:
//            gRetValue_KEY1 = NO_KEY1;
//            if((KEY1 == 0) ) /* 如果按键被按下 进入确认与消抖态 */
//            {
//                status = kKEY1_Debounce;
//            }
//            break;
//        case kKEY1_Debounce: /* 确认与消抖态 */
//            if((KEY1 == 0))
//            {
//                status = kKEY1_Confirm;
//            }
//            else
//            {
//                status = kKEY1_Idle;
//                gRetValue_KEY1 = NO_KEY1;
//            }
//            break;
//        case kKEY1_Confirm: /* 确认态 */
//            if(KEY1 == 1) /* 按键松开 */
//            {
//                gRetValue_KEY1 = KEY1_SINGLE;
//                status = kKEY1_Idle;
//            }
//            break;
//        default:
//            break;
//    }
//}


/* 按键扫描程序 */
//void KEY2_Scan(void)
//{
//    static KEY_Status status = kKEY2_Idle;
//    switch(status)
//    {
//        case kKEY2_Idle:
//            gRetValue_KEY2 = NO_KEY2;
//            if((KEY2 == 0) ) /* 如果按键被按下 进入确认与消抖态 */
//            {
//                status = kKEY2_Debounce;
//            }
//            break;
//        case kKEY2_Debounce: /* 确认与消抖态 */
//            if((KEY2 == 0))
//            {
//                status = kKEY2_Confirm;
//            }
//            else
//            {
//                status = kKEY2_Idle;
//                gRetValue_KEY2 = NO_KEY2;
//            }
//            break;
//        case kKEY2_Confirm: /* 确认态 */
//            if(KEY2 == 1) /* 按键松开 */
//            {
//                gRetValue_KEY2 = KEY2_SINGLE;
//                status = kKEY2_Idle;
//            } 
//             
//           			 
//							
//            break;
//        default:
//            break;
//    }
//}



///* 按键扫描程序 */
void KEY3_Scan(void)
{
    static KEY_Status status = kKEY3_Idle;
    switch(status)
    {
        case kKEY3_Idle:
            gRetValue_KEY3 = NO_KEY3;
            if((KEY3 == 0) ) /* 如果按键被按下 进入确认与消抖态 */
            {
                status = kKEY3_Debounce;
            }
            break;
        case kKEY3_Debounce: /* 确认与消抖态 */
            if((KEY3 == 0))
            {
                status = kKEY3_Confirm;
            }
            else
            {
                status = kKEY3_Idle;
                gRetValue_KEY3 = NO_KEY3;
            }
            break;
        case kKEY3_Confirm: /* 确认态 */
            if(KEY3 == 1) /* 按键松开 */
            {
                gRetValue_KEY3 = KEY3_SINGLE;
                status = kKEY3_Idle;
            }
            break;
        default:
            break;
    }
}

/* 按键扫描程序 */
//void KEY4_Scan(void)
//{
//    static KEY_Status status = kKEY4_Idle;
//    switch(status)
//    {
//        case kKEY4_Idle:
//            gRetValue_KEY4 = NO_KEY4;
//            if((KEY4 == 0) ) /* 如果按键被按下 进入确认与消抖态 */
//            {
//                status = kKEY4_Debounce;
//            }
//            break;
//        case kKEY4_Debounce: /* 确认与消抖态 */
//            if((KEY4 == 0))
//            {
//                status = kKEY4_Confirm;
//            }
//            else
//            {
//                status = kKEY4_Idle;
//                gRetValue_KEY4 = NO_KEY4;
//            }
//            break;
//        case kKEY4_Confirm: /* 确认态 */
//            if(KEY4 == 1) /* 按键松开 */
//            {
//                gRetValue_KEY4 = KEY4_SINGLE;
//                status = kKEY4_Idle;
//            }
//            break;
//        default:
//            break;
//    }
//}

///* 按键扫描程序 */
//void KEY5_Scan(void)
//{
//    static KEY_Status status = kKEY5_Idle;
//    switch(status)
//    {
//        case kKEY5_Idle:
//            gRetValue_KEY5 = NO_KEY5;
//            if((KEY5 == 0) ) /* 如果按键被按下 进入确认与消抖态 */
//            {
//                status = kKEY5_Debounce;
//            }
//            break;
//        case kKEY5_Debounce: /* 确认与消抖态 */
//            if((KEY5 == 0))
//            {
//                status = kKEY5_Confirm;
//            }
//            else
//            {
//                status = kKEY5_Idle;
//                gRetValue_KEY5 = NO_KEY5;
//            }
//            break;
//        case kKEY5_Confirm: /* 确认态 */
//            if(KEY5 == 1) /* 按键松开 */
//            {
//                gRetValue_KEY5 = KEY5_SINGLE;
//                status = kKEY5_Idle;
//            }
//            break;
//        default:
//            break;
//    }
//}

///* 按键扫描程序 */
void KEY6_Scan(void)
{
    static KEY_Status status = kKEY6_Idle;
    switch(status)
    {
        case kKEY6_Idle:
            gRetValue_KEY6 = NO_KEY6;
            if((KEY6 == 0) ) /* 如果按键被按下 进入确认与消抖态 */
            {
                status = kKEY6_Debounce;
            }
            break;
        case kKEY6_Debounce: /* 确认与消抖态 */
            if((KEY6 == 0))
            {
                status = kKEY6_Confirm;
            }
            else
            {
                status = kKEY6_Idle;
                gRetValue_KEY6 = NO_KEY6;
            }
            break;
        case kKEY6_Confirm: 
            if(KEY6 == 1)
            {
                gRetValue_KEY6 = KEY6_SINGLE;
                status = kKEY6_Idle;
            }
            break;
        default:
            break;
			}
		}
	




void KEY_Scan(void)
{
//	KEY1_Scan();
//	KEY2_Scan();
//	KEY3_Scan();
//	KEY4_Scan();
//	KEY5_Scan();
	KEY6_Scan();
}

void boma()
{
  b8=gpio_get(A24);//
	b4=gpio_get(A17);
	b2=gpio_get(A15);
	b1=gpio_get(A16);
  if(b8==0) 
	bb8=8;
	else
	bb8=0;
	if(b4==0)
	bb4=4;
	else
	bb4=0;
	if(b2==0)
	bb2=2;
	else
  bb2=0;
	if(b1==0)
	bb1=1;
	else
  bb1=0;
  boma_value=bb8+bb4+bb2+bb1;
}
int cmp(int16 a,int16 b,int16 c)
{ int16 mid;
 if((a<=b&&b<=c)||(a>=b&&b>=c))
	 mid=b;
 if((b<=a&&a<=c)||(b>=a&&a>=c))
	 mid=a;
 if((a<=c&&c<=b)||(a>=c&&c>=b))
   mid=c;
 return mid;
	
}
