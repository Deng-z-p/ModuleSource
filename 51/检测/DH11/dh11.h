#ifndef _DH11_H
#define _DH11_H
#include "main.h"

sbit Data=P2^4; 
/*
����ʪ���¶����ݺ�����
����һ�δ˺��������ȡ�������е���ʪ�ȣ�д����rec_temperature_dat��rec_humidity_dat������
*/
void DHT11_receive(); //����һ�β������������
   
extern unsigned char rec_temperature_dat[6];   //���ڽ����¶���������
extern unsigned char rec_humidity_dat[7];	   //���ڽ���ʪ���������� 
#endif

