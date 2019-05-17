#include "GlobalDefine.h"
#include "circle.h"
#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "key.h"     
#include "oled.h"
#include "string.h"		
#include "math.h"	 
#include "bmp.h"
#include "beep.h" 
#include "timer.h" 
#include "exti.h"
#include "ov7725.h"
extern u8 ov_sta;	//在exit.c里面定义
extern u8 ov_frame;	//在timer.c里面定义

void Init_all()
{
	delay_init();	    	 //延时函数初始化	  
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	OLED_Init();			//初始化OLED  
	OLED_Clear()  	; 
	uart_init(115200);	 	//串口初始化为115200

	OV7725_Init();
	delay_ms(1500);	
	OV7670_CS=0;
	OV7725_Window_Set(240,240,0);//QVGA模式输出								  
	EXTI8_Init();						//使能外部中断8,捕获帧中断			
	OLED_Clear();
	TIM3_PWM_Init(45000,32);
}