#ifndef _MY_LOG_H_
#define _MY_LOG_H_
#define MY_LOG_ON 1 //Allow serial port printing
#define My_pri_ERROR()  My_Pri_log_x(1,"Error:%S  %d\r\n",__FILE__,__LINE__);

void My_Pri_log_x(u8 uart_x,s8 *fmt,...);

#endif
