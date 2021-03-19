#include "usart.h"

void UsartInit()
{
	SCON=0X50;			//设置为工作方式1
	TMOD=0X20;			//设置计数器工作方式2
	PCON=0X80;			//波特率加倍
	TH1=0XF4;				//计数器初始值设置，注意波特率是4800的
	TL1=0XF4;
	ES=1;						//打开接收中断
	EA=1;						//打开总中断
	TR1=1;					//打开计数器
}

void usart() interrupt 4
{
  static unsigned char receivedata;
	receivedata=SBUF;
	RI = 0;           //清除接收中断标志位
	SBUF=receivedata; //将接收到的数据放入到发送寄存器
	while(!TI);			  //等待发送数据完成
	TI=0;						  //清除发送完成标志位
}