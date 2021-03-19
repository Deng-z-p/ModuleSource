#ifndef _DH11_H
#define _DH11_H
#include "main.h"

sbit Data=P2^4; 
/*
接收湿度温度数据函数，
调用一次此函数，则读取传感器中的温湿度，写入在rec_temperature_dat和rec_humidity_dat数组中
*/
void DHT11_receive(); //接受一次捕获的所有数据
   
extern unsigned char rec_temperature_dat[6];   //用于接收温度数据数组
extern unsigned char rec_humidity_dat[7];	   //用于接收湿度数据数组 
#endif

