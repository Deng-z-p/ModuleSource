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
	ISP_CONTR=ENABLE_IAP;//使能并设置好等待时间
}

void EEPROMDisable(void)
{
    ISP_CONTR=0x00;  //禁止EEPROM
    ISP_CMD=0x00;    //无ISP操作
    ISP_TRIG=0x00;   //清零
    ISP_ADDRH=0x00;  //清零
    ISP_ADDRL=0x00;  //清零
}

/****************************************************
* 函数名称: EEPROMSetAddress
* 输    入: addr 16位地址
* 输    出: 无
* 功能描述: EEPROM 设置读写地址（相对地址）
*****************************************************/
void EEPROMSetAddress(uint addr)
{
    addr+=ADDRESS; //初始化地址为0x0000
    ISP_ADDRH=(uchar)(addr>>8); //设置读写地址高字节
    ISP_ADDRL=(uchar) addr;      //设置读写地址低字节
}

/****************************************************
* 函数名称: EEPROMStart
* 输    入: 无
* 输    出: 无
* 功能描述: EEPROM 启动
*****************************************************/
void EEPROMStart(void)
{
    ISP_TRIG=0x46; //首先写入0x46
    ISP_TRIG=0xB9; //然后写入0xB9
}
/****************************************************
* 函数名称: EEPROMReadByte
* 输    入: addr 16位 地址
* 输    出: 单个字节
* 功能描述: EEPROM 读取单个字节
*****************************************************/
uchar EEPROMReadByte(uint addr)
{
    ISP_DATA=0x00;              //清空ISP_DATA
    ISP_CMD=0x01;               //读模式
    
    EEPROMEnable();             //EEPROM使能
    EEPROMSetAddress(addr);     //设置EEPROM地址
    EEPROMStart();              //EEPROM启动
    DelayNus(30);               //读取一个字节要10us
    EEPROMDisable();            //禁止EEPROM

    return (ISP_DATA);          //返回读取到的数据
}
/****************************************************
* 函数名称: EEPROMWriteByte
* 输    入: addr 16位 地址
byte 单个字节
* 输    出: 无
* 功能描述: EEPROM 写入单个字节
*****************************************************/
void EEPROMWriteByte(uint addr,uchar byte)
{
    EEPROMEnable();           //EERPOM使能
    ISP_CMD=0x02;             //写模式
    
    EEPROMSetAddress(addr);  //设置EEPROM地址
    ISP_DATA=byte;            //写入数据
    EEPROMStart();            //EEPROM启动
    DelayNus(80);             //写一个字节需要60us
    EEPROMDisable();          //禁止EEPROM
} 
/****************************************************
* 函数名称: EEPROMSectorErase
* 输    入: addr 16位 地址
* 输    出: 无
* 功能描述: EEPROM 扇区擦除
*****************************************************/
void EEPROMSectorErase(uint addr)
{
    ISP_CMD=0x03;            //扇区擦除模式
    
    EEPROMEnable();          //EEPROM使能
    EEPROMSetAddress(addr);//设置EEPROM地址
    EEPROMStart();           //EEPROM启动
    delay_ms_(10);             //擦除一个扇区要10ms
    EEPROMDisable();         //禁止EEPROM
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








