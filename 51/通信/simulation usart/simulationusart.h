#ifndef __SIMULATIONUSART_H
#define __SIMULATIONUSART_H
#include "reg52.h"
sbit	P_TXD1 = P3^1;

#define MAIN_Fosc		11059200	                    //������ʱ��, ģ�⴮�ںͺ���ʱ���Զ���Ӧ��5~35MHZ

void	Tx1Send(unsigned char dat);		              //9600��N��8��1		����һ���ֽ�
void PrintString(unsigned char code *puts);		    //����һ���ַ���

#endif