#include "time.h"

const uint8_t GPIO_AF_TIM[15]  = {0,
	                                GPIO_AF_TIM1, GPIO_AF_TIM2, GPIO_AF_TIM3,
																	GPIO_AF_TIM4, GPIO_AF_TIM5, 0,
																	0,            GPIO_AF_TIM8, GPIO_AF_TIM9,
																	GPIO_AF_TIM10,GPIO_AF_TIM11,GPIO_AF_TIM12,
	                                GPIO_AF_TIM13,GPIO_AF_TIM14
                                 };


//static void Time1_Config(void)
//{
//	uint16_t PrescalerValue  = 0;  
//	GPIO_InitTypeDef GPIO_InitStructure;
//  NVIC_InitTypeDef NVIC_InitStructure;
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
//  
//  /* TIM1 clock enable */
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

//  /* GPIOE clock enable */
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
//	
//	TIM_DeInit(TIM1); 
//  
//  /* TIM1 channel 2 pin (PE.11) configuration */
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_Init(GPIOE, &GPIO_InitStructure);

//  /* Connect TIM pins to AF2 */
//  GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);
//  
//  /* Enable the TIM1 global Interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);

//	/* TIM_TimeBaseStructure  configuration*/
////	PrescalerValue  = (uint16_t)(120000000/20000)-1;  
////	Period=(20000/1000)-1;
////	TIM_TimeBaseStructure.TIM_Period =  Period;                           
////	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue; 
////	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  
////	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
////	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 
//}

//extern void Time1_CapInit(void)
//{
//	TIM_ICInitTypeDef TIM_ICStructure;
//	Time1_Config();
//	
//	TIM_ICStructure.TIM_Channel = TIM_Channel_2;
//	TIM_ICStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
//	TIM_ICStructure.TIM_ICFilter = 0x0;
//	TIM_ICStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
//	TIM_ICStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
//	TIM_ICInit(TIM1,&TIM_ICStructure);
//	

//	
//	TIM_ClearFlag(TIM1,TIM_FLAG_CC2);
//	TIM_ITConfig(TIM1,TIM_IT_CC2,ENABLE);
//	
//	TIM_Cmd(TIM1,ENABLE);
//}


/**
  * @brief  
  * @param  GPIO:select the GPIO_PORT
  * @param  pin:select the GPIO_pins.
	*		  		 This parameter must be a number between 0x00 and 0x0F.
  * @param  TIMn:selects the pin to used as Alternate function.
	*		  		 This parameter can be one of the following values:
  *            @arg 1: Connect TIM1 pins to AF1
  *            @arg 2: Connect TIM2 pins to AF1
  *            @arg 3: Connect TIM3 pins to AF2
  *            @arg 4: Connect TIM4 pins to AF2 
  *            @arg 5: Connect TIM5 pins to AF2
  *            @arg 8: Connect TIM8 pins to AF3
  *            @arg 9: Connect TIM9 pins to AF3 
  *            @arg 10: Connect TIM10 pins to AF3
  *            @arg 11: Connect TIM11 pins to AF3
  *            @arg 12: Connect TIM12 pins to AF9
  *            @arg 13: Connect TIM13 pins to AF9
  *            @arg 14: Connect TIM14 pins to AF9
  *           
  * @retval None
  */


