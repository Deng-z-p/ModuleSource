#ifndef __CAPTURE_H
#define __CAPTURE_H
#include "reg52.h"

#define		PCA_IDLE_DISABLE	0			//1: MCU��IDLEģʽʱ��ֹPCA������	0:  MCU��IDLEģʽʱ����PCA������
#define		PCA_SOURCE_SELECT	0			//ѡ��PCA�Ļ�׼ʱ��Դ��
											//0��ϵͳʱ��Fosc/12��
											//1��ϵͳʱ��Fosc/2��
											//2����ʱ��0�������
											//3��ECI/P3.4�ŵ��ⲿʱ�����루���=Fosc/2����
											//4��ϵͳʱ��Fosc��
											//5��ϵͳʱ��Fosc/4��
											//6��ϵͳʱ��Fosc/6��
											//7��ϵͳʱ��Fosc/8��
#define		PCA_ECF				1		//1: ����PCA����������жϣ�0: ��ֹ

sfr CCON = 0xD8;	//STC12C5A60S2ϵ��
sfr CMOD = 0xD9;	//STC12C5A60S2ϵ��
sfr CCAPM0 = 0xDA;	//PCAģ��0�Ĺ���ģʽ�Ĵ�����
sfr CCAPM1 = 0xDB;	//PCAģ��1�Ĺ���ģʽ�Ĵ�����

sfr CL     = 0xE9;	//
sfr CCAP0L = 0xEA;	//PCAģ��0�Ĳ�׽/�ȽϼĴ�����8λ��
sfr CCAP1L = 0xEB;	//PCAģ��1�Ĳ�׽/�ȽϼĴ�����8λ��

sfr PCA_PWM0 = 0xF2;	//PCAģ��0 PWM�Ĵ�����
sfr PCA_PWM1 = 0xF3;	//PCAģ��1 PWM�Ĵ�����
sfr CH     = 0xF9;
sfr CCAP0H = 0xFA;		//PCAģ��0�Ĳ�׽/�ȽϼĴ�����8λ��
sfr CCAP1H = 0xFB;		//PCAģ��1�Ĳ�׽/�ȽϼĴ�����8λ��

sbit CCF0  = CCON^0;	//PCA ģ��0�жϱ�־����Ӳ����λ�������������0��
sbit CCF1  = CCON^1;	//PCA ģ��1�жϱ�־����Ӳ����λ�������������0��
sbit CR    = CCON^6;	//1: ����PCA�����������������������0��
sbit CF    = CCON^7;	//PCA�����������CH��CL��FFFFH��Ϊ0000H����־��PCA�������������Ӳ����λ�������������0��

void cature_init();

#endif