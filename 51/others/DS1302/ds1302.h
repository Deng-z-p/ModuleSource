#ifndef __DS1302_H_
#define __DS1302_H_

//---包含头文件---//
#include "main.h"

//---定义ds1302使用的IO口---//
sbit DSIO=P3^4;
sbit RST=P3^5;
sbit SCLK=P3^6;

//---定义全局函数---//
void Ds1302Write_Time(u8* time);
void Ds1302ReadTime();

//---存储顺序是秒分时日月周年,存储格式是用BCD码---//
extern u8 TIME[7] ;
//---DS1302写入和读取时分秒的地址命令---//
//---秒分时日月周年 最低位读写位;-------//
extern u8 code READ_RTC_ADDR[7]; 
extern u8 code WRITE_RTC_ADDR[7] ;
#endif