extern void Clock_Config(uint16_t time,TIM_TypeDef* TIMn)  //time :需要定时的毫秒数；TIMn :需要的定时器
{
    uint16_t PrescalerValue = 0;
    uint16_t period = 0;
    uint16_t temp_period[16] = {9999,9999,9999,14999,19999,24999,29999,34999,39999,44999,49999,54999,59999,64999};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
   	if(TIMn == TIM2)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    else if(TIMn == TIM3)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    else if(TIMn == TIM4)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    else if(TIMn == TIM5)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);	
    else if(TIMn == TIM12)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);
    else if(TIMn == TIM13)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);
    else 
    {
        if(TIMn == TIM14)
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);
    }
    
    PrescalerValue = (uint16_t) ((60000000) / 10000) - 1;  //config the input frequency 20K
    if(time < 1000 || time == 1000)
    {
        period = (uint16_t) (10000 / (1000 / time)) - 1;
    }
    else
    {
        if(time < 7000 )
        {
            period =temp_period[time/500];
        }
        else                                              //time 超过设定范围，默认为1s
        {
            period =9999;
        }
    }

    /* Time base configuration */  
    TIM_TimeBaseStructure.TIM_Period =period;                               
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_TimeBaseInit(TIMn, &TIM_TimeBaseStructure); 
    
    TIM_ClearFlag(TIMn,TIM_FLAG_Update);
    TIM_ITConfig(TIMn,TIM_IT_Update,DISABLE);
    
    TIM_ARRPreloadConfig(TIMn, ENABLE);  //自动重装载寄存器 
		TIM_Cmd(TIMn,DISABLE);
}





static void Timer_GPIO_AF(GPIO_typedef GPIO,uint8_t pin,uint8_t TIMn)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/**************GPIO clock enable**********/
  RCC_AHB1PeriphClockCmd(CLK_GPIO[GPIO],ENABLE);
	
	/**************GPIO Configuration**********/
	GPIO_InitStructure.GPIO_Pin=PIN_GPIO[pin];
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(PORT_GPIO[GPIO],&GPIO_InitStructure);
	GPIO_PinAFConfig(PORT_GPIO[GPIO], SOUC_GPIO[pin], GPIO_AF_TIM[TIMn]);
}


/**
  * @brief  Configurate TIM3.CH2 as PWMOUT
  * @param  SET_PrescalerValue:Specifies the prescaler value used to divide the TIM clock.
            This parameter can be a number between 0x0000 and 0xFFFF 
  * @param  Period:Specifies the period value to be loaded into the active
            Auto-Reload Register at the next update event
						This parameter must be a number between 0x0000 and 0xFFFF.
  * @retval None
  */



static void Timer_OC_Config(TIM_TypeDef* TIMn,uint8_t Channel,uint32_t SET_PrescalerValue,uint32_t Period)
{
	uint16_t CCR_Val = 0;
	uint16_t PrescalerValue = 0;
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	if(TIMn == TIM2)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	else if(TIMn == TIM3)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	else if(TIMn == TIM4)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	else if(TIMn == TIM5)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);	
	else if(TIMn == TIM12)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);
	else if(TIMn == TIM13)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);
	else 
	{
		if(TIMn == TIM14)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);
	}
	
	
//	TIM_DeInit(TIMn); 
	if(CCR_Val < Period)
	{
	
		/* Compute the prescaler value */  
		
		PrescalerValue = (uint16_t) ((60000000) / SET_PrescalerValue) - 1;  //config the input frequency 20K
	 
		/* Time base configuration */  
		TIM_TimeBaseStructure.TIM_Period =Period;                               
		TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
		TIM_TimeBaseInit(TIMn, &TIM_TimeBaseStructure); 
//		
//	  TIM_ClearFlag(TIMn,TIM_FLAG_Update);
//	  TIM_ITConfig(TIMn,TIM_IT_Update,ENABLE);
		

		/* PWM1 Mode configuration: Channel2 */
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = CCR_Val;                              //CCR的值，设置占空比
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

		if(Channel == 1)
		{
			TIM_OC1Init(TIMn, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIMn, TIM_OCPreload_Enable);
		}
		else if(Channel == 2)
		{
			TIM_OC2Init(TIMn, &TIM_OCInitStructure);
			TIM_OC2PreloadConfig(TIMn, TIM_OCPreload_Enable);
		}
		else if(Channel == 3)
		{
			TIM_OC3Init(TIMn, &TIM_OCInitStructure);
			TIM_OC3PreloadConfig(TIMn, TIM_OCPreload_Enable);
		}
		else
		{
			if(Channel == 4)
			{
				TIM_OC4Init(TIMn, &TIM_OCInitStructure);
				TIM_OC4PreloadConfig(TIMn, TIM_OCPreload_Enable);
			}
		}
		
		TIM_ARRPreloadConfig(TIMn, ENABLE);  //自动重装载寄存器
		TIM_Cmd(TIMn, ENABLE);  
	}
}

