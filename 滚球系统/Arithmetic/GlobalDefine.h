#ifndef _GlobalDefine_H
#define _GlobalDefine_H
#define pi 3.141592
#define Pwm_Fre 50 
#define HEIGHT 240
#define WIDTH  240
typedef struct
{
    unsigned char x;               //
    unsigned char y;              //
    unsigned int rh:15;
    unsigned char flag:1;  //
}Xian_Duan;       
typedef struct
{
   	float x;    
   	float y;   
   	float r;   
}Yuan;
typedef struct
{
   float x,y;  
   float Length; 
  
}Rectangle; 
typedef unsigned char uchar;


extern unsigned char camera_data[HEIGHT][WIDTH];
extern Yuan ZuoBiao[9],Buff[3];
extern float SN_OUT,EW_OUT,last_y;
extern float KP_x,KD_x,KI_x,KP_y,KD_y,KI_y;
extern int x_pos,y_pos;
extern uchar Threshold;
extern float Set_X_pos,Set_Y_pos,X_Pos_Fil,Y_Pos_Fil;
extern float x_pos_O,y_pos_O;
extern Yuan Circle,Buff[3];
extern unsigned int K,ABCD[4],Get_cor;
extern int Mode;


extern float testeiX,testeiY;
extern float Set_x,Set_y;


#endif