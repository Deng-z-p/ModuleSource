#include "lcd.h"

void Lcd1602_Delay1ms(u16 c)   //��� 0us
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
u8 temp=0x80; //��ʼ��temp���λΪ1��ʹ���ܹ���������
 //��whileѭ��
 LCD1602_DATAPINS=0xff;
 LCD1602_RS=0; //�����������
 LCD1602_RW=1; //���ö�����
 LCD1602_E=1; //ʹ��
 //Lcd1602_Delay1ms(100);
 while(temp & 0x80) //��æ��һ�����ʽΪ�٣���temp���λΪ0��
                  //���ʾ1602��æ������while.
 {
 temp=LCD1602_DATAPINS;
 //Lcd1602_Delay1ms(20);
 }      //��p0�ĵĸ�λ����temp,��ʱ
  LCD1602_E=0; //�ر�ʹ���ź�
} 


/*******************************************************************************
* �� �� ��         : LcdWriteCom
* ��������		   : ��LCDд��һ���ֽڵ�����
* ��    ��         : com
* ��    ��         : ��
*******************************************************************************/
#ifndef 	LCD1602_4PINS	 //��û�ж������LCD1602_4PINSʱ
void LcdWriteCom(u8 com)	  //д������
{
busy();
	LCD1602_E = 0;     //ʹ��
	LCD1602_RS = 0;	   //ѡ��������
	LCD1602_RW = 0;	   //ѡ��д��
	
	LCD1602_DATAPINS = com;     //��������
	Lcd1602_Delay1ms(1);		//�ȴ������ȶ�

	LCD1602_E = 1;	          //д��ʱ��
	Lcd1602_Delay1ms(5);	  //����ʱ��
	LCD1602_E = 0;
}
#else 
void LcdWriteCom(u8 com)	  //д������
{
busy();
	LCD1602_E = 0;	 //ʹ������
	LCD1602_RS = 0;	 //ѡ��д������
	LCD1602_RW = 0;	 //ѡ��д��

	LCD1602_DATAPINS = com;	//����4λ�Ľ����ǽӵ�P0�ڵĸ���λ�����Դ��͸���λ���ø�
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 //д��ʱ��
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = com << 4; //���͵���λ
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 //д��ʱ��
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* �� �� ��         : LcdWriteData
* ��������		   : ��LCDд��һ���ֽڵ�����
* ��    ��         : dat
* ��    ��         : ��
*******************************************************************************/		   
#ifndef 	LCD1602_4PINS		   
void LcdWriteData(u8 dat)			//д������
{
busy();
	LCD1602_E = 0;	//ʹ������
	LCD1602_RS = 1;	//ѡ����������
	LCD1602_RW = 0;	//ѡ��д��

	LCD1602_DATAPINS = dat; //д������
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;   //д��ʱ��
	Lcd1602_Delay1ms(5);   //����ʱ��
	LCD1602_E = 0;
}
#else
void LcdWriteData(u8 dat)			//д������
{
busy();
	LCD1602_E = 0;	  //ʹ������
	LCD1602_RS = 1;	  //ѡ��д������
	LCD1602_RW = 0;	  //ѡ��д��

	LCD1602_DATAPINS = dat;	//����4λ�Ľ����ǽӵ�P0�ڵĸ���λ�����Դ��͸���λ���ø�
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	  //д��ʱ��
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = dat << 4; //д�����λ
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	  //д��ʱ��
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* �� �� ��       : LcdInit()
* ��������		 : ��ʼ��LCD��
* ��    ��       : ��
* ��    ��       : ��
*******************************************************************************/		   
#ifndef		LCD1602_4PINS
void LcdInit(void)						  //LCD��ʼ���ӳ���
{
 	LcdWriteCom(0x38);  //����ʾ
	LcdWriteCom(0x0c);  //����ʾ����ʾ���
	LcdWriteCom(0x06);  //дһ��ָ���1
	LcdWriteCom(0x01);  //����
	LcdWriteCom(0x80);  //��������ָ�����
}
#else
void LcdInit(void)						  //LCD��ʼ���ӳ���
{
	LcdWriteCom(0x32);	 //��8λ����תΪ4λ����
	LcdWriteCom(0x28);	 //����λ���µĳ�ʼ��
	LcdWriteCom(0x0c);  //����ʾ����ʾ���
	LcdWriteCom(0x06);  //дһ��ָ���1
	LcdWriteCom(0x01);  //����
	LcdWriteCom(0x80);  //��������ָ�����
}
#endif

/*������ʾ������
address:Ҫ��ʾ��λ�ã�num:Ҫ��ʾ������0-65535��len:Ҫ��ʾ���ֵĳ���*/
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

/*�ַ�����ʾ����
address:Ҫ��ʾ�ĵ�ַ��s:Ҫ��ʾ���ַ�����number:Ҫ��ʾ�ĳ���*/
void String_display(u8 address,u8*s,u8 number)
{
  u8 i;
  busy();
  LcdWriteCom(address);
  for(i=0;i<number;i++)
  LcdWriteData(*s++);
}

/*��������
row:0:���������1�������һ�У�2������ڶ���*/
void LCD1602_clear(u8 row)
{
 u8 i;
 /*����Ҫ�������*/
	if(row==0)
	{
		LcdWriteCom(0x01);
	}
/*��Ҫ��յ�һ��*/
	else if(row==1)
	{
		LcdWriteCom(0x80);
		for(i=0;i<16;i++)
		LcdWriteData(0x20);
	}
/*��Ҫ��յڶ���*/
	else if(row==2)
	{
		LcdWriteCom(0x80+0x40);
		for(i=0;i<16;i++)
		LcdWriteData(0x20);
	}
}


