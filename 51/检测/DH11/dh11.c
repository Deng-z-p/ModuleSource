#include "dh11.h"

u8 rec_temperature_dat[6];   //用于接收温度数据数组
u8 rec_humidity_dat[7];   	 //用于接收湿度数据数组   

void DHT11_delay_us(u8 n)
{
    while(--n);
}

void DHT11_delay_ms(u16 z)//ms级别延时；
{
   u16 i,j;
   for(i=z;i>0;i--)
      for(j=110;j>0;j--);
}

void DHT11_start()//发送起始信号；
{
   Data=1;
   DHT11_delay_us(5);
   Data=0;
   DHT11_delay_ms(30); //延时18ms以上
   Data=1;
   DHT11_delay_us(30);//拉高20—40us;
}

u8 DHT11_rec_byte()  //接收一个字节
{
   u8 i,dat=0;
  for(i=0;i<8;i++)    //从高到低依次接收8位数据
   {          
      while(!Data);   ////等待50us低电平过去
      DHT11_delay_us(8); //延时60us，如果还为高则数据为1，否则为0 
      dat<<=1;           //移位使正确接收8位数据，数据为0时直接移位
      if(Data==1)    
				//数据为1时，dat为1；
         dat|=0x01;
			else
				 dat|=0x00;
      while(Data);//等待数据线拉低    
    }  
    return dat;//返回一个字节的数据；
}

//接收湿度温度数据函数，调用此函数后即可读取数组中的数据
void DHT11_receive()//接收40位的数据
{
    u8 R_H,R_L,T_H,T_L,RL,TL,revise; 
    DHT11_start();
    if(Data==0)
    {
        while(Data==0);          //等待拉高     
        DHT11_delay_us(40);      //拉高后延时80us
        R_H=DHT11_rec_byte();    //接收湿度高八位  
        R_L=DHT11_rec_byte();    //接收湿度低八位  
        T_H=DHT11_rec_byte();    //接收温度高八位  
        T_L=DHT11_rec_byte();    //接收温度低八位
        revise=DHT11_rec_byte(); //接收校正位

        DHT11_delay_us(25);      //结束

        if((R_H+R_L+T_H+T_L)==revise) //校正
        {
           /*数据处理，方便显示*/
        rec_humidity_dat[0]='0'+(R_H/10);//湿度整数高8位；
        rec_humidity_dat[1]='0'+(R_H%10);
				rec_humidity_dat[2]='.';
				rec_humidity_dat[3]='0'+(R_L/10);//湿度小数低8位
				rec_humidity_dat[4]='0'+(R_L%10);
				rec_humidity_dat[5]='R';
				rec_humidity_dat[6]='H';
				
				rec_temperature_dat[0]='0'+(T_H/10);//温度整数高8位；
        rec_temperature_dat[1]='0'+(T_H%10);
				rec_temperature_dat[2]='.';
				rec_temperature_dat[3]='0'+(T_L/10);
				rec_temperature_dat[4]='0'+(T_L%10);//温度小数低8位；
				rec_temperature_dat[5]='C';
        }   
    }
}
