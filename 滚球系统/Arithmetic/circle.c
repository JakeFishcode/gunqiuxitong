#include <math.h>
#include <stdlib.h>
#include <circle.h>
#include "ov7725.h"
#include "GlobalDefine.h"
#define WIDTH 240
#define HEIGHT 240
extern unsigned char data[WIDTH][HEIGHT];
uchar Threshold = 150;
Yuan ZuoBiao[9];
Yuan Buff[3]={{117.5,39,6},{116.5,118,6},{116,197,6}};
Xian_Duan hang[HEIGHT][MAXLINE]; 
void gaussianFilter(u8 data[][WIDTH])
{
	int i,j,index,sum,m,n;
	int templates[9] = {1,2,1,  //�˲�ģ��
	                    2,4,2,
											1,2,1};
						
	 for(i = 1;i<HEIGHT-1;i++)	  
	{
		for(j = 1;j<WIDTH -1;j++) 
		{
			index = sum = 0;
			for( m= -1;m <= 1;m++)
			 {
			 	for(n = -1;n<=1;n++)
			 	  sum += *(*(data+i +m)+j+n) * templates[index++];
			 }
		  *(*(data+i)+j) = sum >> 4;
		}
	}
 } 

/*image:�����ֵͼ��
%h v  :�ֺõ��У��У����߶�
 

*/
void Geth(Xian_Duan h[][MAXLINE], uchar image[][WIDTH])
{
	int length = 0,i,j;  
	uchar num = 0,flag = 0;   
  memset(hang,0,HEIGHT*MAXLINE*sizeof(Xian_Duan)); //��ʼ��0
	 
	for(i=0;i<HEIGHT;i++) 
	{
	  for(j=0;j<WIDTH;j++) 
	  {
			if(image[i][j]  < Threshold)
			{
				if (flag == 1)
				{
					flag = 0;
					h[i][num-1].rh = length;    			 
				}
			}
			else if (flag == 0)
			{
				h[i][num].x = j;  
				h[i][num].y = i;   //��ʼ����   		  
				flag = 1;   
				num++;              //���߶�
				length = 0;
			}			
			if(flag==1)
				length++;
			if(j==WIDTH-1 && image[i][j] <= Threshold)		    
							h[i][num-1].rh  = length;  
	  }
          num = 0;
          flag = 0;
	}
}
//Ѱ���м��߶������ھ�
/*
���� neig: ����ھӵĽṹ��
       h : ���߶�����
	i,j : 
	j???? 0~2 
	cor ??????????   
	flag:?????????? 
???  ????? 
*/
int findUDneig(Xian_Duan *neig,Xian_Duan h[][MAXLINE],int i,int j,uchar *cor)
{
	int k = 0;
	int count = 0;
	int num=0;
     if( i < HEIGHT-1)      
	  { 
	  	if(h[i][j].rh > 0)
	  	 {
	  	 	for(k=0;k<MAXLINE;k++)
			{
					if(h[i][k].flag==0)
					{
						num++;
					}
			 	if(h[i+1][k].flag==0 && h[i+1][k].rh > 0 && h[i+1][k].x <= h[i][j].x + h[i][j].rh && h[i][j].x <= h[i+1][k].x + h[i+1][k].rh)
		        {
				  *neig  = h[i+1][k];
				   *cor = k;   
				   count = count + 1;
		    	}
			}   
		 }
	  }
	  return count;
}
/*******************???????****************
��ȡ���Բ����Ϣ
***********************************************/ 
int Get_Many_Yuan_Message(Yuan *message,uchar image[][WIDTH])
{
	Xian_Duan neig,max_neig={0,0,0};    //??? 
	uchar cor=0;           //???????????? 
	uchar hb=0;	   //?????????? ????? 1,???0 
	int i,j,index=-1;   //index ?????? ,??-1,????+1???????? 
	int subi,subj; 
        
	Geth(hang,image);  //??????
	 
	 for(i=0;i<HEIGHT;i++)
	{
	   for(j=0;j<MAXLINE;j++)
	   {
	   	 if(hang[i][j].rh>0 && hang[i][j].flag == 0) //????? ???????
                {
                    if(hb==0)  //??????? 
                    {
                      hb = 1;
                      index++;//?????1                     
                    }
                    subj = j; 
                    subi = i;            
		    hang[subi][subj].flag = 1;  //??          
                    while( findUDneig(&neig,hang,subi,subj,&cor) ) //????? ,?????? 
                    {			    
                          if(neig.rh > max_neig.rh)					  
                               max_neig = neig;
                                                                     
                          hang[subi][subj].flag = 1;  //??                         
                          subi++;subj = cor;//????
                     }
                        hang[subi][subj].flag = 1;  //??                                           
                        if(max_neig.rh *0.5 > MIN_R && fabs(max_neig.rh - (subi-i)) < 20)  //??????
                        {                                  
                            (message+index)->x = 10;//max_neig.x;// + max_neig.rh *0.5;
                            (message+index)->y = 11;//max_neig.y;
                            (message+index)->r = 12;max_neig.rh *0.5;
                        }
			else        //???????,?? 
                          index--;			    
		    } 
		    hb = 0;
		    max_neig.rh = 0;
	   }
	}	  	
	  return index+1;	  
}

