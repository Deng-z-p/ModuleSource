#include "StepperMotor.h"
 
unsigned char code Positive[] ={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};//反转 
unsigned char code Reverse[]  ={0X09,0X01,0X03,0X02,0X06,0X04,0X0C,0X08};//正转  
unsigned char speed;//步进电机转速调节

 void delay_xms(unsigned int x)
{
  unsigned int i,j;
 for(i=0;i<x;i++)
 for(j=0;j<112;j++);
}

//逆时针转动
void ONEamotorcw(unsigned int n)
{
    unsigned int i,j;
    n*=512;//传动轮转64，步进电机转一圈 512=64*8；
    for(j=0;j<n;j++)
    {
      for(i=0;i<8;i++)  //传动轮转动45°
        {
        motordata=Positive[i];
        delay_xms(speed);//转速调节
        }
    }
}
//顺时针转动
void ONEwmotorcw(unsigned int n)   
{
    unsigned int i,j;
     n*=512;//传动轮转64，步进电机转一圈 512=64*8；
  for(j=0;j<n;j++)
    {
      for(i=0;i<8;i++)  //传动轮转动45°
        {                   
        motordata=Reverse[i];
        delay_xms(speed);//转速调节
        }
    }
}