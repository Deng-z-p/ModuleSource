#ifndef __SR_04_H
#define __SR_04_H
#include "reg52.h"
#include "intrins.h"

sbit Trig = P2^1;
sbit Echo = P2^0;      //����Trig Echo����

void start_count();    //SR_04������ʼ���
void T0_init();        //��ʱ��0��ʼ��

#endif