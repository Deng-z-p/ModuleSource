#ifndef __LCD12864_H
#define __LCD12864_H
#include "reg52.h"

#define LCD12864_DATA_PORT	 P0			// LCD12864的8位数据端口

sbit gLcd12864_E  = P2^7;			// LCD12864控制总线的使能信号
sbit gLcd12864_RW = P2^5;			// LCD12864控制总线的读写选择信号
sbit gLcd12864_RS = P2^6;			// LCD12864控制总线的数据/命令选择信号
sbit gLcd12864_PSB= P3^2;			// PSB=1为并口，PSB=0为串口

/*
**********************************************************************
*                         外部函数原型声明
**********************************************************************
*/
void Lcd12864Init(void);
void Lcd12864ShowImage(unsigned char *pData);
void Lcd12864ShowStr(unsigned char x, unsigned char y, unsigned char *pStr);     //显示字符串

#endif
