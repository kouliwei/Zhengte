#ifndef __COMMON_H
#define __COMMON_H

#include "include.h"



#ifdef __cplusplus
 extern "C" {
#endif
	 




/**************the definition of LED******************/
//LED1	PB1
//LED2	PB0
//LED3	PC5
//LED4	PC4
	 
	 
#define LEDn                             4
	 

#define LED1_PIN                         GPIO_Pin_1
#define LED1_GPIO_PORT                   GPIOB
#define LED1_GPIO_CLK                    RCC_AHB1Periph_GPIOB  
  
#define LED2_PIN                         GPIO_Pin_0
#define LED2_GPIO_PORT                   GPIOB
#define LED2_GPIO_CLK                    RCC_AHB1Periph_GPIOB  
  
#define LED3_PIN                         GPIO_Pin_5
#define LED3_GPIO_PORT                   GPIOC
#define LED3_GPIO_CLK                    RCC_AHB1Periph_GPIOC

#define LED4_PIN                         GPIO_Pin_4
#define LED4_GPIO_PORT                   GPIOC
#define LED4_GPIO_CLK                    RCC_AHB1Periph_GPIOC


#define GPIOn                            9


/**************the  definition of direction********************/
#define INPUT   1
#define OUTPUT  0

#define EFFECT              0
#define NONEFF              1


/**************the definition of Key**************************/
//KEY1	PE12
//KEY2	PE11
//KEY3	PE10
//KEY4	PE9
#define GPIO_KEY1           GPIO_E
#define Pin_KEY1            12
#define Dir_KEY1            INPUT

#define GPIO_KEY2           GPIO_E
#define Pin_KEY2            11
#define Dir_KEY2            INPUT

#define GPIO_KEY3           GPIO_E
#define Pin_KEY3            10
#define Dir_KEY3            INPUT

#define GPIO_KEY4           GPIO_E
#define Pin_KEY4            9
#define Dir_KEY4            INPUT

#define VAL_KEY1            GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)
#define VAL_KEY2            GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)
#define VAL_KEY3            GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)
#define VAL_KEY4            GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)

#define EFF_VAL_KEY1()      VAL_KEY1 == EFFECT
#define EFF_VAL_KEY2()      VAL_KEY2 == EFFECT
#define EFF_VAL_KEY3()      VAL_KEY3 == EFFECT
#define EFF_VAL_KEY4()      VAL_KEY4 == EFFECT

#define NON_VAL_KEY1()      VAL_KEY1 == NONEFF
#define NON_VAL_KEY2()      VAL_KEY2 == NONEFF
#define NON_VAL_KEY3()      VAL_KEY3 == NONEFF
#define NON_VAL_KEY4()      VAL_KEY4 == NONEFF
/**************the definition of LCD_1602***********************/
#define GPIO_LCD_RS         GPIO_C
#define Pin_LCD_RS          1
#define Dir_LCD_RS          OUTPUT

#define GPIO_LCD_RW         GPIO_C
#define Pin_LCD_RW          2
#define Dir_LCD_RW          OUTPUT
 
#define GPIO_LCD_E          GPIO_C
#define Pin_LCD_E           3
#define Dir_LCD_E           OUTPUT

#define GPIO_LCD_D0         GPIO_A
#define Pin_LCD_D0          1
#define Dir_LCD_D0          OUTPUT

#define GPIO_LCD_D1         GPIO_A
#define Pin_LCD_D1          2
#define Dir_LCD_D1          OUTPUT

#define GPIO_LCD_D2         GPIO_D
#define Pin_LCD_D2          9
#define Dir_LCD_D2          OUTPUT

#define GPIO_LCD_D3         GPIO_D
#define Pin_LCD_D3          8
#define Dir_LCD_D3          OUTPUT

#define GPIO_LCD_D4         GPIO_B
#define Pin_LCD_D4          15
#define Dir_LCD_D4          OUTPUT

#define GPIO_LCD_D5         GPIO_B
#define Pin_LCD_D5          14
#define Dir_LCD_D5          OUTPUT

#define GPIO_LCD_D6         GPIO_B
#define Pin_LCD_D6          13
#define Dir_LCD_D6          OUTPUT

#define GPIO_LCD_D7         GPIO_B
#define Pin_LCD_D7          12
#define Dir_LCD_D7          OUTPUT

#define CLR_LCD_RS()        GPIO_ResetBits(GPIOC,GPIO_Pin_1)
#define SET_LCD_RS()        GPIO_SetBits(GPIOC,GPIO_Pin_1)
#define CLR_LCD_RW()        GPIO_ResetBits(GPIOC,GPIO_Pin_2)
#define SET_LCD_RW()        GPIO_SetBits(GPIOC,GPIO_Pin_2)
#define CLR_LCD_E()         GPIO_ResetBits(GPIOC,GPIO_Pin_3)
#define SET_LCD_E()         GPIO_SetBits(GPIOC,GPIO_Pin_3)
#define CLR_LCD_D0()        GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define SET_LCD_D0()        GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define CLR_LCD_D1()        GPIO_ResetBits(GPIOA,GPIO_Pin_2)
#define SET_LCD_D1()        GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define CLR_LCD_D2()        GPIO_ResetBits(GPIOD,GPIO_Pin_9)
#define SET_LCD_D2()        GPIO_SetBits(GPIOD,GPIO_Pin_9)
#define CLR_LCD_D3()        GPIO_ResetBits(GPIOD,GPIO_Pin_8)
#define SET_LCD_D3()        GPIO_SetBits(GPIOD,GPIO_Pin_8)
#define CLR_LCD_D4()        GPIO_ResetBits(GPIOB,GPIO_Pin_15)
#define SET_LCD_D4()        GPIO_SetBits(GPIOB,GPIO_Pin_15)
#define CLR_LCD_D5()        GPIO_ResetBits(GPIOB,GPIO_Pin_14)
#define SET_LCD_D5()        GPIO_SetBits(GPIOB,GPIO_Pin_14)
#define CLR_LCD_D6()        GPIO_ResetBits(GPIOB,GPIO_Pin_13)
#define SET_LCD_D6()        GPIO_SetBits(GPIOB,GPIO_Pin_13)
#define CLR_LCD_D7()        GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define SET_LCD_D7()        GPIO_SetBits(GPIOB,GPIO_Pin_12)



/**************the definition of senser************************/

//I0	PD1
//I1	PD2
//I2	PD3
//I3	PD4
//I4	PD7
//I5	PB3
//I6	PB4
//I7	PB5
//I8	PB6
//I9	PB7
//I10	PB8
//I11	PB9
//I12	PE0
//I13	PE1
///**********simulating keys*************/
//#define SENSER_EFFECT       1
//#define SENSER_NONEFF       0
/*********PNP bipolar transistor*******/
#define SENSER_EFFECT       0
#define SENSER_NONEFF       1


#define GPIO_SENSER0        GPIO_D
#define Pin_SENSER0         1
#define Dir_SENSER0         INPUT    

#define GPIO_SENSER1        GPIO_D
#define Pin_SENSER1         2
#define Dir_SENSER1         INPUT

#define GPIO_SENSER2        GPIO_D
#define Pin_SENSER2         3
#define Dir_SENSER2         INPUT

#define GPIO_SENSER3        GPIO_D
#define Pin_SENSER3         4
#define Dir_SENSER3         INPUT
     
#define GPIO_SENSER4        GPIO_D
#define Pin_SENSER4         7
#define Dir_SENSER4         INPUT

#define GPIO_SENSER5        GPIO_B
#define Pin_SENSER5         3
#define Dir_SENSER5         INPUT

#define GPIO_SENSER6        GPIO_B
#define Pin_SENSER6         4
#define Dir_SENSER6         INPUT

#define GPIO_SENSER7        GPIO_B
#define Pin_SENSER7         5
#define Dir_SENSER7         INPUT

#define GPIO_SENSER8        GPIO_B
#define Pin_SENSER8         6
#define Dir_SENSER8         INPUT

#define GPIO_SENSER9        GPIO_B
#define Pin_SENSER9         7
#define Dir_SENSER9         INPUT
     
#define GPIO_SENSER10       GPIO_B
#define Pin_SENSER10        8
#define Dir_SENSER10        INPUT

#define GPIO_SENSER11       GPIO_B
#define Pin_SENSER11        9
#define Dir_SENSER11        INPUT

#define GPIO_SENSER12       GPIO_E
#define Pin_SENSER12        0
#define Dir_SENSER12        INPUT

#define GPIO_SENSER13       GPIO_E
#define Pin_SENSER13        1
#define Dir_SENSER13        INPUT




#define VAL_SENSER0         GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)      
#define VAL_SENSER1         GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)
#define VAL_SENSER2         GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)
#define VAL_SENSER3         GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)
#define VAL_SENSER4         GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)
#define VAL_SENSER5         GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)
#define VAL_SENSER6         GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)
#define VAL_SENSER7         GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define VAL_SENSER8         GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define VAL_SENSER9         GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)
#define VAL_SENSER10        GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)
#define VAL_SENSER11        GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)
#define VAL_SENSER12        GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)
#define VAL_SENSER13        GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)



#if     DEBUG == 2
#define EFF_VAL_SENSER0()   ch == '0'
#define EFF_VAL_SENSER1()   ch == '1'
#define EFF_VAL_SENSER2()   ch == '2'
#define EFF_VAL_SENSER3()   ch == '3'
#define EFF_VAL_SENSER4()   ch == '4'
#define EFF_VAL_SENSER5()   ch == '5'
#define EFF_VAL_SENSER6()   ch == '6'
#define EFF_VAL_SENSER7()   ch == '7'

#else
#define EFF_VAL_SENSER0()   VAL_SENSER0 == SENSER_EFFECT
#define EFF_VAL_SENSER1()   VAL_SENSER1 == SENSER_EFFECT
#define EFF_VAL_SENSER2()   VAL_SENSER2 == SENSER_EFFECT
#define EFF_VAL_SENSER3()   VAL_SENSER3 == SENSER_EFFECT
#define EFF_VAL_SENSER4()   VAL_SENSER4 == SENSER_EFFECT
#define EFF_VAL_SENSER5()   VAL_SENSER5 == SENSER_EFFECT
#define EFF_VAL_SENSER6()   VAL_SENSER6 == SENSER_EFFECT
#define EFF_VAL_SENSER7()   VAL_SENSER7 == SENSER_EFFECT
#define EFF_VAL_SENSER8()   VAL_SENSER8 == SENSER_EFFECT
#define EFF_VAL_SENSER9()   VAL_SENSER9 == SENSER_EFFECT
#define EFF_VAL_SENSER10()  VAL_SENSER10== SENSER_EFFECT
#define EFF_VAL_SENSER11()  VAL_SENSER11== SENSER_EFFECT
#define EFF_VAL_SENSER12()  VAL_SENSER12== SENSER_EFFECT
#define EFF_VAL_SENSER13()  VAL_SENSER13== SENSER_EFFECT

#define NON_VAL_SENSER0()   VAL_SENSER0 == SENSER_NONEFF
#define NON_VAL_SENSER1()   VAL_SENSER1 == SENSER_NONEFF
#define NON_VAL_SENSER2()   VAL_SENSER2 == SENSER_NONEFF
#define NON_VAL_SENSER3()   VAL_SENSER3 == SENSER_NONEFF
#define NON_VAL_SENSER4()   VAL_SENSER4 == SENSER_NONEFF
#define NON_VAL_SENSER5()   VAL_SENSER5 == SENSER_NONEFF
#define NON_VAL_SENSER6()   VAL_SENSER6 == SENSER_NONEFF
#define NON_VAL_SENSER7()   VAL_SENSER7 == SENSER_NONEFF
#define NON_VAL_SENSER8()   VAL_SENSER8 == SENSER_NONEFF
#define NON_VAL_SENSER9()   VAL_SENSER9 == SENSER_NONEFF
#define NON_VAL_SENSER10()  VAL_SENSER0 == SENSER_NONEFF
#define NON_VAL_SENSER11()  VAL_SENSER11== SENSER_NONEFF
#define NON_VAL_SENSER12()  VAL_SENSER12== SENSER_NONEFF
#define NON_VAL_SENSER13()  VAL_SENSER13== SENSER_NONEFF
#endif


/****************the definition of WIFI********************/
#define GPIO_LINK           GPIO_E
#define Pin_LINK            3
#define Dir_LINK            INPUT

#define GPIO_READY          GPIO_E
#define Pin_READY           4
#define Dir_READY           INPUT

#define GPIO_D2_RST         GPIO_E
#define Pin_D2_RST          2
#define Dir_D2_RST          OUTPUT

#define VAL_LINK            GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define VAL_READY           GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define NONEFF_VAL_LINK()   VAL_LINK == NONEFF 
#define NONEFF_VAL_READY()  VAL_READY == NONEFF
#define EFF_VAL_READY() 		VAL_READY == EFFECT
#define RST_VAL_RST()       GPIO_ResetBits(GPIOE,GPIO_Pin_2)
#define SET_VAL_RST()       GPIO_SetBits(GPIOE,GPIO_Pin_2)

/****************the definition of Motor*********************/
#define GPIO_MSON           GPIO_D
#define Pin_MSON            0
#define Dir_MSON            OUTPUT

#define GPIO_MARST          GPIO_C         
#define Pin_MARST           12
#define Dir_MARST           OUTPUT

#define GPIO_MOPST          GPIO_A
#define Pin_MOPST           12
#define Dir_MOPST           OUTPUT

#define GPIO_MSRDY          GPIO_D
#define Pin_MSRDY           14
#define Dir_MSRDY           INPUT

#define GPIO_MZSPD          GPIO_D
#define Pin_MZSPD           15
#define Dir_MZSPD           INPUT

#define GPIO_MALRM          GPIO_C
#define Pin_MALRM           6
#define Dir_MALRM           INPUT

#define SET_VAL_MSON()      GPIO_SetBits(GPIOD,GPIO_Pin_0) 				//禁能电机
#define RST_VAL_MSON()      GPIO_ResetBits(GPIOD,GPIO_Pin_0)  		//使能电机
#define SET_VAL_MARST()     GPIO_SetBits(GPIOC,GPIO_Pin_12) 			
#define RST_VAL_MARST()     GPIO_ResetBits(GPIOC,GPIO_Pin_12) 		//伺服报警信号清除
#define SET_VAL_MOPST()     GPIO_SetBits(GPIOA,GPIO_Pin_12) 			
#define RST_VAL_MOPST()     GPIO_ResetBits(GPIOA,GPIO_Pin_12) 		//伺服急停

#define VAL_MSRDY           GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14)
#define VAL_MZSPD           GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)
#define VAL_MALRM           GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)

#define EFF_MSRDY()         VAL_MSRDY == EFFECT     								//伺服备妥
#define NONEFF_MSRDY()      VAL_MSRDY == NONEFF 										//伺服未备妥
#define EFF_MZSPD()         VAL_MZSPD == EFFECT  										//伺服停止输出
#define EFF_MALRM()         VAL_MALRM == EFFECT 										//伺服报警输出

#define GPIO_INIT           GPIO_D
#define Pin_INIT            13
#define Dir_INIT            INPUT

#define VAL_INIT            GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13)
#define EFF_INIT()          VAL_INIT == EFFECT



    
/*****************the definition of Delay*************************/
#define NOP Delay_1us()


/**********全局变量申明****************/



extern GPIO_TypeDef* PORT_GPIO[GPIOn];
extern const uint16_t PIN_GPIO[16];
extern const uint8_t  SOUC_GPIO[16];
extern const uint32_t CLK_GPIO[GPIOn];



/*****flag = 0,GPIO OUT;
******flag = 1,GPIO IN*******/
extern void GPIO_Config(GPIO_typedef GPIO_x,uint8_t pin,uint8_t flag);


/***********initialize the Led and Drive the Led*******************/
extern void Led_Init(Led_TypeDef Led);
static void GPIO_Led_Init(void);
extern void Led_On(Led_TypeDef Led);
extern void Led_Off(Led_TypeDef Led);
extern void Led_Toggle(Led_TypeDef Led);
extern void Led_Drive(uint8_t num);


extern void Delay(__IO uint32_t nCount);
extern void Delay_1ms(void);
extern void Delay_Nms(__IO uint16_t nCount);
extern void Delay_1us(void);
extern void Delay_Nus(__IO uint16_t nCount);



uint16_t My_pow(uint8_t a,uint8_t b);
extern void myiostr(char* str);
extern void float2array(float num,uint8_t* Tx_Buffer);
extern void array2float(float* num,uint8_t* Rx_Buffer);
extern void int2array(uint16_t num,uint8_t* Tx_Buffer);
extern void array2int(uint16_t* num,uint8_t* Rx_Buffer);


static void GPIO_Motor_Init(void);
extern void Wifi_RST(void);
static void GPIO_Wifi_Init(void);
static void GPIO_Key_Init(void);
static void GPIO_Senser_Init(void);
extern void GPIO_All_Init(void);

extern  void Sys_InitConfig(void);

/****************************LCD**********************************/
static void GPIO_LCD_Init(void);
static void IWDG_Init(void);

	 
	 
#ifdef __cplusplus
}
#endif

#endif


