#ifndef _bmp180_h_
#define _bmp180_h_

#include "math.h" 
#include "stc12c5a60s2.h"

sbit  SCL=P0^0;       //IIC时钟引脚定义
sbit  SDA=P0^1;       //IIC数据引脚定义
extern long  temperature;
extern long  pressure;
extern long  height;
 
#define BMP085_SlaveAddress   0xee  //定义器件在IIC总线中的从地址                              
#define OSS 2                       // Oversampling Setting (note: code is not set up to use other OSS values)

typedef unsigned char  BYTE;
typedef unsigned short WORD;

//BMP180校正参数
typedef struct{
    short ac1;
    short ac2;
    short ac3;
    unsigned short ac4;
    unsigned short ac5;
    unsigned short ac6;
    short b1;
    short b2;
    short mb;
    short mc;
    short md;
}BMP180_parameter; 

typedef struct{
    BMP180_parameter cal_parameter;//修正系数
    unsigned long UnsetTemperature;//未校正的温度值
    unsigned long UnsetGaspress;   //未校准的气压值
    float Temperature;             //校准后的温度值
    unsigned long Gaspress;        //校准后的气压值
    float Altitude;                //海拔
}BMP180_info;


void BMP180ReadCalibrateParameter_Init(BMP180_info*p);  ///*初始化BMP180 ,第一次计算温度和压力之前，需读出EEPROM的数据。*/
void bmp085Convert(BMP180_info*temp) ;                   ///*温度，压强变换处理 */

#endif
