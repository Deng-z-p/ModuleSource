#ifndef __LCD_H_
#define __LCD_H_
/**********************************
��ʹ�õ���4λ���ݴ����ʱ���壬
ʹ��8λȡ���������
**********************************/
#ifndef __LCD_H_
#define __LCD_H_
/**********************************
��ʹ�õ���4λ���ݴ����ʱ���壬
ʹ��8λȡ���������
**********************************/
//#define LCD1602_4PINS

#include "main.h"

#define LCD1602_DATAPINS P1
sbit LCD1602_E=P3^4;
sbit LCD1602_RW=P3^6;
sbit LCD1602_RS=P3^5;

/*LCD1602д��8λ�����Ӻ���*/
void LcdWriteCom(u8 com);	  
/*LCD1602д��8λ�����Ӻ���*/	
void LcdWriteData(u8 dat);
/*�ַ�����ʾ����*/	
void String_display(u8 address,u8*s,u8 number); 
/*������ʾ����*/
void Num_display(u8 address,u16 num,u8 len); 
/*��������*/    
void LCD1602_clear(u8 row);
/*LCD1602��ʼ���ӳ���*/	
void LcdInit(void);	

#endif

