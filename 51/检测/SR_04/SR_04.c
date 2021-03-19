#include "sr_04.h"

unsigned int Distance; //距离

void T0_init()
{
  TMOD=0x01;	 //设T0为方式1，GATE=1；
	TH0=0;
	TL0=0;          
	ET0=1;       //允许T0中断
	EA=1;			   //开启总中断	
}

void  StartModule() 		//启动模块
{
	unsigned char i;
	Trig=1;			          //启动一次模块>10us
	for(i=10;i>0;i--)
	_nop_(); 
	Trig=0;
}

void Conut(void)
{
   static unsigned int time;
	 time=TH0*256+TL0;
	 TH0=0;
	 TL0=0;
	
	 Distance=(time*1.7)/100;     //算出来是CM
}

void start_count()
{
	 StartModule();   //启动模块
	 while(!Echo);		//当ECHO为低时等待
	 TR0=1;			      //开启计数
	 while(Echo);			//当ECH0为高计数并等待
	 TR0=0;				    //关闭计数
	 Conut();			    //计算
}