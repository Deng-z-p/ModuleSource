#ifndef		_config_h
#define		_config_h	

#include "stc12c5a60s2.h"

//#define MAIN_Fosc		22118400L	//������ʱ��	����0������600~115200
//#define MAIN_Fosc		33177600L	//������ʱ��	����0������300~57600
#define MAIN_Fosc		11059200L	//������ʱ��	����0������300~57600
//#define MAIN_Fosc		18432000L	//������ʱ��	����0������600~19200
//#define MAIN_Fosc		24000000L	//������ʱ��	����0������600~115200
//#define MAIN_Fosc		12000000L	//������ʱ��	����0������300~4800



#define T_MS   50                            //��ʱʱ�䳣������λms
#define T1TMS    (T_MS*MAIN_Fosc/1000)       //1Tģʽ��  
#define T12TMS   (T_MS*MAIN_Fosc/1000/12)    //12Tģʽ��



#define Baudrate1		9600		//define the baudrate,
									//12T mode: 600~115200 for 22.1184MHZ, 300~57600 for 11.0592MHZ
									//1T  mode: 7200~1382400 for 22.1184MHZ, 3600~691200 for 11.0592MHZ
#define Baudrate2		9600		//define the baudrate2,
									//12T mode: 600~115200 for 22.1184MHZ, 300~57600 for 11.0592MHZ

/****************** �������Զ����ɣ��û������޸� ************************************/

#define T1_TimerReload	(256 - MAIN_Fosc / 192 / Baudrate1)		//Calculate the timer1 reload value	at 12T mode
#define BRT_Reload		(256 - MAIN_Fosc /16 / Baudrate2)		//Calculate BRT reload value 1T
#define BRT_Reload		(256 - MAIN_Fosc / 12 / 16 / Baudrate2)	//Calculate BRT reload value 12T

/***********************************************************/

#define	uchar	unsigned char
#define uint	unsigned int
#define ulong	unsigned long


#endif
