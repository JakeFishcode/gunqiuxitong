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
#include "init.h"


extern u8 ov_sta;	//在exit.c里面定义
extern u8 ov_frame;	//在timer.c里面定义
unsigned char data[240][240];
unsigned int flag,y;//识别标志和y坐标
Yuan message;
u8 oled_data[1024];
void work(unsigned int *p);



int main(void)
{	 					 
	Init_all();
 	while(1)
	{	
		get_xy(&flag,&y);
		if(flag==255)
			work(&y);
	}				    
}










void work(unsigned int *p)
{
	camera_show();
	Get_One_Yuan_Message(&message,data);
	usart1_niming_report(0xA1,0,message.x,message.y,message.r,28);
	delay_ms(10);
	OV7725_camera_refresh();//更新显示
	TIM_SetCompare3(TIM3,20000);//PB0
  TIM_SetCompare4(TIM3,22500);//PB1
}
















