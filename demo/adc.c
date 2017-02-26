#include "adc.h"


__IO uint16_t ADC3ConvertedValue = 0;
__IO float ADC3ConvertedVoltage = 0;

__IO uint16_t ADC2ConvertedValue = 0;
__IO float ADC2ConvertedVoltage = 0;
uint16_t AD_Buffer[4] = {0};


__IO uint16_t MUL_ADC3ConvertedValue[2]={0,0};
__IO float MUL_ADC3ConvertedVoltage[2]={0,0};


extern void ADC3_CH7_DMA_Config(void)
{
	GPIO_InitTypeDef       GPIO_InitStructure;
	ADC_InitTypeDef        ADC_InitStructure;
	ADC_CommonInitTypeDef  ADC_CommonInitStructure;
	DMA_InitTypeDef        DMA_InitStructure;
	
	/***********enable GPIOF ,DMA2  and ADC3  clock*************/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOF, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
	
	
  /***********DMA    configuration  ********************/
	DMA_InitStructure.DMA_Channel = DMA_Channel_2;
	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t)ADC3_DR_ADDRESS;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC3ConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0,&DMA_InitStructure);
  DMA_Cmd(DMA2_Stream0,ENABLE);
	
		
	/***********GPIO  configuration**************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	
		/***********ADC_Common  configuration********************/
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	
	
	/***********ADC    configuration    ********************/

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC3,&ADC_InitStructure);

	
	ADC_RegularChannelConfig(ADC3,ADC_Channel_7,1,ADC_SampleTime_3Cycles);
	
	ADC_DMARequestAfterLastTransferCmd(ADC3,ENABLE);
	
	ADC_DMACmd(ADC3,ENABLE);
	
	ADC_Cmd(ADC3,ENABLE);
	
	ADC_SoftwareStartConv(ADC3);		
}

extern float Voltage_Measure(void)
{

  ADC3ConvertedVoltage = (float)ADC3ConvertedValue *3.3/0xFFF;
	return ADC3ConvertedVoltage;
}

extern void MUL_ADC3_DMA(uint8_t num)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
	
	
	
	DMA_InitStructure.DMA_Channel = DMA_Channel_2;
	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t)ADC3_DR_ADDRESS;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&MUL_ADC3ConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = num;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0,&DMA_InitStructure);
  DMA_Cmd(DMA2_Stream0,ENABLE);
}

extern void MUL_ADC3(void)
{
	GPIO_InitTypeDef       GPIO_InitStructure;
	ADC_InitTypeDef        ADC_InitStructure;
	ADC_CommonInitTypeDef  ADC_CommonInitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOF, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
	
	
		
	/***********GPIO  PA2configuration**************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	/***********GPIO  PF9configuration**************/
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	
	
	
	/***********ADC_Common  configuration********************/
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	
	
	/***********ADC    configuration    ********************/

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 2;
	ADC_Init(ADC3,&ADC_InitStructure);

	
	ADC_RegularChannelConfig(ADC3,ADC_Channel_7,1,ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC3,ADC_Channel_2,2,ADC_SampleTime_3Cycles);

	
	ADC_DMARequestAfterLastTransferCmd(ADC3,ENABLE);
	
	ADC_DMACmd(ADC3,ENABLE);
	
	ADC_Cmd(ADC3,ENABLE);
	
	ADC_SoftwareStartConv(ADC3);		
	
}
extern void ADC3_DMA_TIMConfig(void)
{
	GPIO_InitTypeDef       GPIO_InitStructure;
	ADC_InitTypeDef        ADC_InitStructure;
	ADC_CommonInitTypeDef  ADC_CommonInitStructure;
	DMA_InitTypeDef        DMA_InitStructure;
	
	/***********enable GPIOF ,DMA2  and ADC3  clock*************/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOF, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
	
	
  /***********DMA    configuration  ********************/
	DMA_InitStructure.DMA_Channel = DMA_Channel_2;
	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t)ADC3_DR_ADDRESS;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC3ConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0,&DMA_InitStructure);
	
	
