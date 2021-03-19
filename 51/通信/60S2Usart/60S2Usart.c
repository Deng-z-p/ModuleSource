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
	AUXR |=  0x01;		//UART0 ʹ��BRT
	AUXR |=  0x04;		//BRT set as 1T mode
	BRT = BRT_Reload; //ʹ�ò����ʷ����� �����ʣ�BRT_Reload
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

	AUXR |=  (1 << 3);		            //����2�����ʼӱ�
	S2CON  = (S2CON & 0x3f) | (1<<6);	//����2ģʽ1��8λUART��(2^S2SMOD / 32) * BRT�����
	S2CON |= 1 << 4;		            //����2����

	AUXR |=  1 << 4;	                //baudrate use BRT
	BRT = BRT_Reload;

	IE2 |=  1;			                //������2�ж�
}

/*����1�жϷ�����*/
void UART1_RCV (void) interrupt 4
{
	static unsigned char i=0;
	if(RI)               //�����ܵ�����
	{
	
	}  	
}  


/*����2�жϷ�����*/
void UART2_RCV (void) interrupt 8
{
 
	if(RI2)                     //�����ܵ�����
	{
	} 
}

