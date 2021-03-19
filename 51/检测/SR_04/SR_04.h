#ifndef __SR_04_H
#define __SR_04_H
#include "reg52.h"
#include "intrins.h"

sbit Trig = P2^1;
sbit Echo = P2^0;      //定义Trig Echo引脚

void start_count();    //SR_04启动开始测距
void T0_init();        //定时器0初始化

#endif