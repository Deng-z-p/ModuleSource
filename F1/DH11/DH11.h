#ifndef __DH11_H_
#define __DH11_H_
#include "main.h"

#define GPIOx_DHT11           GPIOB
#define GPIOx_PIN_DHT11       GPIO_PIN_9
#define GPIOx_PIN_Number      9

/**
 * @brief IO direction setting
 * @note  only GPIOx8~15 can be configured, if you want to configure GPIOx0~7,Change CRH to CRL,
 *        and remove "8" in (GPIOx_PIN_Number-8)
 */ 
#define DHT11_IO_IN()   {GPIOx_DHT11->CRH &= ~(0X0F<<(GPIOx_PIN_Number-8)*4);\
                         GPIOx_DHT11->CRH |= 8<<(GPIOx_PIN_Number-8)*4;}
#define DHT11_IO_OUT()  {GPIOx_DHT11->CRH &= ~(0X0F<<(GPIOx_PIN_Number-8)*4);\
                         GPIOx_DHT11->CRH |= 3<<(GPIOx_PIN_Number-8)*4;}
 
/**
 * @brief IO operation function ,pull up or down
 */ 										   
#define DHT11_DQ_OUT_H()  HAL_GPIO_WritePin(GPIOx_DHT11,GPIOx_PIN_DHT11,GPIO_PIN_SET)
#define DHT11_DQ_OUT_L()  HAL_GPIO_WritePin(GPIOx_DHT11,GPIOx_PIN_DHT11,GPIO_PIN_RESET)

/**
 * @brief Read IO definition
 */ 
#define DHT11_DQ_IN     HAL_GPIO_ReadPin(GPIOx_DHT11,GPIOx_PIN_DHT11)
   	
uint8_t DHT11_Init(void);
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi) ; 
uint8_t DHT11_Check(void);

#endif