/*******************???????****************
��ȡ����Բ
***********************************************/ 
float last_x,last_y;
void Get_One_Yuan_Message(Yuan *message,uchar image[][WIDTH])
{
	Xian_Duan neig,max_neig={0,0,0};    //��ʼ��
	uchar cor=0;           //???????????? 
	int i,j; 
	int subi,subj;  
        //static float last_x,last_y;
	(message)->x=0;
	Geth(hang,image);  //��ֵ��	���߶�
	
	for(i=0;i<HEIGHT;i++)
	{
	   for(j=0;j<MAXLINE;j++)
	   {
               if(hang[i][j].rh>0 && hang[i][j].flag == 0) //????? ???????
              {
                  subj = j; 
                  subi = i;
                   hang[subi][subj].flag = 1;  //?? 
                  while( findUDneig(&neig,hang,subi,subj,&cor) ) //????? ,?????? 
                  {
//															((message)->x);										
                              if(neig.rh > max_neig.rh)					  
															{       max_neig = neig;
																			
															}
                               hang[subi][subj].flag = 1;  //?? 
                               
                              subi++;subj = cor;//????KP_y
                   }	
//								((message)->x)=findUDneig(&neig,hang,subi,subj,&cor);
                    hang[subi][subj].flag = 1;  //?? 
                    if(max_neig.rh *0.5 > MIN_R && fabs(max_neig.rh - (subi-i)) < 25)//???????,????? 
                    {
                      
                        (message)->x = max_neig.x + max_neig.rh *0.5;//-Buff[1].x;
                        (message)->y = max_neig.y;//-Buff[1].y;
                        (message)->r = max_neig.rh *0.5;
                        /* if(fabs((message)->x)>110 ||fabs((message)->x - last_x)>50)
                          (message)->x=last_x;
                        if(fabs((message)->y)>110||fabs((message)->y - last_y)>50)
                          (message)->y=last_y;
                        last_x=(message)->x;
                        last_y=(message)->y;*/
                        return;
                    }
               }  		   
	   }
	}       
//      (message)->x =0;
//      (message)->y = 0;
//      (message)->r =0;
}

/*********************************************************
���Բxy����
**********************************************************/ 
void Get_init_cor()
{
  float Xinju;
  int k;
   k = Get_Many_Yuan_Message(Buff,data);
   
   if(k==3)
   {
      Xinju = (Buff[2].y - Buff[0].y) * 0.5;  //????

      ZuoBiao[0].x =ZuoBiao[3].x =ZuoBiao[6].x= Buff[0].x-Buff[1].x - Xinju;
      ZuoBiao[1].x =ZuoBiao[4].x =ZuoBiao[7].x= Buff[0].x-Buff[1].x;
      ZuoBiao[2].x =ZuoBiao[5].x =ZuoBiao[8].x= Buff[0].x-Buff[1].x + Xinju;
      ZuoBiao[0].y =ZuoBiao[1].y =ZuoBiao[2].y= Buff[0].y-Buff[1].y;
      ZuoBiao[3].y =ZuoBiao[4].y =ZuoBiao[5].y= Buff[1].y-Buff[1].y;
      ZuoBiao[6].y =ZuoBiao[7].y =ZuoBiao[8].y= Buff[2].y-Buff[1].y;  
   }    
}