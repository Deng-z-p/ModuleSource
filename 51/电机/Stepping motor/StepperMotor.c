#include "StepperMotor.h"
 
unsigned char code Positive[] ={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};//��ת 
unsigned char code Reverse[]  ={0X09,0X01,0X03,0X02,0X06,0X04,0X0C,0X08};//��ת  
unsigned char speed;//�������ת�ٵ���

 void delay_xms(unsigned int x)
{
  unsigned int i,j;
 for(i=0;i<x;i++)
 for(j=0;j<112;j++);
}

//��ʱ��ת��
void ONEamotorcw(unsigned int n)
{
    unsigned int i,j;
    n*=512;//������ת64���������תһȦ 512=64*8��
    for(j=0;j<n;j++)
    {
      for(i=0;i<8;i++)  //������ת��45��
        {
        motordata=Positive[i];
        delay_xms(speed);//ת�ٵ���
        }
    }
}
//˳ʱ��ת��
void ONEwmotorcw(unsigned int n)   
{
    unsigned int i,j;
     n*=512;//������ת64���������תһȦ 512=64*8��
  for(j=0;j<n;j++)
    {
      for(i=0;i<8;i++)  //������ת��45��
        {                   
        motordata=Reverse[i];
        delay_xms(speed);//ת�ٵ���
        }
    }
}