/**
  * @brief  output the PWM
  * @param  None
  * @retval None
  */

static void PWMA_Config(void)
{

	Timer_GPIO_AF(GPIO_A,3,2);   //PA.3  ----  TIM2-CH4
	Timer_OC_Config(TIM2,4,60000000,59999);

}
static void PWMB_Config(void)
{
	Timer_GPIO_AF(GPIO_B,10,2);   //PB.10  ----  TIM2-CH3
	Timer_OC_Config(TIM2,3,60000000,59999);

}

extern void PWM_Config(void)
{
	PWMA_Config();
	PWMB_Config();
}



void Time4_TI1Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TIM_DeInit(TIM4);
	
	TIM_TimeBaseStructure.TIM_Period =10;                               
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 

	TIM_TIxExternalClockConfig(TIM4,TIM_TIxExternalCLK1Source_TI1,TIM_ICPolarity_Rising,0);

	TIM_ClearFlag(TIM4,TIM_IT_Update);
  TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	
	TIM_ClearFlag(TIM4,TIM_IT_Trigger);
  TIM_ITConfig(TIM4,TIM_IT_Trigger,ENABLE);
	
	TIM_Cmd(TIM4, ENABLE); 
	
}


void Timer4_ETR_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TIM_DeInit(TIM4);
	
	TIM_TimeBaseStructure.TIM_Period =10;                               
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 

  TIM_ETRClockMode1Config(TIM4,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_Inverted,0);

	TIM_ClearFlag(TIM4,TIM_IT_Update);
  TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	
	TIM_ClearFlag(TIM4,TIM_IT_Trigger);
  TIM_ITConfig(TIM4,TIM_IT_Trigger,ENABLE);
	
	TIM_Cmd(TIM4, ENABLE); 
	
}



extern void Encoder_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
	TIM_ICInitTypeDef TIM_ICInitStructure;
	Timer_GPIO_AF(GPIO_A,6,3);
	Timer_GPIO_AF(GPIO_A,7,3);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ENCODER_TIMER, ENABLE);             //TIM3
	TIM_DeInit(ENCODER_TIMER);              
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);    
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;   
	TIM_TimeBaseStructure.TIM_Period = 60000;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(ENCODER_TIMER, &TIM_TimeBaseStructure); 
	TIM_EncoderInterfaceConfig(ENCODER_TIMER,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); 
	
	TIM_ICStructInit(&TIM_ICInitStructure);    
	TIM_ICInitStructure.TIM_ICFilter = 6; 
	TIM_ICInit(ENCODER_TIMER, &TIM_ICInitStructure);  
	TIM_ClearFlag(ENCODER_TIMER, TIM_FLAG_Update);
	TIM_ITConfig(ENCODER_TIMER, TIM_IT_Update, ENABLE); 	
	TIM_SetCounter(ENCODER_TIMER,0);
	TIM_Cmd(ENCODER_TIMER, ENABLE); 
}








extern void SysTick_Configuration(void)
{
  /* SysTick interrupt each 250 ms */
  if (SysTick_Config((SystemCoreClock/8) /4))
  { 
    /* Capture error */ 
    while (1);
  }

  /* Select AHB clock(HCLK) divided by 8 as SysTick clock source */
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);

  /* Set SysTick Preemption Priority to 1 */    //默认分组为0，故0100，代表抢占式优先级为1，响应式优先级为0
  NVIC_SetPriority(SysTick_IRQn, 0x04);
}



