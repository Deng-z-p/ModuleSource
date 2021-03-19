#include "dh11.h"

/**
 * @brief Reset DHT11
 */ 
void DHT11_Rst(void)	   
{                 
	DHT11_IO_OUT(); 	//Set as output
	DHT11_DQ_OUT_L(); 	//Pull down DQ
	delay_ms(20);    	//Put down at least 18ms
	DHT11_DQ_OUT_H(); 	//DQ=1 
	delay_us(30);     //The host is pulled up 20~40us
}


/**
 * @brief Check if DHT11 exists
 * @retval 1:does not exist
 *         0:Exist
 */ 
uint8_t DHT11_Check(void) 	   
{   
	uint8_t retry=0;
	DHT11_IO_IN();      //Set as input	 
	while (DHT11_DQ_IN && retry<100)//DHT11 will pull down 40~80us
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
	while (!DHT11_DQ_IN && retry<100)//After DHT11 is pulled down, it will be pulled up again by 40~80us
	{
		retry++;
		delay_us(1);
		
	};
	if(retry>=100)return 1;	    
	return 0;
}


/**
 * @brief Read a bit from DHT11
 * @retval Value 0/1
 */ 
uint8_t DHT11_Read_Bit(void) 			 
{
 	uint8_t retry=0;
	while(DHT11_DQ_IN && retry<100)//Wait to go low
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT11_DQ_IN && retry<100)//Wait for high level
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);//Wait for 40us��If it is still high, this bit is 1, otherwise it is 0
	if(DHT11_DQ_IN)return 1;
	else return 0;		   
}


/**
 * @brief Read a byte from DHT11
 * @retval Data read
 */ 
uint8_t DHT11_Read_Byte(void)    
{        
	uint8_t i,dat;
	dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit();
    }						    
    return dat;
}


/**
 * @brief Read four bytes of data from DHT11
 * @param temp:Pointer to temperature integer
 * @param humi:Pointer to Humidity integer
 * @retval 0:Read successfully
 *         1:Read failed
 */ 
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi)    
{        
 	uint8_t buf[5];
	uint8_t i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humi=buf[0];
			*temp=buf[2];
		}
	}else return 1;
	return 0;	    
}


/**
 * @brief Initialize the IO part of DHT11,Simultaneous detection of the presence of DHT11
 * @note attention to the enabled clock
 * @retval 0:DHTII exists
 *         1:DHTII is not exists
 */ 
uint8_t DHT11_Init(void)
{
  GPIO_InitTypeDef GPIO_Initure;
  __HAL_RCC_GPIOB_CLK_ENABLE();			   

  GPIO_Initure.Pin=GPIOx_PIN_DHT11;           	
  GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  
  GPIO_Initure.Pull=GPIO_PULLUP;         
  GPIO_Initure.Speed=GPIO_SPEED_HIGH;     
  HAL_GPIO_Init(GPIOx_DHT11,&GPIO_Initure);     

  DHT11_Rst();
  return DHT11_Check();
}
