#ifndef __LCD_H_
#define __LCD_H_
/**********************************
当使用的是4位数据传输的时候定义，
使用8位取消这个定义
**********************************/
#ifndef __LCD_H_
#define __LCD_H_
/**********************************
当使用的是4位数据传输的时候定义，
使用8位取消这个定义
**********************************/
//#define LCD1602_4PINS

#include "main.h"

#define LCD1602_DATAPINS P1
sbit LCD1602_E=P3^4;
sbit LCD1602_RW=P3^6;
sbit LCD1602_RS=P3^5;

/*LCD1602写入8位命令子函数*/
void LcdWriteCom(u8 com);	  
/*LCD1602写入8位数据子函数*/	
void LcdWriteData(u8 dat);
/*字符串显示函数*/	
void String_display(u8 address,u8*s,u8 number); 
/*数字显示函数*/
void Num_display(u8 address,u16 num,u8 len); 
/*清屏函数*/    
void LCD1602_clear(u8 row);
/*LCD1602初始化子程序*/	
void LcdInit(void);	

#endif

