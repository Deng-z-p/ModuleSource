#include<key.h>
bit execult;  //不支持连续按标志位
unsigned char KeyValue=0,value,select,key_temp,key_clean;

extern unsigned char number[6];

unsigned int k;

void KeyDown(void)
{
	GPIO_KEY=0xf0;
	if(GPIO_KEY!=0xf0&&execult==0)//读取按键是否按下
	{
	  execult=1;
		GPIO_KEY=0Xf0;       //测试列
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=0;break;
				case(0Xb0):	KeyValue=1;break;
				case(0Xd0): KeyValue=2;break;
				case(0Xe0):	KeyValue=3;break;
			}
			//测试行
			GPIO_KEY=0X0f;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=KeyValue;break;
				case(0X0b):	KeyValue=KeyValue+4;break;
				case(0X0d): KeyValue=KeyValue+8;break;
				case(0X0e):	KeyValue=KeyValue+12;break;
				
			}
	    if(KeyValue==15)
			{ 
			   k=0;
			 while(GPIO_KEY!=0x0f)
			 {
			   Delay1ms(10);//长按D，KeyValue=16；
				 k++;
				 if(k>100) 
				 {
				  KeyValue=16;
					break;
				 }
			 }
			}
	 key_keydata_dispose();
	}
	else if(GPIO_KEY==0xf0)
	execult=0;
	
}

void key_keydata_dispose()
{
  switch(KeyValue)
	{
	  case(0): value=1;break;
		case(1): value=4;break;
		case(2): value=7;break;
		case(3): select=1;break;//*
		case(4): value=2;break;
		case(5): value=5;break;
		case(6): value=8;break;
		case(7): value=0;break;
		case(8): value=3;break;
		case(9): value=6;break;
		case(10):value=9;break;
		case(11):select=2;break;//#
		case(12):key_temp=1;break;//A
		case(13):key_temp=2;break;//B
	  case(14):key_temp=3;break;//C
		case(15):key_temp=4;break;//短按D
		case(16):key_temp=5;break;//长按D
	}
}


void Delay1ms(unsigned int c)   //误差 0us
{
    unsigned char a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}
    	
}
