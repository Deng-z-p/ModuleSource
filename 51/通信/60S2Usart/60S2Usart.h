#ifndef __60S2USART_H
#define __60S2USART_H
#include "stc12c5a60s2.h"
/*************** 用户定义参数 *****************************/

#define MAIN_Fosc		11059200L	//define main clock
#define Baudrate0		9600L		//define the baudrate,
									//12T mode: 600~115200 for 22.1184MHZ, 300~57600 for 11.0592MHZ
									//1T  mode: 7200~1382400 for 22.1184MHZ, 3600~691200 for 11.0592MHZ
									
									/****************** 编译器自动生成，用户请勿修改 ************************************/

//#define T1_TimerReload	(256 - MAIN_Fosc / 192 / Baudrate0)		//Calculate the timer1 reload value	at 12T mode
#define T1_TimerReload		(256 - MAIN_Fosc / 16 / Baudrate0)		//Calculate the timer1 reload value ar 1T mode
#define BRT_Reload			(256 - MAIN_Fosc / 16 / Baudrate0)		//Calculate the timer1 reload value ar 1T mode


void uart1_init(void);   //串口1初始化
void usart12_init(void); //串口1——2初始化

#endif