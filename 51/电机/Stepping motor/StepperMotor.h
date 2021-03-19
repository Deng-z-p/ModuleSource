#ifndef __STEPPERMOTOR_H
#define __STEPPERMOTOR_H
//#include "reg52.h"
#include "stc12c5a60s2.h"

#define motordata P1   //步进电机控制接口定义
//电机为8拍（A-AB-B-BC-C-CD-D-DA-A....）

void ONEamotorcw(unsigned int n);//逆时针转动,n:转动的圈数
void ONEwmotorcw(unsigned int n);//顺时针转动,n:转动的圈数
#endif