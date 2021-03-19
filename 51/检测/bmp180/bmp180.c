#include "bmp180.h"
#include "delay.h"

long  temperature;//温度值
long  pressure;//压力值
long  height;//相对海拔高度值
 
/**************************************
起始信号
**************************************/
void BMP085_Start()
{
 
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 0;                    //产生下降沿
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
 
}
 
/**************************************
停止信号
**************************************/
void BMP085_Stop()
{
 
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 1;                    //产生上升沿
    Delay5us();                 //延时
 
}
 
/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void BMP085_SendACK(bit ack)
{
 
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
 
}
 
/**************************************
接收应答信号
**************************************/
bit BMP085_RecvACK()
{
 
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
 
    return CY;
 
}
 
/**************************************
向IIC总线发送一个字节数据
**************************************/
void BMP085_SendByte(BYTE dat)
{
 
    BYTE i;
 
    for (i=0; i<8; i++)         //8位计数器
    {
 
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
     
}
    BMP085_RecvACK();
 
}
 
/**************************************
从IIC总线接收一个字节数据
**************************************/
BYTE BMP085_RecvByte()
{
 
    BYTE i;
    BYTE dat = 0;
 
    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
 
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        dat |= SDA;             //读数据              
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
     
}
    return dat;
 
}
 
 
//*********************************************************
//读出BMP085内部数据,连续两个
//*********************************************************
long Multiple_read(unsigned char ST_Address)
{
    
unsigned char msb, lsb;

    BMP085_Start();                          //起始信号
    BMP085_SendByte(BMP085_SlaveAddress);    //发送设备地址+写信号
    BMP085_SendByte(ST_Address);             //发送存储单元地址
    BMP085_Start();                          //起始信号
    BMP085_SendByte(BMP085_SlaveAddress+1);  //发送设备地址+读信号
 
    msb = BMP085_RecvByte();                 //BUF[0]存储
    BMP085_SendACK(0);                       //回应ACK
    lsb = BMP085_RecvByte();    
    BMP085_SendACK(1);                       //最后一个数据需要回NOACK
 
    BMP085_Stop();                           //停止信号
    Delayms_60s2(5);
   
return (((long)msb)<<8|lsb);
 
}
//write 0x2e into reg 0xf4,wait 4,5ms read reg 0xf6(msb),0xf7(lsb);
long bmp085ReadTemp(void)
{
    BMP085_Start();                  //起始信号
    BMP085_SendByte(BMP085_SlaveAddress);   //发送设备地址+写信号
    BMP085_SendByte(0xF4);          // write register address
    BMP085_SendByte(0x2E);          // write register data for temp
    BMP085_Stop();                   //发送停止信号
    Delayms_60s2(10);// max time is 4.5ms
 
   return (long) Multiple_read(0xF6);//返回温度数据；；
}
//*************************************************************
long bmp085ReadPressure(void)
{
 
long pressure = 0;
 
    BMP085_Start();                   //起始信号
    BMP085_SendByte(BMP085_SlaveAddress);   //发送设备地址+写信号
    BMP085_SendByte(0xF4);             // write register address
    BMP085_SendByte(0x34);             // write register data for pressure
    BMP085_Stop();                     //发送停止信号
    Delayms_60s2(10);                  // max time is 4.5ms
 
   pressure = Multiple_read(0xF6);
   pressure=(((long)pressure<<8)+Multiple_read(0xf8))>>(8-OSS);
  // pressure &= 0x0000FFFF;          //若是bmp085则打开此注释，注释上条
 
return pressure;
}

/*初始化BMP180 ,第一次计算温度和压力之前，需读出EEPROM的数据。*/
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

 /*温度，压强变换处理 */
void bmp085Convert(BMP180_info*temp)
{
 
long x1, x2, b5, b6, x3, b3, p;
unsigned long b4, b7;
 

temp->UnsetTemperature= bmp085ReadTemp();      // 读取温度

temp->UnsetGaspress = bmp085ReadPressure();    // 读取压强
 //计算得到真实的温度值
x1 = ((temp->UnsetTemperature)-temp->cal_parameter.ac6 )* temp->cal_parameter.ac5>> 15;
x2 = ((long) (temp->cal_parameter.mc) << 11) / (x1 +temp->cal_parameter.md );
b5 = x1 + x2;

temp->Temperature = ((b5 + 8) >> 4)*0.1;


//计算得到真实的气压值 
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
 //得到相对海拔高度值
  temp->Altitude=(44330.0*(1.0-pow((float)(temp->Gaspress)/101325.0,1.0/5.255)));
}
 
