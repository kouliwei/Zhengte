#include "nvic.h"

extern void  NVIC_Config(void)
{
	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);      //分组
	NVIC_ConfigUsart();
	NVIC_ConfigPFO();
//	NVIC_ConfigALA();
	NVIC_ConfigTIM4();
//	NVIC_ConfigTIM3();
	NVIC_ConfigTIM12();
	NVIC_ConfigTIM5();
	NVIC_ConfigTIM13();
//	NVIC_ConfigDma();
//	NVIC_ConfigExit();
	 
}


extern void PFO_EXTI_Config(void)
{
    EXTI_InitTypeDef   EXTI_InitStructure;
    GPIO_InitTypeDef   GPIO_InitStructure;
    
    /* Enable GPIOA clock */
    RCC_AHB1PeriphClockCmd(PFO_GPIO_CLK, ENABLE);
    /* Enable SYSCFG clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Configure PE13 pin as input floating */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = PFO_GPIO_PIN;
    GPIO_Init(PFO_GPIO_PORT, &GPIO_InitStructure);

  /* Connect EXTI Line13 to PE13 pin */
    SYSCFG_EXTILineConfig(PFO_EXTI_PORT, PFO_EXTI_PIN);

  /* Configure EXTI Line13 */
    EXTI_InitStructure.EXTI_Line = PFO_EXTI_LINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

 
}


extern void MOTOR_EXTI_Config(void)
{

    EXTI_InitTypeDef   EXTI_InitStructure;
    GPIO_InitTypeDef   GPIO_InitStructure;
    
    /* Enable GPIOC clock */
    RCC_AHB1PeriphClockCmd(ALA_GPIO_CLK, ENABLE);
    /* Enable SYSCFG clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Configure PC6 pin as input floating */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = ALA_GPIO_PIN;
    GPIO_Init(ALA_GPIO_PORT, &GPIO_InitStructure);

  /* Connect EXTI Line6 to PC6 pin */
    SYSCFG_EXTILineConfig(ALA_EXTI_PORT, ALA_EXTI_PIN);

  /* Configure EXTI Line6 */
    EXTI_InitStructure.EXTI_Line = ALA_EXTI_LINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}


extern void EXTILine0_Config(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOA clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Configure PA0 pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Connect EXTI Line0 to PA0 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

  /* Configure EXTI Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}



static void NVIC_ConfigExit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;   
	
//	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
//  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
	
	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
}

static void NVIC_ConfigPFO(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;   
    /* Enable and set EXTI Line13 Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = PFO_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
}

static void NVIC_ConfigALA(void) 
{
    NVIC_InitTypeDef NVIC_InitStructure;   
   
    NVIC_InitStructure.NVIC_IRQChannel = ALA_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
}



static void NVIC_ConfigDma(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;   
    NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;    //DMA_Stream0中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         //响应优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //使能
    NVIC_Init(&NVIC_InitStructure);
}

static void NVIC_ConfigUsart(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;    //串口1中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;         //响应优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //使能
    NVIC_Init(&NVIC_InitStructure);
}



static void NVIC_ConfigTIM3(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;  
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;    //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;         //响应优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //使能
    NVIC_Init(&NVIC_InitStructure);
}


static void NVIC_ConfigTIM4(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;    //TIM4中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;         //响应优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //使能
    NVIC_Init(&NVIC_InitStructure);
}

static void NVIC_ConfigTIM5(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;    //TIM4中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;         //响应优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //使能
    NVIC_Init(&NVIC_InitStructure);
}



static void NVIC_ConfigTIM12(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM8_BRK_TIM12_IRQn;    //TIM12中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;         //响应优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //使能
    NVIC_Init(&NVIC_InitStructure);
}


static void NVIC_ConfigTIM13(void)
{
	  NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;    //TIM13中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;         //响应优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //使能
    NVIC_Init(&NVIC_InitStructure);
}

