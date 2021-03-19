#ifndef __JQ8900_H
#define __JQ8900_H
#include "reg52.h"
#include "intrins.h"

sbit sda=P0^0;//JQ8900????
/**/
void voice_dispose(unsigned char dat1,unsigned char dat2);

#endif