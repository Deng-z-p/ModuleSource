#ifndef _bmp180_h_
#define _bmp180_h_

#include "math.h" 
#include "stc12c5a60s2.h"

sbit  SCL=P0^0;       //IICʱ�����Ŷ���
sbit  SDA=P0^1;       //IIC�������Ŷ���
extern long  temperature;
extern long  pressure;
extern long  height;
 
#define BMP085_SlaveAddress   0xee  //����������IIC�����еĴӵ�ַ                              
#define OSS 2                       // Oversampling Setting (note: code is not set up to use other OSS values)

typedef unsigned char  BYTE;
typedef unsigned short WORD;

//BMP180У������
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
    BMP180_parameter cal_parameter;//����ϵ��
    unsigned long UnsetTemperature;//δУ�����¶�ֵ
    unsigned long UnsetGaspress;   //δУ׼����ѹֵ
    float Temperature;             //У׼����¶�ֵ
    unsigned long Gaspress;        //У׼�����ѹֵ
    float Altitude;                //����
}BMP180_info;


void BMP180ReadCalibrateParameter_Init(BMP180_info*p);  ///*��ʼ��BMP180 ,��һ�μ����¶Ⱥ�ѹ��֮ǰ�������EEPROM�����ݡ�*/
void bmp085Convert(BMP180_info*temp) ;                   ///*�¶ȣ�ѹǿ�任���� */

#endif
