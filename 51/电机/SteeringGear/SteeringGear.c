#include "SteeringGear.h"

unsigned char count; //0.5ms次数标识
unsigned char Angle; //角度标识

void Time0_Init()    //定时器初始化
{
    AUXR&=0x7f;      //12分频
    TMOD = 0x01;     //定时器0工作在方式1,16位定时/计数器 
    IE   = 0x82;     //相当于打开EA和ET0
    TH0  = 0xfe;
    TL0  = 0x33;     //11.0592MZ晶振，0.5ms
    TR0  =1;         //定时器开始
}

void Time0_Int() interrupt 1 //中断程序
{
    TH0 = 0xfe;             //重新赋值
	  TL0 = 0x33;
    if(count< Angle)        //判断0.5ms次数是否小于角度标识
      pwm=1;                //确实小于，PWM输出高电平
    else
      pwm=0;                //大于则输出低电平
    count++;                //0.5ms次数加1
    count=count%40;         //次数始终保持为40 即保持周期为20ms
}
