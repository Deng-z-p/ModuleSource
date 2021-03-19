#include "ineeprom.h"
     
void delay_ms_(uint i)
{
  uint j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}
void DelayNus(uint t)
{
	uint d=0;
	d=t;
	do
	{
	  NOP();
	}while(--d >0); 
}

void EEPROMEnable(void)
{
	ISP_CONTR=ENABLE_IAP;//ʹ�ܲ����úõȴ�ʱ��
}

void EEPROMDisable(void)
{
    ISP_CONTR=0x00;  //��ֹEEPROM
    ISP_CMD=0x00;    //��ISP����
    ISP_TRIG=0x00;   //����
    ISP_ADDRH=0x00;  //����
    ISP_ADDRL=0x00;  //����
}

/****************************************************
* ��������: EEPROMSetAddress
* ��    ��: addr 16λ��ַ
* ��    ��: ��
* ��������: EEPROM ���ö�д��ַ����Ե�ַ��
*****************************************************/
void EEPROMSetAddress(uint addr)
{
    addr+=ADDRESS; //��ʼ����ַΪ0x0000
    ISP_ADDRH=(uchar)(addr>>8); //���ö�д��ַ���ֽ�
    ISP_ADDRL=(uchar) addr;      //���ö�д��ַ���ֽ�
}

/****************************************************
* ��������: EEPROMStart
* ��    ��: ��
* ��    ��: ��
* ��������: EEPROM ����
*****************************************************/
void EEPROMStart(void)
{
    ISP_TRIG=0x46; //����д��0x46
    ISP_TRIG=0xB9; //Ȼ��д��0xB9
}
/****************************************************
* ��������: EEPROMReadByte
* ��    ��: addr 16λ ��ַ
* ��    ��: �����ֽ�
* ��������: EEPROM ��ȡ�����ֽ�
*****************************************************/
uchar EEPROMReadByte(uint addr)
{
    ISP_DATA=0x00;              //���ISP_DATA
    ISP_CMD=0x01;               //��ģʽ
    
    EEPROMEnable();             //EEPROMʹ��
    EEPROMSetAddress(addr);     //����EEPROM��ַ
    EEPROMStart();              //EEPROM����
    DelayNus(30);               //��ȡһ���ֽ�Ҫ10us
    EEPROMDisable();            //��ֹEEPROM

    return (ISP_DATA);          //���ض�ȡ��������
}
/****************************************************
* ��������: EEPROMWriteByte
* ��    ��: addr 16λ ��ַ
byte �����ֽ�
* ��    ��: ��
* ��������: EEPROM д�뵥���ֽ�
*****************************************************/
void EEPROMWriteByte(uint addr,uchar byte)
{
    EEPROMEnable();           //EERPOMʹ��
    ISP_CMD=0x02;             //дģʽ
    
    EEPROMSetAddress(addr);  //����EEPROM��ַ
    ISP_DATA=byte;            //д������
    EEPROMStart();            //EEPROM����
    DelayNus(80);             //дһ���ֽ���Ҫ60us
    EEPROMDisable();          //��ֹEEPROM
} 
/****************************************************
* ��������: EEPROMSectorErase
* ��    ��: addr 16λ ��ַ
* ��    ��: ��
* ��������: EEPROM ��������
*****************************************************/
void EEPROMSectorErase(uint addr)
{
    ISP_CMD=0x03;            //��������ģʽ
    
    EEPROMEnable();          //EEPROMʹ��
    EEPROMSetAddress(addr);//����EEPROM��ַ
    EEPROMStart();           //EEPROM����
    delay_ms_(10);             //����һ������Ҫ10ms
    EEPROMDisable();         //��ֹEEPROM
}

//main()
//{
//	uchar a,b;
//	a=0;
// 	b=0;

//	EEPROMWriteByte(0x00,0x01);
//	EEPROMWriteByte(0x01,0x02);
//	EEPROMWriteByte(0x02,0x03);
//	EEPROMWriteByte(0x03,0x04);
//	while(1)
//	{
//		a = EEPROMReadByte(b);
//		P1 = a;
//		b++;
//		delay_ms(500); 	
//	}
//}