//	DMA_ClearITPendingBit(DMA2_Stream0,DMA_FLAG_TCIF2);
	DMA_ITConfig(DMA2_Stream0,DMA_IT_TC,ENABLE);
  DMA_Cmd(DMA2_Stream0,ENABLE);
	
		
	/***********GPIO  configuration**************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	
		/***********ADC_Common  configuration********************/
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	
	
	/***********ADC    configuration    ********************/

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_CC1;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC3,&ADC_InitStructure);

	
	ADC_RegularChannelConfig(ADC3,ADC_Channel_7,1,ADC_SampleTime_3Cycles);
	
	ADC_DMARequestAfterLastTransferCmd(ADC3,ENABLE);
	
	ADC_DMACmd(ADC3,ENABLE);
	
	ADC_Cmd(ADC3,ENABLE);
	
	//ADC_SoftwareStartConv(ADC3);		
}





/****************AD7606/AD7607芯片使用说明：
(1)调用AD7606_Init(void)函数进行AD相关的初始化，包括以下三个方面
1.AD7606_Config(void):和STM32相关的引脚配置
2.AD7606_BUSY_EXTI(void):和外部中断相关的配置
3.AD控制引脚的初始化以及复位操作
(2)调用AD7606_START(void)函数进行AD转换的启动
(3)调用AD7606_ReadData(uint16_t* data)函数进行AD转换后数字量的读取********/


extern void AD7606_Init(void)
{
	AD7606_Config();    //AD7606的引脚配置，包括data[15:0]和CS/RD/CVT/BUSY/RST/FRST/OS0/OS1/OS2等的配置
	AD7606_BUSY_EXTI(); /****AD7606转化完成时中断引脚的配置，BUSY引脚在转换完成时产生
	                   下降沿中断，MCU在中断服务子程序中读取AD值************/
	
	
	
	Delay_1ms();
	AD7606_RST_L();
	AD7606_CS_H();
    AD7606_CVT_L();
	AD7606_OS0_L();
	AD7606_OS1_L();
	AD7606_OS2_L();
	AD7606_RD_H();
	Delay_1ms();
	
	/******AD7606  RESET**************/
	AD7606_RST_H();
	Delay_1us();
	AD7606_RST_L();
	Delay_1us();
	
}

extern void AD7606_START(void)
{
	AD7606_CVT_L();
	Delay_1us();
	AD7606_CVT_H();   //转换开始
	Delay_1us();
	

}



static void AD7606_BUSY_EXTI(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOA clock */
  RCC_AHB1PeriphClockCmd(BUSY_CLK, ENABLE);
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Configure PD0 pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = BUSY_PIN;
  GPIO_Init(BUSY_PORT, &GPIO_InitStructure);

  /* Connect EXTI Line0 to PD0 pin */
  SYSCFG_EXTILineConfig(BUSY_EXTIPORTSOURCE, BUSY_EXTIPINSOURCE);

  /* Configure EXTI Line0 */
	EXTI_ClearFlag(BUSY_EXTILINE);
  EXTI_InitStructure.EXTI_Line = BUSY_EXTILINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	EXTI_ClearFlag(BUSY_EXTILINE);
	
}

extern void AD7606_Read(void)
{
	uint8_t i=0;
	AD7606_CS_L();
	Delay_1us();
	for(i=0;i<8;i++)
	{
		AD7606_RD_L();
		Delay_1us();
		AD7606_ReadData(&AD_Buffer[i]);
		AD7606_RD_H();
		Delay_1us();
	}
	AD7606_CS_H();
}

