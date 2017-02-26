#ifndef __NVIC_H
#define __NVIC_H

#include "include.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define LOW             0
#define HIGH            1

#define PFO_GPIO_PIN    GPIO_Pin_13
#define PFO_GPIO_PORT   GPIOE
#define PFO_GPIO_CLK    RCC_AHB1Periph_GPIOE
#define PFO_EXTI_PORT   EXTI_PortSourceGPIOE
#define PFO_EXTI_PIN    EXTI_PinSource13
#define PFO_EXTI_LINE   EXTI_Line13
#define	PFO_IRQn        EXTI15_10_IRQn
#define PFO_EXTI(void)  EXTI15_10_IRQHandler(void)
#define VALUE_PFO       GPIO_ReadInputDataBit(PFO_GPIO_PORT,PFO_GPIO_PIN)
#define ISEFF_PFO()     VALUE_PFO == LOW
#define ISNONEFF_PFO()  VALUE_PFO == HIGH

	 
#define ALA_GPIO_PIN    GPIO_Pin_6
#define ALA_GPIO_PORT   GPIOC
#define ALA_GPIO_CLK    RCC_AHB1Periph_GPIOC
#define ALA_EXTI_PORT   EXTI_PortSourceGPIOC
#define ALA_EXTI_PIN    EXTI_PinSource6
#define ALA_EXTI_LINE   EXTI_Line6
#define	ALA_IRQn        EXTI9_5_IRQn
#define ALA_EXTI(void)  EXTI9_5_IRQHandler(void)
#define VALUE_ALA       GPIO_ReadInputDataBit(PFO_GPIO_PORT,PFO_GPIO_PIN)
#define ISEFF_ALA()     VALUE_ALA == LOW
#define ISNONEFF_ALA()  VALUE_ALA == HIGH
	 
extern void NVIC_Config(void);	 
static void NVIC_ConfigUsart(void);
static void NVIC_ConfigDma(void);
static void NVIC_ConfigExit(void);
static void NVIC_ConfigPFO(void);
static void NVIC_ConfigALA(void);
static void NVIC_ConfigTIM3(void);
static void NVIC_ConfigTIM4(void);
static void NVIC_ConfigTIM12(void);
static void NVIC_ConfigTIM5(void);
static void NVIC_ConfigTIM13(void);



extern void PFO_EXTI_Config(void);
extern void MOTOR_EXTI_Config(void);
extern void EXTILine0_Config(void);
	 


	 


 
	 
#ifdef __cplusplus
}
#endif

#endif

