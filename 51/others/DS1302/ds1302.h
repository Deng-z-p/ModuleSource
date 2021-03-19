#ifndef __DS1302_H_
#define __DS1302_H_

//---����ͷ�ļ�---//
#include "main.h"

//---����ds1302ʹ�õ�IO��---//
sbit DSIO=P3^4;
sbit RST=P3^5;
sbit SCLK=P3^6;

//---����ȫ�ֺ���---//
void Ds1302Write_Time(u8* time);
void Ds1302ReadTime();

//---�洢˳�������ʱ��������,�洢��ʽ����BCD��---//
extern u8 TIME[7] ;
//---DS1302д��Ͷ�ȡʱ����ĵ�ַ����---//
//---���ʱ�������� ���λ��дλ;-------//
extern u8 code READ_RTC_ADDR[7]; 
extern u8 code WRITE_RTC_ADDR[7] ;
#endif