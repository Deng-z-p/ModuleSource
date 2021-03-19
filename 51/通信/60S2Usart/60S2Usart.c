#include "60s2usart.h"

void uart1_init(void)
{
	PCON |= 0x80;		//UART0 Double Rate Enable
	SCON = 0x50;		//UART0 set as 10bit , UART0 RX enable
/*
	TMOD &= ~(1<<6);		//Timer1 Set as Timer, defalul 12T
	TMOD = (TMOD & ~0x30) | 0x20;	//Timer1 set as 8 bits auto relaod
	AUXR |=  (1<<6);		//Timer1 set as 1T mode
	TH1 = T1_TimerReload;		//Load the timer
	TR1  = 1;
*/
	AUXR |=  0x01;		//UART0 使用BRT
	AUXR |=  0x04;		//BRT set as 1T mode
	BRT = BRT_Reload; //使用波特率发生器 波特率：BRT_Reload
	AUXR |=  0x10;		//start BRT	

	//ES  = 1;
	EA = 1;
}


void usart12_init(void)
{   
	PCON |= 0x80;		            //UART0 Double Rate Enable
	SCON = 0x50;		            //UART0 set as 10bit , UART0 RX enable
	TMOD &= ~(1<<6);		        //Timer1 Set as Timer, 12T
	TMOD = (TMOD & ~0x30) | 0x20;	//Timer1 set as 8 bits auto relaod
	TH1 = T1_TimerReload;		    //Load the timer
	TR1  = 1;
	ES  = 1;
	EA = 1;

	AUXR |=  (1 << 3);		            //串口2波特率加倍
	S2CON  = (S2CON & 0x3f) | (1<<6);	//串口2模式1，8位UART，(2^S2SMOD / 32) * BRT溢出率
	S2CON |= 1 << 4;		            //允许串2接收

	AUXR |=  1 << 4;	                //baudrate use BRT
	BRT = BRT_Reload;

	IE2 |=  1;			                //允许串口2中断
}

/*串口1中断服务函数*/
void UART1_RCV (void) interrupt 4
{
	static unsigned char i=0;
	if(RI)               //若接受到数据
	{
	
	}  	
}  


/*串口2中断服务函数*/
void UART2_RCV (void) interrupt 8
{
 
	if(RI2)                     //若接受到数据
	{
	} 
}

