#include "capture.h"

unsigned int  CCAP0_tmp,CCAP1_tmp;
float time;

bit		B_Cap0,B_Cap1;


void cature_init()
{
 	CCAPM0 = 0x21;	//CCAP0下降沿捕捉，允许中断		下降沿捕捉: 0x11,  上升沿捕捉: 0x21, 上升下降沿捕捉: 0x31
	CCAPM1 = 0x11;	//CCAP1下降沿捕捉，允许中断		下降沿捕捉: 0x11,  上升沿捕捉: 0x21, 上升下降沿捕捉: 0x31
	CMOD = (PCA_IDLE_DISABLE << 7) | (PCA_SOURCE_SELECT << 1) | PCA_ECF;	//初始化PCA模式寄存器。
	CL = 0;					//清空PCA基本计数器。
	CH = 0;
	CR = 1;					//Start CR
	EA = 1;
}

void PCA_interrupt (void) interrupt 7
{
 static unsigned char i=0,frequency=0;
	if(CCF0 == 1)		 //PCA模块0中断
	{
	  i++;
		CCF0 = 0;		   //清PCA模块0中断标志
		if(i==1)
		{
	    CCAP0H=0;
			CCAP0L=0;
			frequency=0;
			CCAPM0=0x11; //下降沿捕获
		}
	  else if(i>=2)
		{
		 i=0;
	   time =  CCAP0H;	                 //读CCAP0H
		 time =  (CCAP0_tmp << 8) + CCAP0L;//读CCAPOL
		 time =  CCAP0_tmp+frequency*65535;//得到总时间
		 time =  time/1000;
		 CCAPM0 = 0x21;                    //上升沿捕获
		 frequency=0;    
		 B_Cap0=1;
		}
	}
	
	if(CF == 1)	         //PCA溢出中断
	{
		CF = 0;			       //清PCA溢出中断标志
		frequency++;
		if(frequency>=200) 		 frequency=0;
	}
}