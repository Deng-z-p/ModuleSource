#ifndef  __DELAY_H
#define  __DELAY_H
#include "stc12c5a60s2.h"
#include "intrins.h"

#define MAIN_Fosc		11059200L	//define main clock

void  Delay_ms_60s2(unsigned int ms);//MAIN_Fosc control
void  Delay1ms();		   //@11.0592MHz
void  Delay_ms_c52(unsigned int c) ;   //Îó²î 0us
void  Delay_us(unsigned int us); 
#endif