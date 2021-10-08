/*      
       
         
        
				   14th NXP CUP
				 
			TEAM：       核工程四轮一队   
	    TEAMMATE:    张博钊
			PERFORMANCE: Second prize in North China Competition area   
			
            2018 - 2019  
          by  xiaozhaoggi								
	        
	      	QQ:970089030		
		
    	@Smart Car Laboratory Of HEBEU 		
	    
				 
					                          
*/
#include "headfile.h"
#include "SEEKFREE_7725.h"
#include "SEEKFREE_OLED.h"
#include "motor.h"
#include "findline.h"
#include "MK60_pit.h"
#include "isr.h"
#include "pid.h"
#include "key.h"

int main()
{
	
	get_clk();
	SE_PID_init();
	gpio_init(A6,GPO,0); 
//	uart_init(uart0,9600);
	ftm_quad_init(ftm1);	
	ov7725_init();    
	
	gpio_init(TRIG_PIN, GPO, 0); //初始化IO端口为输出模式且上拉 
	port_init_NoAlt (TRIG_PIN, PULLUP );  //设置端口上拉电阻    
	gpio_init(ECHO_PIN, GPI, 0);//初始化IO端口为输出模式且上拉 
	port_init_NoAlt (ECHO_PIN, PULLUP | IRQ_RISING | IRQ_FALLING);   //设置端口上拉电阻
	PORTA_init();
	
	pit0_init();
  pit1_init();
  pit3_init();	
	OLED_Init();
  motor_init();
	Motor_PID_init();
  SE_init();
	FLASH_Init();
	Flash_Read();	
 	adc_config();
//  NRF_Dev_Init();//NRF无线初始化
//	ftm_pwm_init(ftm2,ftm_ch1,300,4100); 

  key();

    while(1)
	{
 
	     
	
	}
}


