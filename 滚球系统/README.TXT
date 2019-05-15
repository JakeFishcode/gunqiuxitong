主控:
	主控STM32F103ZE
外设:
	hc-05蓝牙模块，ov7725摄像头模块,OLED(SPI)
接线脚:
ov7725
	OV_D0~D7  -----------   PC0~7
	OV_SCL    ------------  PD3
	OV_SDA    ------------  PG13
	OV_VSYNC  ------------  PA8
	FIFO_RRST -----------   PG14
	FIFO_OE   -----------   PG15
	FIFO_WRST ------------  PD6
	FIFO_WEN  ------------  PB3
	FIFO_RCLK ------------  PB4	
OLED:
	GND    电源地
	VCC  接5V或3.3v电源
	D0   接PD6（SCL）
                D1   接PD7（SDA）
                RES  接PD4
                DC   接PD5
                CS   接PD3  
HC-05:
	TX->PA10
	RX->PA0
	  
实验目的:
	学习2017年国电赛滚球系统
	学院的单片机比赛
硬件资源:
	1,串口1(波特率:115200,PA9/PA10连接在板载USB转串口芯片CH340上面)
	2,OLED接上显示二值化图像
	3,OV7725摄像头监测位置
	4,外部中断8(PA8,用于检测OV7670的帧信号)
	5,TIM3输出PWM给舵机控制平台
实验现象:
	小球会在指定的区域内保持平衡，外界作用的时候也能很快的恢复原状

特别声明：
	本实验在正点原子@ALIENTEK的代码例程上修改 。





































