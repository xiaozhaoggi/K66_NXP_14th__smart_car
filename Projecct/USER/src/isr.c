/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2016,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		isr.c
 * @brief      		中断函数库
 * @company	   		成都逐飞科技有限公司
 * @author     		Go For It(1325536866)
 * @version    		v1.0
 * @Software 		IAR 7.7 or MDK 5.17
 * @Target core		MK60DN512VLL10
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2016-02-25
 ********************************************************************************************************************/



#include "isr.h"
#include "findline.h"
#include "pid.h"
#include "key.h"


//-------------------------------------------------------------------------------------------------------------------
//  @brief      PROTA中断执行函数
//  @return     void   
//  @since      v1.0
//  Sample usage:               当A口启用中断功能且发生中断的时候会自动执行该函数
//-------------------------------------------------------------------------------------------------------------------
//void PORTA_IRQHandler(void)
//{
//    //清除中断标志第一种方法直接操作寄存器，每一位对应一个引脚
//	PORTA->ISFR = 0xffffffff;
//	//使用我们编写的宏定义清除发生中断的引脚
//	//PORTA_FLAG_CLR(A1);

//}


void PORTC_IRQHandler(void)
{
   ov7725_vsync();       //////摄像头场中断
}


void DMA0_IRQHandler(void)
{
   ov7725_dma();         ////摄像头采集中断

}

void PIT0_IRQHandler(void)
{  
//      	if(ov7725_finish_flag == 1)
//		{
	 		 Image_Decompression(image_bin,image_dec[0]);    //解压图像	 
  		 jizhunhang();
	     findline();    	
	  //   hgzhixian();
	     jiaquan_error1();                                      	
      // jiaquan_error2();	
       dianci();
   //    yangguang();	
       SE_control();
		 //  heixian();
       PIT_FlAG_CLR(pit0);    
//		 }
		    
   

}

void PIT1_IRQHandler(void)
{ 
    gpio_set(TRIG_PIN,1);                           //触发引脚输出高电平
    systick_delay(1000);                            //延时10us    延时时间 = 1000*(1/(100*1000*1000))*1000*1000  US  第一个1000就是延时函数里面的参数  延时时间并未考虑函数调用时间
    gpio_set(TRIG_PIN,0);
    PIT_FlAG_CLR(pit1);
}

extern uint8 motor_flag;
extern int stop_flag ;
void PIT3_IRQHandler(void)
{   int i;
    int16 M_nowpoint_tt=ftm_quad_get(ftm1); 
	  ftm_quad_clean(ftm1);
	  SPEED_Filter(M_nowpoint_tt);
	  if(stop_flag == 1)
			Check_stop();  // 过横断后开始寻找停止线		
    if(stop_flag == 0 || stop_flag == 1)
	{		
		switch(motor_flag)
		{ 
					case 1:    Motor_control();  break;                             	                             					
				  case 2:  	 //M_setpoint=0 ;    break;                                 												
		}
 	}
    PIT_FlAG_CLR(pit3);
}

long wait_time = 0;                 //超时检测变量
uint32 distance_time = 0;           //测距的时间变量
uint32 distance = 0;                //转换出来的距离  单位为厘米
uint32 distance_tt = 0;                //转换出来的距离  单位为厘米
uint32 distance_t = 0;  
void PORTA_IRQHandler(void)
{

//	PORTC_FLAG_CLR(C1);
        static uint16 D[5]={0};
       uint32 distance_time = 0;           //测距的时间变量
       if(gpio_get(ECHO_PIN))
       {
           pit_time_start(pit2);//打开计时器
           distance_time=0;
       }
       if(!gpio_get(ECHO_PIN))
       {
           distance_time = pit_time_get(pit2);
				   distance = distance_time*34/2/(bus_clk_mhz*1000);           //计算距离cm
//           distance_t = distance_time*34/2/(bus_clk_mhz*1000);           //计算距离cm
				 
       }
//			   distance_tt=distance; 
//			  if(distance_tt - distance_t< 70)
//			   distance=distance_t;  
//        else
//				 distance=distance_tt;           //防误判

			
			 if(distance>200)
				 distance=200;
			     //清除中断标志第一种方法直接操作寄存器，每一位对应一个引脚
	PORTA->ISFR = 0xffffffff;
	//使用我们编写的宏定义清除发生中断的引脚
 }


