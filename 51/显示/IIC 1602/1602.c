#include "1602.h"

bit ack;
unsigned char LCD_data=0x08;

void delay_nus(unsigned int n) //N us��ʱ����
{
	unsigned int i=0;
	for (i=0;i<n;i++)
	_nop_();
}
void delay_nms(unsigned int n) //N ms��ʱ����
{
	unsigned int i,j;
		for (i=0;i<n;i++)
			for (j=0;j<1140;j++);
}

void nop4()
{
	 _nop_();     //�ȴ�һ����������
	 _nop_();     //�ȴ�һ����������
	 _nop_();     //�ȴ�һ����������
	 _nop_();     //�ȴ�һ����������
}
//***************************************
void Start()
{
 	SDA=1;
  _nop_();
  SCL=1;
	nop4();
  SDA=0;
	nop4();
  SCL=0;
  _nop_();
	_nop_();
}

void Stop()
{
 	SDA=0;
  _nop_();
	SCL=0;
	nop4();//>4us��SCL����
	SCL=1;
	nop4();
	SDA=1;
  _nop_();
  _nop_();
}

void  Write_A_Byte(unsigned char c)
{
 unsigned char BitCnt;
  for(BitCnt=0;BitCnt<8;BitCnt++)   //Ҫ���͵����ݳ���Ϊ8λ
    {
     if((c<<BitCnt)&0x80)  SDA=1;   //�жϷ���λ
     else  SDA=0;                
     _nop_();
     SCL=1;                         //��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ
     nop4(); 
     _nop_();       
     SCL=0; 
    }  
    _nop_();
    _nop_();
    SDA=1;                           //8λ��������ͷ������ߣ�׼������Ӧ��λ
    _nop_();
    _nop_();  
    SCL=1;
    _nop_();
    _nop_();
    _nop_();
    if(SDA==1)ack=0;     
       else 
	   {
	   ack=1;        //�ж��Ƿ���յ�Ӧ���ź�
	   P1=0x00;
	   }	 	   	   
    SCL=0;
    _nop_();
    _nop_();
}

bit Write_Random_Address_Byte(unsigned char add,unsigned char dat)
{
 	Start();                 //��������
	Write_A_Byte(add<<1|0);  //����������ַ
  if(ack==0)return(0);
	Write_A_Byte(dat);       //��������
  if(ack==0)return(0);
	Stop();                  //��������
  return(1);
}

//********************Һ����ʹ��*********************
void Enable_LCD_write()
{
  LCD_data|=(1<<(3-1));//E=1;
	Write_Random_Address_Byte(0x27,LCD_data);  //
	delay_nus(2);
  LCD_data&=~(1<<(3-1));//E=0;
  Write_Random_Address_Byte(0x27,LCD_data);
}

//*************д����****************************
void LCD_write_command(unsigned char command)
{
	delay_nus(16);
	LCD_data&=~(1<<(1-1));//RS=0;
	LCD_data&=~(1<<(2-1));//RW=0;
	//LCD_data&=~(1<<(4-1));
  Write_Random_Address_Byte(0x27,LCD_data);

	LCD_data&=0X0f;           //�����λ
	LCD_data|=command & 0xf0; //д����λ
  Write_Random_Address_Byte(0x27,LCD_data);
  Enable_LCD_write();

	command=command<<4;     //����λ�Ƶ�����λ
	LCD_data&=0x0f;         //�����λ
	LCD_data|=command&0xf0; //д����λ
  Write_Random_Address_Byte(0x27,LCD_data);
  Enable_LCD_write();
}
//*************д����****************************
void LCD_write_data(unsigned char value) 
{
	delay_nus(16);
	LCD_data|=(1<<(1-1));  //RS=1;
	LCD_data&=~(1<<(2-1));//RW=0;
  Write_Random_Address_Byte(0x27,LCD_data);

	LCD_data&=0X0f;       //�����λ
	LCD_data|=value&0xf0; //д����λ
  Write_Random_Address_Byte(0x27,LCD_data);
  Enable_LCD_write();			

	value=value<<4;           //����λ�Ƶ�����λ
	LCD_data&=0x0f;           //�����λ
	LCD_data|=value&0xf0;     //д����λ
  Write_Random_Address_Byte(0x27,LCD_data);
  Enable_LCD_write();
}

//**********************������ʾλ��*********************************
void set_position(unsigned char x,unsigned char y)
{
	unsigned char position;
	if (y == 0)
        position = 0x80 + x;
	else 
		position = 0xc0 + x;
    LCD_write_command(position);
}
//**********************��ʾ�ַ���*****************************

void display_string(unsigned char x,unsigned char y,unsigned char *s)
{ 
  set_position(x,y);
	while (*s) 
 	{     
		LCD_write_data(*s);     
		s++;     
 	}
}
//*************Һ����ʼ��****************************
void LCD_init(void) 
{ 
	LCD_write_command(0x28);
	delay_nus(40); 
	LCD_write_command(0x28);
	delay_nus(40); 
  Enable_LCD_write();
	delay_nus(40);
	LCD_write_command(0x28); //4λ��ʾ������������������������������������
	LCD_write_command(0x0c); //��ʾ��
	LCD_write_command(0x01); //����
	delay_nms(2);
}

