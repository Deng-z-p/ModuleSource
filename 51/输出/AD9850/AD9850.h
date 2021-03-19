#ifndef __AD9850_H
#define __AD9850_H
# include <stc12c5a60s2.h>
# include <stdio.h>
# include <intrins.h>

sbit ad9850_w_clk    =P2^2;  //P2.2口接ad9850的w_clk脚/PIN7
sbit ad9850_fq_up    =P2^1;  //P2.1口接ad9850的fq_up脚/PIN8
sbit ad9850_rest     =P2^0;  //P2.0口接ad9850的rest脚/PIN12
sbit ad9850_bit_data =P1^7;  //P1.7口接ad9850的D7脚/PIN25

void ad9850_reset_serial();
void ad9850_wr_serial(unsigned char w0,double frequence);

#endif 