//-------------------------------------------------------------------------------------------------------------------
//  @brief      UART3中断执行函数
//  @return     void   
//  @since      v1.0
//  Sample usage:               当UART3启用中断功能且发生中断的时候会自动执行该函数
//-------------------------------------------------------------------------------------------------------------------
void UART3_RX_TX_IRQHandler(void)
{
    if(UART3->S1 & UART_S1_RDRF_MASK)                                     //接收数据寄存器满
    {
        //用户需要处理接收数据
        mt9v032_cof_uart_interrupt();
    }
    if(UART3->S1 & UART_S1_TDRE_MASK )                                    //发送数据寄存器空
    {
        //用户需要处理发送数据

    }
}

 void pit0_init()
 {
  pit_init_ms(pit0,30)								//
	set_irq_priority(PIT0_IRQn,1);						//设置优先级,根据自己的需求设置
	enable_irq(PIT0_IRQn);								//打开pit0的中断开关
 }

  void pit1_init()
 {
  pit_init_ms(pit1,100)								//
	set_irq_priority(PIT1_IRQn,3);						//设置优先级,根据自己的需求设置	                   
  enable_irq(PIT1_IRQn);    //打开pit1的中断开关
 }
   void pit3_init()

	 {
  pit_init_ms(pit3,10)								//
	set_irq_priority(PIT3_IRQn,2);						//设置优先级,根据自己的需求设置	                   
  enable_irq(PIT3_IRQn);    //打开pit3的中断开关
 }
 
 void PORTA_init()
 {
   
    set_irq_priority(PORTA_IRQn,0);						//设置优先级
    enable_irq(PORTA_IRQn);  
 
 
 }


/*
中断函数名称，用于设置对应功能的中断函数
Sample usage:当前启用了DMA0中断，然后就到下面去找哪个是DMA0的中断函数名称，找到后写一个该名称的函数即可
void DMA0_IRQHandler(void)
{
    ;
}
记得进入中断后清除标志位


DMA0_IRQHandler  
DMA1_IRQHandler  
DMA2_IRQHandler  
DMA3_IRQHandler  
DMA4_IRQHandler  
DMA5_IRQHandler  
DMA6_IRQHandler  
DMA7_IRQHandler  
DMA8_IRQHandler  
DMA9_IRQHandler  
DMA10_IRQHandler 
DMA11_IRQHandler 
DMA12_IRQHandler 
DMA13_IRQHandler 
DMA14_IRQHandler 
DMA15_IRQHandler 
DMA_Error_IRQHandler      
MCM_IRQHandler            
FTFL_IRQHandler           
Read_Collision_IRQHandler 
LVD_LVW_IRQHandler        
LLW_IRQHandler            
Watchdog_IRQHandler       
RNG_IRQHandler            
I2C0_IRQHandler           
I2C1_IRQHandler           
SPI0_IRQHandler           
SPI1_IRQHandler           
SPI2_IRQHandler           
CAN0_ORed_Message_buffer_IRQHandler    
CAN0_Bus_Off_IRQHandler                
CAN0_Error_IRQHandler                  
CAN0_Tx_Warning_IRQHandler             
CAN0_Rx_Warning_IRQHandler             
CAN0_Wake_Up_IRQHandler                
I2S0_Tx_IRQHandler                     
I2S0_Rx_IRQHandler                     
CAN1_ORed_Message_buffer_IRQHandler    
CAN1_Bus_Off_IRQHandler                
CAN1_Error_IRQHandler                  
CAN1_Tx_Warning_IRQHandler             
CAN1_Rx_Warning_IRQHandler             
CAN1_Wake_Up_IRQHandler                
Reserved59_IRQHandler                  
UART0_LON_IRQHandler                   
UART0_RX_TX_IRQHandler                 
UART0_ERR_IRQHandler                   
UART1_RX_TX_IRQHandler                 
UART1_ERR_IRQHandler  
UART2_RX_TX_IRQHandler
UART2_ERR_IRQHandler  
UART3_RX_TX_IRQHandler
UART3_ERR_IRQHandler  
UART4_RX_TX_IRQHandler
UART4_ERR_IRQHandler  
UART5_RX_TX_IRQHandler
UART5_ERR_IRQHandler  
ADC0_IRQHandler
ADC1_IRQHandler
CMP0_IRQHandler
CMP1_IRQHandler
CMP2_IRQHandler
FTM0_IRQHandler
FTM1_IRQHandler
FTM2_IRQHandler
CMT_IRQHandler 
RTC_IRQHandler 
RTC_Seconds_IRQHandler  
PIT0_IRQHandler  
PIT1_IRQHandler  
PIT2_IRQHandler  
PIT3_IRQHandler  
PDB0_IRQHandler  
USB0_IRQHandler  
USBDCD_IRQHandler
ENET_1588_Timer_IRQHandler
ENET_Transmit_IRQHandler  
ENET_Receive_IRQHandler
ENET_Error_IRQHandler  
Reserved95_IRQHandler  
SDHC_IRQHandler
DAC0_IRQHandler
DAC1_IRQHandler
TSI0_IRQHandler
MCG_IRQHandler 
LPTimer_IRQHandler 
Reserved102_IRQHandler 
PORTA_IRQHandler 
PORTB_IRQHandler 
PORTC_IRQHandler 
PORTD_IRQHandler 
PORTE_IRQHandler 
Reserved108_IRQHandler
Reserved109_IRQHandler
SWI_IRQHandler 
*/
                


