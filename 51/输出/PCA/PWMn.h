#ifndef		PWMn_H
#define		PWMn_H

#include	"STC12C5A60S2.h"

//#define		STC12C5201AD					//如果注销，则PCA输出默认使用STC12C5A60S2系列

#define		MAIN_Fosc	11059200L	//定义时钟
                                            //IDLE待机模式
#define		PCA_IDLE_DISABLE	0			//1: MCU在IDLE模式时禁止PCA工作。	0:  MCU在IDLE模式时允许PCA工作。
#define		PCA_SOURCE_SELECT	4			//选择PCA的基准时钟源。
											//0：系统时钟Fosc/12。
											//1：系统时钟Fosc/2。
											//2：定时器0的溢出。
											//3：ECI/P3.4脚的外部时钟输入（最大=Fosc/2）。
											//4：系统时钟Fosc。
											//5：系统时钟Fosc/4。
											//6：系统时钟Fosc/6。
											//7：系统时钟Fosc/8。

//SYSclk/PWM_DUTY=frequency;

typedef struct{
	unsigned int PWM_high;	//定义PWM占空比寄存器，即PWM输出高电平的PCA时钟脉冲个数（占空比写入变量）。
    unsigned int PWM_low;	//定义PWM输出低电平的PCA时钟脉冲个数。
    unsigned int CCAP0_tmp;	//定义CCAP0重装载影射寄存器。
	unsigned int PWM_DUTY;	//定义PWM的周期，数值为PCA所选择的时钟脉冲个数。
	unsigned int PWM_HIGH_MAX;//限制PWM输出的最大占空比。
	unsigned int PWM_HIGH_MIN;//限制PWM输出的最小占空比。
}PWM_Parameter;


/*PCA模块工作模式设定 */
#define PWM_8_NOI 0x42//8位PWM，无中断
#define PWM_8_HIR 0x63//8位PWM，由低变高可产生中断
#define PWM_8_HIF 0x53//8位PWM，由高变低可产生中断
#define PWM_8_HIE 0x73//8位PWM, 边沿触发
#define CAP_16_RI 0x60//16位捕获模式，由CCPN/PCAN的上升沿触发，ECOMn=1;ECCFn=0;
#define CAP_16_FI 0x50//16位捕获模式，由CCPN/PCAN的下升沿触发  ECOMn=1;ECCFn=0;
#define CAP_16_EI 0x70//16位捕获模式，边沿触发  ECOMn=1;ECCFn=0;
#define CAP_16_TI 0x48//16位软件定时器，ECCFn=0;
#define CAP_16_HO 0x4c//16位高速输出，ECCFn=0;

/**********************************************************************************************************/

#ifdef	STC12C5201AD
	sbit  CCP0  = P3^7;	//STC12C5201AD/PWM
	sbit  CCP1  = P3^5;	//STC12C5201AD/PWM

#else
	sbit  CCP0  = P1^3;	//STC12C5A60S2
	sbit  CCP1  = P1^4;	//STC12C5A60S2
#endif

void PWM_Parameter_init(PWM_Parameter*p);
void PWMn_init();
void PWMn_SetHighReg(PWM_Parameter*SetHigh,unsigned int high);

#endif
