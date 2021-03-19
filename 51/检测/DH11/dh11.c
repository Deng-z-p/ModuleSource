#include "dh11.h"

u8 rec_temperature_dat[6];   //���ڽ����¶���������
u8 rec_humidity_dat[7];   	 //���ڽ���ʪ����������   

void DHT11_delay_us(u8 n)
{
    while(--n);
}

void DHT11_delay_ms(u16 z)//ms������ʱ��
{
   u16 i,j;
   for(i=z;i>0;i--)
      for(j=110;j>0;j--);
}

void DHT11_start()//������ʼ�źţ�
{
   Data=1;
   DHT11_delay_us(5);
   Data=0;
   DHT11_delay_ms(30); //��ʱ18ms����
   Data=1;
   DHT11_delay_us(30);//����20��40us;
}

u8 DHT11_rec_byte()  //����һ���ֽ�
{
   u8 i,dat=0;
  for(i=0;i<8;i++)    //�Ӹߵ������ν���8λ����
   {          
      while(!Data);   ////�ȴ�50us�͵�ƽ��ȥ
      DHT11_delay_us(8); //��ʱ60us�������Ϊ��������Ϊ1������Ϊ0 
      dat<<=1;           //��λʹ��ȷ����8λ���ݣ�����Ϊ0ʱֱ����λ
      if(Data==1)    
				//����Ϊ1ʱ��datΪ1��
         dat|=0x01;
			else
				 dat|=0x00;
      while(Data);//�ȴ�����������    
    }  
    return dat;//����һ���ֽڵ����ݣ�
}

//����ʪ���¶����ݺ��������ô˺����󼴿ɶ�ȡ�����е�����
void DHT11_receive()//����40λ������
{
    u8 R_H,R_L,T_H,T_L,RL,TL,revise; 
    DHT11_start();
    if(Data==0)
    {
        while(Data==0);          //�ȴ�����     
        DHT11_delay_us(40);      //���ߺ���ʱ80us
        R_H=DHT11_rec_byte();    //����ʪ�ȸ߰�λ  
        R_L=DHT11_rec_byte();    //����ʪ�ȵͰ�λ  
        T_H=DHT11_rec_byte();    //�����¶ȸ߰�λ  
        T_L=DHT11_rec_byte();    //�����¶ȵͰ�λ
        revise=DHT11_rec_byte(); //����У��λ

        DHT11_delay_us(25);      //����

        if((R_H+R_L+T_H+T_L)==revise) //У��
        {
           /*���ݴ���������ʾ*/
        rec_humidity_dat[0]='0'+(R_H/10);//ʪ��������8λ��
        rec_humidity_dat[1]='0'+(R_H%10);
				rec_humidity_dat[2]='.';
				rec_humidity_dat[3]='0'+(R_L/10);//ʪ��С����8λ
				rec_humidity_dat[4]='0'+(R_L%10);
				rec_humidity_dat[5]='R';
				rec_humidity_dat[6]='H';
				
				rec_temperature_dat[0]='0'+(T_H/10);//�¶�������8λ��
        rec_temperature_dat[1]='0'+(T_H%10);
				rec_temperature_dat[2]='.';
				rec_temperature_dat[3]='0'+(T_L/10);
				rec_temperature_dat[4]='0'+(T_L%10);//�¶�С����8λ��
				rec_temperature_dat[5]='C';
        }   
    }
}
