#ifndef __SIMULATIONUSART_H
#define __SIMULATIONUSART_H
#include "reg52.h"
sbit	P_TXD1 = P3^1;

#define MAIN_Fosc		11059200	                    //定义主时钟, 模拟串口和和延时会自动适应。5~35MHZ

void	Tx1Send(unsigned char dat);		              //9600，N，8，1		发送一个字节
void PrintString(unsigned char code *puts);		    //发送一串字符串

#endif