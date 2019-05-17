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
extern u8 ov_sta;	//��exit.c���涨��
extern u8 ov_frame;	//��timer.c���涨��

void Init_all()
{
	delay_init();	    	 //��ʱ������ʼ��	  
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear()  	; 
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200

	OV7725_Init();
	delay_ms(1500);	
	OV7670_CS=0;
	OV7725_Window_Set(240,240,0);//QVGAģʽ���								  
	EXTI8_Init();						//ʹ���ⲿ�ж�8,����֡�ж�			
	OLED_Clear();
	TIM3_PWM_Init(45000,32);
}