#ifndef __LCD12864_H
#define __LCD12864_H
#include "reg52.h"

#define LCD12864_DATA_PORT	 P0			// LCD12864��8λ���ݶ˿�

sbit gLcd12864_E  = P2^7;			// LCD12864�������ߵ�ʹ���ź�
sbit gLcd12864_RW = P2^5;			// LCD12864�������ߵĶ�дѡ���ź�
sbit gLcd12864_RS = P2^6;			// LCD12864�������ߵ�����/����ѡ���ź�
sbit gLcd12864_PSB= P3^2;			// PSB=1Ϊ���ڣ�PSB=0Ϊ����

/*
**********************************************************************
*                         �ⲿ����ԭ������
**********************************************************************
*/
void Lcd12864Init(void);
void Lcd12864ShowImage(unsigned char *pData);
void Lcd12864ShowStr(unsigned char x, unsigned char y, unsigned char *pStr);     //��ʾ�ַ���

#endif
