#ifndef __USER_H
#define __USER_H

#include "include.h"


#ifdef __cplusplus
 extern "C" {
#endif

/***************user DataType******************/
typedef enum 
{
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3
} Led_TypeDef;



typedef enum
{
	GPIO_A = 0,
	GPIO_B = 1,
	GPIO_C = 2,
	GPIO_D = 3,
	GPIO_E = 4,
	GPIO_F = 5,
	GPIO_G = 6,
	GPIO_H = 7,
	GPIO_I = 8
}GPIO_typedef;


typedef enum
{
	D0 = 0,
	D1 = 1,
	D2 = 2,
	D3 = 3,
	D4 = 4,
	D5 = 5,
	D6 = 6,
	D7 = 7,
	D8 = 8,
	D9 = 9,
	D10= 10,
	D11= 11,
	D12= 12,
	D13= 13,
	D14= 14,
	D15= 15
}AD7606_TypeDef;

typedef struct{
    uint8_t num;            //小车编号
    uint8_t pos;            //小车所在的工位位置
    uint8_t opr;            //小车所在的操作台位置
		uint8_t pos1;
}Car;

	 
	 
	 
#ifdef __cplusplus
}
#endif

#endif


