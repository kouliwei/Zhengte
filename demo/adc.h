#ifndef __ADC_H
#define __ADC_H

#include "include.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define ADC3_DR_ADDRESS   (uint32_t)0x4001224C
	 
#define ADC2_DR_ADDRESS   (uint32_t)0x4001214C  
	 
#define ADC1_DR_ADDRESS   (uint32_t)0x4001204C  
	 
	 



#define AD7606_CVT_H()  GPIOD->BSRRL = GPIO_Pin_4
#define AD7606_CVT_L()  GPIOD->BSRRH = GPIO_Pin_4
#define AD7606_OS0_H()  GPIOD->BSRRL = GPIO_Pin_7
#define AD7606_OS0_L()  GPIOD->BSRRH = GPIO_Pin_7
#define AD7606_OS1_H()  GPIOD->BSRRL = GPIO_Pin_6
#define AD7606_OS1_L()  GPIOD->BSRRH = GPIO_Pin_6
#define AD7606_OS2_H()  GPIOD->BSRRL = GPIO_Pin_5
#define AD7606_OS2_L()  GPIOD->BSRRH = GPIO_Pin_5
#define AD7606_CS_H()   GPIOD->BSRRL = GPIO_Pin_1
#define AD7606_CS_L()   GPIOD->BSRRH = GPIO_Pin_1
#define AD7606_RD_H()   GPIOD->BSRRL = GPIO_Pin_2
#define AD7606_RD_L()   GPIOD->BSRRH = GPIO_Pin_2
#define AD7606_RST_H()  GPIOD->BSRRL = GPIO_Pin_3
#define AD7606_RST_L()  GPIOD->BSRRH = GPIO_Pin_3
#define BUSY            GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)
#define FRST            GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)




#define BUSY_CLK                          RCC_AHB1Periph_GPIOD         
#define BUSY_PIN                          GPIO_Pin_0
#define BUSY_PORT                         GPIOD
#define BUSY_EXTIPORTSOURCE               EXTI_PortSourceGPIOD
#define BUSY_EXTIPINSOURCE                EXTI_PinSource0
#define BUSY_EXTILINE                     EXTI_Line0
#define BUSY_IRQHandler                   EXTI0_IRQHandler


	 
	 



extern __IO uint16_t ADC3ConvertedValue;
extern __IO float MUL_ADC3ConvertedVoltage[2];	 

extern __IO uint16_t MUL_ADC3ConvertedValue[2];


/*********AD7606 配置*************/
static void AD7606_Config(void);
extern void AD7606_Init(void);
static void AD7606_ReadData(uint16_t* data);
static void AD7606_BUSY_EXTI(void);
extern void AD7606_START(void);
extern void AD7606_Read(void);



	 
/***********单通道ADC DMA转换*************/	 	 

extern void ADC3_CH7_DMA_Config(void);	
extern float Voltage_Measure(void);	 	 

	 
/**********多通道ADC   DMA转换******************/ 
extern void MUL_ADC3_DMA(uint8_t num);	
extern void MUL_ADC3(void);


/***********定时ADC DMA转换*********************/

extern void ADC3_DMA_TIMConfig(void);




	 
	
	 
#ifdef __cplusplus
}
#endif

#endif

