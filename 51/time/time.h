#ifndef __TIME_H
#define __TIME_H
#include "main.h"

#define MAIN_Fosc		11059200L	         //定义主时钟，注意和下载频率选择一致
#define T_MS   50                            //定时时间常量，单位ms
#define T1TMS    (T_MS*MAIN_Fosc/1000)       //1T模式下  
#define T12TMS   (T_MS*MAIN_Fosc/1000/12)    //12T模式下

/*C51定时器初始化程序*/
void TimerInit(u8 Chioce,u8 ms_init);
#endif