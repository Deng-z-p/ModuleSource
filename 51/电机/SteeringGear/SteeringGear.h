#ifndef __STEERINGGEAR_H
#define __STEERINGGEAR_H   //橙色：信号线，红色：VCC 棕色：GND
#include "stc12c5a60s2.h"

sbit pwm =P2^4 ;            //PWM信号输出，舵机控制线

void Time0_Init();          //定时器初始化
#endif