#include "lcd.h"

void Lcd1602_Delay1ms(u16 c)   //误差 0us
{
    u8 a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}
    	
}

void busy(void)
{ 
u8 temp=0x80; //初始化temp最高位为1，使得能够进入下面
 //的while循环
 LCD1602_DATAPINS=0xff;
 LCD1602_RS=0; //设置命令操作
 LCD1602_RW=1; //设置读操作
 LCD1602_E=1; //使能
 //Lcd1602_Delay1ms(100);
 while(temp & 0x80) //判忙，一旦表达式为假，即temp最高位为0，
                  //则表示1602不忙，跳出while.
 {
 temp=LCD1602_DATAPINS;
 //Lcd1602_Delay1ms(20);
 }      //把p0的的高位读入temp,延时
  LCD1602_E=0; //关闭使能信号
} 


/*******************************************************************************
* 函 数 名         : LcdWriteCom
* 函数功能		   : 向LCD写入一个字节的命令
* 输    入         : com
* 输    出         : 无
*******************************************************************************/
#ifndef 	LCD1602_4PINS	 //当没有定义这个LCD1602_4PINS时
void LcdWriteCom(u8 com)	  //写入命令
{
busy();
	LCD1602_E = 0;     //使能
	LCD1602_RS = 0;	   //选择发送命令
	LCD1602_RW = 0;	   //选择写入
	
	LCD1602_DATAPINS = com;     //放入命令
	Lcd1602_Delay1ms(1);		//等待数据稳定

	LCD1602_E = 1;	          //写入时序
	Lcd1602_Delay1ms(5);	  //保持时间
	LCD1602_E = 0;
}
#else 
void LcdWriteCom(u8 com)	  //写入命令
{
busy();
	LCD1602_E = 0;	 //使能清零
	LCD1602_RS = 0;	 //选择写入命令
	LCD1602_RW = 0;	 //选择写入

	LCD1602_DATAPINS = com;	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 //写入时序
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = com << 4; //发送低四位
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 //写入时序
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* 函 数 名         : LcdWriteData
* 函数功能		   : 向LCD写入一个字节的数据
* 输    入         : dat
* 输    出         : 无
*******************************************************************************/		   
#ifndef 	LCD1602_4PINS		   
void LcdWriteData(u8 dat)			//写入数据
{
busy();
	LCD1602_E = 0;	//使能清零
	LCD1602_RS = 1;	//选择输入数据
	LCD1602_RW = 0;	//选择写入

	LCD1602_DATAPINS = dat; //写入数据
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;   //写入时序
	Lcd1602_Delay1ms(5);   //保持时间
	LCD1602_E = 0;
}
#else
void LcdWriteData(u8 dat)			//写入数据
{
busy();
	LCD1602_E = 0;	  //使能清零
	LCD1602_RS = 1;	  //选择写入数据
	LCD1602_RW = 0;	  //选择写入

	LCD1602_DATAPINS = dat;	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	  //写入时序
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = dat << 4; //写入低四位
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	  //写入时序
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* 函 数 名       : LcdInit()
* 函数功能		 : 初始化LCD屏
* 输    入       : 无
* 输    出       : 无
*******************************************************************************/		   
#ifndef		LCD1602_4PINS
void LcdInit(void)						  //LCD初始化子程序
{
 	LcdWriteCom(0x38);  //开显示
	LcdWriteCom(0x0c);  //开显示不显示光标
	LcdWriteCom(0x06);  //写一个指针加1
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x80);  //设置数据指针起点
}
#else
void LcdInit(void)						  //LCD初始化子程序
{
	LcdWriteCom(0x32);	 //将8位总线转为4位总线
	LcdWriteCom(0x28);	 //在四位线下的初始化
	LcdWriteCom(0x0c);  //开显示不显示光标
	LcdWriteCom(0x06);  //写一个指针加1
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x80);  //设置数据指针起点
}
#endif

/*数字显示函数：
address:要显示的位置，num:要显示的数字0-65535；len:要显示数字的长度*/
void Num_display(u8 address,u16 num,u8 len)
{
	LcdWriteCom(address);
	if(len==5)
	{
		LcdWriteData(num/10000+'0');
		LcdWriteData(num%10000/1000+'0');
		LcdWriteData(num%10000%1000/100+'0');
		LcdWriteData(num%10000%1000%100/10+'0');
		LcdWriteData(num%10000%1000%100%10+'0');
	}
	else if(len==4)
	{
		LcdWriteData(num/1000+'0');
		LcdWriteData(num%1000/100+'0');
		LcdWriteData(num%1000%100/10+'0');
		LcdWriteData(num%1000%100%10+'0');
	}
	else if(len==3)
	{
		LcdWriteData(num/100+'0');
		LcdWriteData(num%100/10+'0');
		LcdWriteData(num%100%10+'0');
	}
	else if(len==2)
	{
		LcdWriteData(num/10+'0');
		LcdWriteData(num%10+'0');
	}
	else if(len==1)
	{
		LcdWriteData(num+'0');
	}
}

/*字符串显示函数
address:要显示的地址；s:要显示的字符串；number:要显示的长度*/
void String_display(u8 address,u8*s,u8 number)
{
  u8 i;
  busy();
  LcdWriteCom(address);
  for(i=0;i<number;i++)
  LcdWriteData(*s++);
}

/*清屏函数
row:0:清除整屏；1：清除第一行；2：清除第二行*/
void LCD1602_clear(u8 row)
{
 u8 i;
 /*若是要清空整屏*/
	if(row==0)
	{
		LcdWriteCom(0x01);
	}
/*若要清空第一行*/
	else if(row==1)
	{
		LcdWriteCom(0x80);
		for(i=0;i<16;i++)
		LcdWriteData(0x20);
	}
/*若要清空第二行*/
	else if(row==2)
	{
		LcdWriteCom(0x80+0x40);
		for(i=0;i<16;i++)
		LcdWriteData(0x20);
	}
}


