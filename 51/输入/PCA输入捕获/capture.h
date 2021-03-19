#ifndef __CAPTURE_H
#define __CAPTURE_H
#include "reg52.h"

#define		PCA_IDLE_DISABLE	0			//1: MCU在IDLE模式时禁止PCA工作。	0:  MCU在IDLE模式时允许PCA工作。
#define		PCA_SOURCE_SELECT	0			//选择PCA的基准时钟源。
											//0：系统时钟Fosc/12。
											//1：系统时钟Fosc/2。
											//2：定时器0的溢出。
											//3：ECI/P3.4脚的外部时钟输入（最大=Fosc/2）。
											//4：系统时钟Fosc。
											//5：系统时钟Fosc/4。
											//6：系统时钟Fosc/6。
											//7：系统时钟Fosc/8。
#define		PCA_ECF				1		//1: 允许PCA计数器溢出中断，0: 禁止

sfr CCON = 0xD8;	//STC12C5A60S2系列
sfr CMOD = 0xD9;	//STC12C5A60S2系列
sfr CCAPM0 = 0xDA;	//PCA模块0的工作模式寄存器。
sfr CCAPM1 = 0xDB;	//PCA模块1的工作模式寄存器。

sfr CL     = 0xE9;	//
sfr CCAP0L = 0xEA;	//PCA模块0的捕捉/比较寄存器低8位。
sfr CCAP1L = 0xEB;	//PCA模块1的捕捉/比较寄存器低8位。

sfr PCA_PWM0 = 0xF2;	//PCA模块0 PWM寄存器。
sfr PCA_PWM1 = 0xF3;	//PCA模块1 PWM寄存器。
sfr CH     = 0xF9;
sfr CCAP0H = 0xFA;		//PCA模块0的捕捉/比较寄存器高8位。
sfr CCAP1H = 0xFB;		//PCA模块1的捕捉/比较寄存器高8位。

sbit CCF0  = CCON^0;	//PCA 模块0中断标志，由硬件置位，必须由软件清0。
sbit CCF1  = CCON^1;	//PCA 模块1中断标志，由硬件置位，必须由软件清0。
sbit CR    = CCON^6;	//1: 允许PCA计数器计数，必须由软件清0。
sbit CF    = CCON^7;	//PCA计数器溢出（CH，CL由FFFFH变为0000H）标志。PCA计数器溢出后由硬件置位，必须由软件清0。

void cature_init();

#endif