static void AD7606_ReadData(uint16_t* data)
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15))
	{
		(*data) |= (1<<0);
	}
	else
	{
		(*data) &= ~(1<<0);
	}
	
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12))
	{
		(*data) |= (1<<1);
	}
	else
	{
		(*data) &= ~(1<<1);
	}
	
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11))
	{
		(*data) |= (1<<2);
	}
	else
	{
		(*data) &= ~(1<<2);
	}
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8))
	{
		(*data) |= (1<<3);
	}
	else
	{
		(*data) &= ~(1<<3);
	}
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7))
	{
		(*data) |= (1<<4);
	}
	else
	{
		(*data) &= ~(1<<4);
	}
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6))
	{
		(*data) |= (1<<5);
	}
	else
	{
		(*data) &= ~(1<<5);
	}
	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15))
	{
		(*data) |= (1<<6);
	}
	else
	{
		(*data) &= ~(1<<6);
	}
	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14))
	{
		(*data) |= (1<<7);
	}
	else
	{
		(*data) &= ~(1<<7);
	}
	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13))
	{
		(*data) |= (1<<8);
	}
	else
	{
		(*data) &= ~(1<<8);
	}
	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12))
	{
		(*data) |= (1<<9);
	}
	else
	{
		(*data) &= ~(1<<9);
	}
	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11))
	{
		(*data) |= (1<<10);
	}
	else
	{
		(*data) &= ~(1<<10);
	}
	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10))
	{
		(*data) |= (1<<11);
	}
	else
	{
		(*data) &= ~(1<<11);
	}
	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9))
	{
		(*data) |= (1<<12);
	}
	else
	{
		(*data) &= ~(1<<12);
	}
	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8))
	{
		(*data) |= (1<<13);
	}
	else
	{
		(*data) &= ~(1<<13);
	}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15))
	{
		(*data) |= (1<<14);
	}
	else
	{
		(*data) &= ~(1<<14);
	}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14))
	{
		(*data) |= (1<<15);
	}
	else
	{
		(*data) &= ~(1<<15);
	}
	
	printf("%.2f\n",((float)(*data))/8192*5);
}

static void AD7606_Config(void)
{
	/*****   数据位        D0~D15*************/
	GPIO_Config(GPIO_A,15,1);   //AD7606_D0
	GPIO_Config(GPIO_A,12,1);   //AD7606_D1
	GPIO_Config(GPIO_A,11,1);   //AD7606_D2
	GPIO_Config(GPIO_C,8 ,1);   //AD7606_D3
	GPIO_Config(GPIO_C,7 ,1);   //AD7606_D4
	GPIO_Config(GPIO_C,6 ,1);   //AD7606_D5
	GPIO_Config(GPIO_D,15,1);   //AD7606_D6
	GPIO_Config(GPIO_D,14,1);   //AD7606_D7
	GPIO_Config(GPIO_D,13,1);   //AD7606_D8
	GPIO_Config(GPIO_D,12,1);   //AD7606_D9
	GPIO_Config(GPIO_D,11,1);   //AD7606_D10
	GPIO_Config(GPIO_D,10,1);   //AD7606_D11
	GPIO_Config(GPIO_D,9 ,1);   //AD7606_D12
	GPIO_Config(GPIO_D,8 ,1);   //AD7606_D13
	GPIO_Config(GPIO_B,15,1);   //AD7606_D14
	GPIO_Config(GPIO_B,14,1);   //AD7606_D15
	
	/*********控制位 CS、RD、RST、CVT、BUSY、FRST、OS0、OS1、OS2*******/
	GPIO_Config(GPIO_D,1 ,0);   //AD7606_CS
	GPIO_Config(GPIO_D,2 ,0);   //AD7606_RD
	GPIO_Config(GPIO_D,3 ,0);   //AD7606_RST
	GPIO_Config(GPIO_D,4 ,0);   //AD7606_CVT
	GPIO_Config(GPIO_D,0 ,1);   //AD7606_BUSY
	GPIO_Config(GPIO_C,12,1);   //AD7606_FRST
	GPIO_Config(GPIO_D,7 ,0);   //AD7606_OS0
	GPIO_Config(GPIO_D,6 ,0);   //AD7606_OS1
	GPIO_Config(GPIO_D,5 ,0);   //AD7606_OS2
	
}
