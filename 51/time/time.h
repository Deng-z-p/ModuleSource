#ifndef __TIME_H
#define __TIME_H
#include "main.h"

#define MAIN_Fosc		11059200L	         //������ʱ�ӣ�ע�������Ƶ��ѡ��һ��
#define T_MS   50                            //��ʱʱ�䳣������λms
#define T1TMS    (T_MS*MAIN_Fosc/1000)       //1Tģʽ��  
#define T12TMS   (T_MS*MAIN_Fosc/1000/12)    //12Tģʽ��

/*C51��ʱ����ʼ������*/
void TimerInit(u8 Chioce,u8 ms_init);
#endif