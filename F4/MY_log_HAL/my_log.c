#include <stdarg.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "usart.h"
#include "my_log.h"
s8 string[500];       
s32 mcu_uart_write (u8 uart_x ,u8 *buf, s32 len);

//extern int vsprintf(char * s, const char * format, __va_list arg);
/**
 *@brief:     uart_printf
 *@details:   Format and output debugging information from the serial port
 *@param      uart_x:Select the UARTX to be output
 *            @arg 1:UART1
 *            @arg 2:UART2
 *            @arg 3:UART3
 *@param      s8 *fmt  
 *@retval:    None 
 */
void My_Pri_log_x(u8 uart_x,s8 *fmt,...)
{
	s32 length = 0;
    va_list ap;
    s8 *pt;
		
    if(!MY_LOG_ON)
    return;    
		
    va_start(ap,fmt);
    vsprintf((char *)string,(const char *)fmt,ap);
    pt = &string[0];
    while(*pt!='\0')
    {
        length++;
        pt++;
    }

    mcu_uart_write(uart_x,(u8*)&string[0], length);  //Write serial port
    va_end(ap);
}


/**
 *@brief:    mcu_uart_write
 *@details:  Write serial data
 *@param    uart_x:Select the UARTX to be output
 *            @arg 1:UART1
 *            @arg 2:UART2
 *            @arg 3:UART3
 *@param      u8 *buf      
 *@param      s32 len      
 *@retval:    None 
 */
s32 mcu_uart_write (u8 uart_x,u8 *buf, s32 len)
{
    u32 t;
    UART_HandleTypeDef *UART_Handle;
    if (len <= 0) 
        return(-1);      
    if(buf == NULL) 
        return(-1);
    if(uart_x==1)
      UART_Handle=&UART1_Handler;
    else if(uart_x == 2)
      UART_Handle=&UART2_Handler;
    else if(uart_x == 3)
      UART_Handle=&UART3_Handler;

    while(__HAL_UART_GET_FLAG(UART_Handle, USART_FLAG_TXE) == RESET)
    {
        if(t++ >= 0x1000000)//Timeout
            return(-1);
    }  
    HAL_UART_Transmit(UART_Handle,buf,len,1000);
    return(0);
}


