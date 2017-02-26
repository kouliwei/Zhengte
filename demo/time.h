#ifndef __TIME_H
#define __TIME_H

#include "include.h"

#ifdef __cplusplus
 extern "C" {
#endif
	 
#define RCC_APB1Periph_ENCODER_TIMER                RCC_APB1Periph_TIM3
#define RCC_AHBPeriph_ENCODER_GPIO                  RCC_AHB1Periph_GPIOA
#define ENCODER_TI1                                 GPIO_Pin_6 
#define ENCODER_TI2                                 GPIO_Pin_7
#define ENCODER_GPIO                                GPIOA
#define ENCODER_TIMER                               TIM3
#define ENCODER_IRQHandler                          TIM3_IRQHandler
#define IS_FOREWARD()                               (ENCODER_TIMER->CR1 & 0x0010) == 0 
#define IS_BACKWARD() 														  (ENCODER_TIMER->CR1 & 0x0010) == 1
	 

	 
	 
	 
	 
static void Timer_GPIO_AF(GPIO_typedef GPIO,uint8_t pin,uint8_t TIMn);	 
static void Time_OC_Config(TIM_TypeDef* TIMn,uint8_t Channel,uint32_t SET_PrescalerValue,uint32_t Period);
static void PWMA_Config(void);
static void PWMB_Config(void);
	 
extern void PWM_Config(void);
	 
extern void Clock_Config(uint16_t time,TIM_TypeDef* TIMn);
extern void Time4_TI1Config(void);
extern void Timer4_ETR_Config(void);
extern void Encoder_Init(void);
	 

	 
//extern void Time1_CapInit(void);	 
extern void SysTick_Configuration(void);
 
	 
#ifdef __cplusplus
}
#endif

#endif

