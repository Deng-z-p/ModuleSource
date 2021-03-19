#include "bmp180.h"
#include "delay.h"

long  temperature;//�¶�ֵ
long  pressure;//ѹ��ֵ
long  height;//��Ժ��θ߶�ֵ
 
/**************************************
��ʼ�ź�
**************************************/
void BMP085_Start()
{
 
    SDA = 1;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 0;                    //�����½���
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
 
}
 
/**************************************
ֹͣ�ź�
**************************************/
void BMP085_Stop()
{
 
    SDA = 0;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 1;                    //����������
    Delay5us();                 //��ʱ
 
}
 
/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void BMP085_SendACK(bit ack)
{
 
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ
 
}
 
/**************************************
����Ӧ���ź�
**************************************/
bit BMP085_RecvACK()
{
 
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    CY = SDA;                   //��Ӧ���ź�
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ
 
    return CY;
 
}
 
/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void BMP085_SendByte(BYTE dat)
{
 
    BYTE i;
 
    for (i=0; i<8; i++)         //8λ������
    {
 
        dat <<= 1;              //�Ƴ����ݵ����λ
        SDA = CY;               //�����ݿ�
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
     
}
    BMP085_RecvACK();
 
}
 
/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
BYTE BMP085_RecvByte()
{
 
    BYTE i;
    BYTE dat = 0;
 
    SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
 
        dat <<= 1;
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        dat |= SDA;             //������              
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
     
}
    return dat;
 
}
 
 
//*********************************************************
//����BMP085�ڲ�����,��������
//*********************************************************
long Multiple_read(unsigned char ST_Address)
{
    
unsigned char msb, lsb;

    BMP085_Start();                          //��ʼ�ź�
    BMP085_SendByte(BMP085_SlaveAddress);    //�����豸��ַ+д�ź�
    BMP085_SendByte(ST_Address);             //���ʹ洢��Ԫ��ַ
    BMP085_Start();                          //��ʼ�ź�
    BMP085_SendByte(BMP085_SlaveAddress+1);  //�����豸��ַ+���ź�
 
    msb = BMP085_RecvByte();                 //BUF[0]�洢
    BMP085_SendACK(0);                       //��ӦACK
    lsb = BMP085_RecvByte();    
    BMP085_SendACK(1);                       //���һ��������Ҫ��NOACK
 
    BMP085_Stop();                           //ֹͣ�ź�
    Delayms_60s2(5);
   
return (((long)msb)<<8|lsb);
 
}
//write 0x2e into reg 0xf4,wait 4,5ms read reg 0xf6(msb),0xf7(lsb);
long bmp085ReadTemp(void)
{
    BMP085_Start();                  //��ʼ�ź�
    BMP085_SendByte(BMP085_SlaveAddress);   //�����豸��ַ+д�ź�
    BMP085_SendByte(0xF4);          // write register address
    BMP085_SendByte(0x2E);          // write register data for temp
    BMP085_Stop();                   //����ֹͣ�ź�
    Delayms_60s2(10);// max time is 4.5ms
 
   return (long) Multiple_read(0xF6);//�����¶����ݣ���
}
//*************************************************************
long bmp085ReadPressure(void)
{
 
long pressure = 0;
 
    BMP085_Start();                   //��ʼ�ź�
    BMP085_SendByte(BMP085_SlaveAddress);   //�����豸��ַ+д�ź�
    BMP085_SendByte(0xF4);             // write register address
    BMP085_SendByte(0x34);             // write register data for pressure
    BMP085_Stop();                     //����ֹͣ�ź�
    Delayms_60s2(10);                  // max time is 4.5ms
 
   pressure = Multiple_read(0xF6);
   pressure=(((long)pressure<<8)+Multiple_read(0xf8))>>(8-OSS);
  // pressure &= 0x0000FFFF;          //����bmp085��򿪴�ע�ͣ�ע������
 
return pressure;
}

/*��ʼ��BMP180 ,��һ�μ����¶Ⱥ�ѹ��֮ǰ�������EEPROM�����ݡ�*/
void BMP180ReadCalibrateParameter_Init(BMP180_info*p)
{
    p->cal_parameter.ac1 = Multiple_read(0xAA);
    p->cal_parameter.ac2 = Multiple_read(0xAC);
    p->cal_parameter.ac3 = Multiple_read(0xAE);
    p->cal_parameter.ac4 = Multiple_read(0xB0);
    p->cal_parameter.ac5 = Multiple_read(0xB2);
    p->cal_parameter.ac6 = Multiple_read(0xB4);
    p->cal_parameter.b1  = Multiple_read(0xB6);
    p->cal_parameter.b2  = Multiple_read(0xB8);
    p->cal_parameter.mb  = Multiple_read(0xBA);
    p->cal_parameter.mc  = Multiple_read(0xBC);
    p->cal_parameter.md  = Multiple_read(0xBE);
 
}

 /*�¶ȣ�ѹǿ�任���� */
void bmp085Convert(BMP180_info*temp)
{
 
long x1, x2, b5, b6, x3, b3, p;
unsigned long b4, b7;
 

temp->UnsetTemperature= bmp085ReadTemp();      // ��ȡ�¶�

temp->UnsetGaspress = bmp085ReadPressure();    // ��ȡѹǿ
 //����õ���ʵ���¶�ֵ
x1 = ((temp->UnsetTemperature)-temp->cal_parameter.ac6 )* temp->cal_parameter.ac5>> 15;
x2 = ((long) (temp->cal_parameter.mc) << 11) / (x1 +temp->cal_parameter.md );
b5 = x1 + x2;

temp->Temperature = ((b5 + 8) >> 4)*0.1;


//����õ���ʵ����ѹֵ 
  b6 = b5 - 4000;
  // Calculate B3
  x1 = ((long)(temp->cal_parameter.b2) * (b6 * b6>>12))>>11;
  x2 = (long)(temp->cal_parameter.ac2)* b6>>11;
  x3 = x1 + x2;
  b3 = ((((long)(temp->cal_parameter.ac1)*4 + x3)<<OSS) + 2)/4;
   
  // Calculate B4
  x1 = ((long)temp->cal_parameter.ac3) * b6>>13;
  x2 = ((long)(temp->cal_parameter.b1) * (b6 * b6>>12))>>16;
  x3 = ((x1 + x2) + 2)>>2;
  b4 = ((long)(temp->cal_parameter.ac4) * (unsigned long)(x3 + 32768))>>15;
   
  b7 = ((unsigned long)(temp->UnsetGaspress) - b3) * (50000>>OSS);
  if (b7 < 0x80000000)
    p = (b7*2)/b4;
  else
    p = (b7/b4)*2;
     
  x1 = (p>>8) * (p>>8);
  x1 = ((long)x1 * 3038)>>16;
  x2 = (-7357 * p)>>16;
  temp->Gaspress = p+((x1 + x2 + 3791)>>4);
 //�õ���Ժ��θ߶�ֵ
  temp->Altitude=(44330.0*(1.0-pow((float)(temp->Gaspress)/101325.0,1.0/5.255)));
}
 
