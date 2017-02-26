   /**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f2xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx_it.h"
#include "include.h"


__IO uint16_t IC3ReadValue1 = 0, IC3ReadValue2 = 0;
__IO uint16_t CaptureNumber = 0;
__IO uint32_t Capture = 0;
__IO uint32_t TIM1Freq = 0;





/** @addtogroup STM32F2xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup IOToggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */

//__asm void wait(void)
//{
//	BX lr
//}

void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
		
  }
//	wait();
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	IWDG_ReloadCounter();
}

/******************************************************************************/
/*                 STM32F2xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f2xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  This function handles External line 0 interrupt request.
  * @param  None
  * @retval None
  */
void BUSY_IRQHandler(void)
{
  if(EXTI_GetITStatus(BUSY_EXTILINE) != RESET)
  {
   
		
		Led_Toggle(LED1);
		Led_Toggle(LED2);
		 /* Clear the EXTI line 0 pending bit */
        EXTI_ClearITPendingBit(BUSY_EXTILINE);
		AD7606_Read();
    
  }
}

void PFO_EXTI(void)
{
    uint8_t flag1 = 0x55;
    uint8_t flag2 = 0xaa;
		gl_car_state = 0;
		Led_Drive(0x0f);

    
    
    if(EXTI_GetITStatus(PFO_EXTI_LINE) != RESET)
    {
        EXTI_ClearITPendingBit(PFO_EXTI_LINE);
			

					
				
			

        sEE_WriteBuffer(&flag1,sEE_WRITE_ADDRESS1,1);   										//第一个字节写特征值0x55
        sEE_WriteBuffer(&flag2,sEE_WRITE_ADDRESS1+1,1); 										//第二个字节写特征值0xaa
			
				sEE_WriteBuffer(&gl_car.opr,ADDRESS1_INEEPROM,1); 
				sEE_WriteBuffer(&gl_car.pos,ADDRESS2_INEEPROM,1); 
				sEE_WriteBuffer(&gl_DirFlag,ADDRESS3_INEEPROM,1);
				sEE_WriteBuffer(&gl_car.num,ADDRESS4_INEEPROM,1);
				sEE_WriteBuffer(&gl_car.pos1,ADDRESS10_INEEPROM,1); 
				sEE_WriteBuffer(&gl_Double_Flag,ADDRESS12_INEEPROM,1); 
				sEE_WriteBuffer(&gl_Multi_Flag,ADDRESS13_INEEPROM,1); 
				sEE_WriteBuffer(&gl_CheckStop_Flag[0],ADDRESS14_INEEPROM,1);
				
				sEE_WriteBuffer(&gl_StartFlag,ADDRESS15_INEEPROM,1);
				sEE_WriteBuffer(&gl_SlowFlag,ADDRESS16_INEEPROM,1);
				sEE_WriteBuffer(&gl_ColliFlag,ADDRESS17_INEEPROM,1);
				sEE_WriteBuffer(&gl_StopFlag,ADDRESS18_INEEPROM,1);
				sEE_WriteBuffer(&gl_Status[0],ADDRESS19_INEEPROM,1);
				sEE_WriteBuffer(&gl_Status[1],ADDRESS20_INEEPROM,1);
				sEE_WriteBuffer(&gl_Status[2],ADDRESS21_INEEPROM,1);
				sEE_WriteBuffer(&gl_AlertFlag,ADDRESS22_INEEPROM,1);
				sEE_WriteBuffer(&gl_Flag5,ADDRESS23_INEEPROM,1);
			  sEE_WriteBuffer(&gl_flag1,ADDRESS24_INEEPROM,1);
        sEE_WaitEepromStandbyState();
    }
}




void ALA_EXTI(void)
{
    uint8_t flag = 0;
		Led_Toggle(LED3);
    if(EXTI_GetITStatus(ALA_EXTI_LINE) != RESET)
    {
        EXTI_ClearITPendingBit(ALA_EXTI_LINE);
        while(EFF_MALRM())                                                  //小车输出报警信号
        {
            RST_VAL_MARST();                                                //清除小车报警信号
            Delay_Nms(100);
            flag++;
            if(flag > 20)
            {
                printf("  连续20次未清除报警，电机故障，要进行特殊处理");
								flag = 0;
								Stop();
            }
				}
        SET_VAL_MARST();
				if(EFF_MZSPD())  //电机零速检出有效
				{
					gl_AlertStopFlag = 1;
				}
    }
}	





void TIM8_BRK_TIM12_IRQHandler(void)
{
    static int8_t i = 0;
//		static uint8_t flag = 0;
//	  static uint8_t flag1 = 0;
    if(gl_flagRx[0] == 1)   
    {
        gl_flagRx[0] = 0;
        i = 0;
    }
		
    
    if(TIM_GetITStatus(TIM12, TIM_IT_Update) != RESET)
    {    
        TIM_ClearITPendingBit(TIM12 , TIM_FLAG_Update);
        i++;
    }
    
    if(i <= 4)
    {
        Rx_Disable();
        gl_flagRx[1] = 1;
        Rx_Enable();
    }
    else
    {
				Led_Toggle(LED4);
        i = 0;
			  if(gl_JiTingFlag == 0 && gl_StopFlag != 123)
				{	
					 gl_Status[0] = gl_StartFlag;
					 gl_Status[1] = gl_SlowFlag;
					 gl_Status[2] = gl_StopFlag;
					 gl_JiTingFlag = 1;
				}
        gl_StartFlag = 0;
			  gl_SlowFlag = 0;
			  gl_StopFlag = 123;
				
				gl_CheckFlag1 = 1;
			
				if(gl_OpenFlag[0] == 1)  //用户点过启动按钮,并且掉线了
				{
					gl_OpenFlag[1] = 2;
				}
				else
				{
					gl_OpenFlag[1] = 0;
				}
				printf("data can not be received");
    }
		
		
//		if(gl_CheckFlag1 == 1)
//		{
//			i = 0;
//			if(flag > 15)   //17.5s复位一下
//			{
//				Wifi_RST();
//				flag = 0;
//			}
//			else
//			{
//				flag++;
//			}
//		}
		
		if(gl_CheckFlag1 == 1)
		{
			i = 0;
			if(gl_ResetFlag > 10)   //17.5s复位一下
			{
				Wifi_RST();
				gl_ResetFlag = 0;
			}
			else
			{
				gl_ResetFlag++;
			}
		}
		else
		{
			gl_ResetFlag = 0;
		}
//		
		
//		if(gl_ResetFlag1 == 1)
//		{
//			gl_ResetFlag = 0;
//		}
//			if(flag1 == 1)   
//			{
//				i = 0;
//				Wifi_RST();
//				TIM_Cmd(TIM12,DISABLE);
//				Rx_Disable();
//        gl_flagRx[1] = 1;
//        Rx_Enable();
//			}
				
}



void EVAL_COM2_IRQHandler(void)
{
    static uint8_t state = 0;
    static uint8_t lencnt = 0;
    static uint8_t length = 0;
		static uint8_t temp_length = 0;
    static uint8_t flag = 0;
		static uint8_t sum_check = 0;
	
    uint16_t ch=0;
	
		Led_Toggle(LED1);     //每来一次接收中断，LED1闪烁一次。
    Tx_Disable();	
	  gl_Tim12Flag = 0;
    TIM_Cmd(TIM12,ENABLE);
    if(gl_flagRx[1] == 1)      //复位接收状态
    {
        gl_flagRx[1] = 0;
        flag = 0;
        length = 0;
        lencnt = 0;
				temp_length = 0;
				sum_check = 0;
        state = 0;
    }
    
    if(USART_GetFlagStatus(EVAL_COM2, USART_FLAG_RXNE) != RESET)
    {
        USART_ClearFlag(EVAL_COM2, USART_FLAG_RXNE);
        ch = USART_ReceiveData(EVAL_COM2);
    }
		
		switch(state)
		{
			case 0:
				if(ch == 0x55)
				{
					state = 1;
				}
				else
				{
					state = 0;
				}
				length = 0;
				temp_length = 0;
				sum_check = 0;
				flag  = 0;
				lencnt = 0;
				break;
			case 1:
				if(flag == 0)
				{
					temp_length = ch;
					flag = 1;
				}
				else
				{
					length = ch;
					flag = 0;
					if(temp_length == length)   //长度校验
					{
						state = 2;
						gl_RxLen = length;
					}
					else
					{
						state = 0;
						temp_length = 0;
						length = 0;
					}
				}
				break;
			case 2:
				if(ch == 0xAA)
				{
					state = 3;
				}
				else
				{
					state = 0;
					flag = 0;
					temp_length = 0;
					length = 0;
				}
				break;
			case 3:
				gl_Buff[lencnt++] = ch;
				sum_check += ch;
				if(lencnt == length)
				{
					state = 4;
					lencnt = 0;
				}
				break;
			case 4:
				if(ch == sum_check)   //校验正确
				{
					gl_RxRight = 1;  //成功接收到10个123，将gl_RxRight置1，state置0，方便下次接收
          gl_flagRx[0] = 1;
					TIM_SetCounter(TIM12,0);
          Led_Toggle(LED2);
				}
				flag = 0;
				state = 0;   
				lencnt = 0;
				sum_check = 0;
				length = 0;
				temp_length = 0;
				gl_ResetFlag = 0;
				break;
		}
}



void ENCODER_IRQHandler(void)
{
		Led_Toggle(LED1);
	  if(TIM_GetITStatus(ENCODER_TIMER, TIM_IT_Update) != RESET)
    {    
        TIM_ClearITPendingBit(ENCODER_TIMER , TIM_FLAG_Update);
				if(ENCODER_TIMER->CR1 & 0x0010)    //反向
				{
					Led_Toggle(LED4);
				}
				else                               //正向
				{
					Led_Toggle(LED3);
				}
    }
	
}




void Encoder_Count(uint16_t* last_count,uint16_t* current_count,uint32_t* error_count,uint32_t* error_sum)
{
    uint16_t temp_last_count = *last_count;
    uint16_t temp_current_count = *current_count;
    uint32_t temp_error_count = *error_count;
    uint32_t temp_error_sum = *error_sum;

    temp_current_count = ENCODER_TIMER->CNT;
    if(IS_FOREWARD())
    {
        if(temp_current_count < temp_last_count)
        {
            temp_error_count = 60000 - temp_last_count + temp_current_count;
        }
        else
        {
            temp_error_count = temp_current_count - temp_last_count;
        }
    }
    else
    {
        if(temp_current_count > temp_last_count)
        {
            temp_error_count = 60000 - temp_current_count + temp_last_count;
        }
        else
        {
            temp_error_count = temp_last_count - temp_current_count;
        }
    }
    temp_last_count = temp_current_count;
    temp_error_sum += temp_error_count;

    *last_count = temp_last_count;
    *current_count = temp_current_count;
    *error_count = temp_error_count;
    *error_sum = temp_error_sum;
}



void SlowDistance_Antishake()   //减速的距离防抖
{
    static uint16_t last_count = 0;
    static uint16_t current_count = 0;
    static uint32_t error_count = 0;
    static uint32_t error_sum = 0;
    
    if(gl_Senser_Flag[0] == 0)
    {
        Encoder_Count(&last_count,&current_count,&error_count,&error_sum);
        if(error_sum > 10000)
        {
            gl_Senser_Flag[0] = 1;
        }
    }
    else
    {
        last_count = 0;
        current_count = 0;
        error_count = 0;
        error_sum = 0;
    }
}

void StopDistance_Antishake()   //停止的距离防抖
{
    static uint16_t last_count = 0;
    static uint16_t current_count = 0;
    static uint32_t error_count = 0;
    static uint32_t error_sum = 0;
    
    if(gl_Senser_Flag[1] == 0)
    {
        Encoder_Count(&last_count,&current_count,&error_count,&error_sum);
        if(error_sum > 10000)
        {
            gl_Senser_Flag[1] = 1;
        }
    }
    else
    {
        last_count = 0;
        current_count = 0;
        error_count = 0;
        error_sum = 0;
    }
}





void DDistance_Antishake()        //方向传感器距离防抖
{ 
	
    static uint16_t last_count = 0;
    static uint16_t current_count = 0;
    static uint32_t error_count = 0;
    static uint32_t error_sum = 0;
    
    if(gl_Senser_Flag[2] == 0)
    {
        Encoder_Count(&last_count,&current_count,&error_count,&error_sum);
        if(error_sum > 10000)
        {
            gl_Senser_Flag[2] = 1;
        }
    }
    else
    {
        last_count = 0;
        current_count = 0;
        error_count = 0;
        error_sum = 0;
    }
}

void StopDistance_Test(void)
{
	  static uint16_t last_count = 0;
    static uint16_t current_count = 0;
    static uint32_t error_count = 0;
    static uint32_t error_sum = 0;
    
    if(gl_CheckStop_Flag[0] == 1)
    {
        Encoder_Count(&last_count,&current_count,&error_count,&error_sum);
        if(error_sum > 60000)
        {
            gl_CheckStop_Flag[1] = 1;
						gl_CheckStop_Flag[0] = 0;
        }
    }
    else
    {
        last_count = 0;
        current_count = 0;
        error_count = 0;
        error_sum = 0;
    }
}



//*************减速后延时未检测到停止则小车自动停止************************//
//*************gl_car.pos 在左右升降梯时延时6s: 20*300=6000;***************//
//*************gl_car.pos 不在左右升降梯时延时10s:20*500 = 10000;**********//
//**************************************************************************//

void StopTime_Test(void) 
{
	static uint16_t  flag[2]= {0};
	
	if(gl_CheckStop_Flag[0] == 1 &&  gl_car_state == 2 && gl_car.pos != 21 && gl_car.pos != 0)
	{
		if(flag[0] > 500)
		{
			flag[0] = 0;
			gl_CheckStop_Flag[1] = 1;
		}
		else
		{
			if(gl_StopFlag != 123 && gl_ColliFlag == 0)
			{
				flag[0]++; 
			}
		}
	}
	else
	{
		flag[0] = 0;
	}
	
	
	if(gl_CheckStop_Flag[0] == 1 &&  gl_car_state == 2 && (gl_car.pos == 21 || gl_car.pos == 0))
	{
		if(flag[1] > 300)
		{
			flag[1] = 0;
			gl_CheckStop_Flag[1] = 1;
		}
		else
		{
			if(gl_StopFlag != 123 && gl_ColliFlag == 0)
			{
				flag[1]++; 
			}
		}
	}
	else
	{
		flag[1] = 0;
	}
	
}



void Time_Antishake(void)   //gl_Senser_Flag[0]:减速防抖；gl_Senser_Flag[1]:停止防抖；gl_Senser_Flag[2]:换向防抖 ，检测到后10s内不再检测该传感器
{
	static uint16_t flag[5] = {0};
	
	if(gl_Senser_Flag[0] == 0)
	{
		if(flag[0] > 10)
		{
			gl_Senser_Flag[0] = 1;
			flag[0] = 0;
		}
		else  
		{
			flag[0]++;
		}
	}
	else
	{
		flag[0] = 0;
	}
	
	
	
	
	if(gl_Senser_Flag[1] == 0 && gl_ColliFlag == 0 && (gl_car_state == 2 || gl_car_state == 3))
	{
		if(gl_Flag4 > 75)
		{
			gl_Senser_Flag[1] = 1;
			gl_Flag4 = 0;
		}
		else
		{
			gl_Flag4++;
		}
	}
	else
	{
		gl_Flag4 = 0;
	} 
	
	if(gl_Senser_Flag[2] == 0)
	{
		if(flag[2] > 500)                    //换向后10s内不再检测换向.
		{
			gl_Senser_Flag[2] = 1; 
			flag[2] = 0;
		}
		else
		{
			flag[2]++;
		}
	}
	else
	{
		flag[2] = 0;
	}
	
	if( gl_car.pos == gl_pos + 1)
	{
		if(gl_Senser_Flag[3] == 1)      //防撞信号延时10s. 在线下工位时
		{
			if(flag[3] > 500)
			{
				gl_Senser_Flag[3] = 0;
				flag[3] = 0;
				gl_ColliFlag = 0;
			}
			else
			{
				flag[3]++;
			}
		}
		else
		{
			flag[3] = 0;
		}	
	}
	else
	{
		if(gl_Senser_Flag[3] == 1)      //防撞信号延时5s.
		{
			if(flag[3] > 250)
			{
				gl_Senser_Flag[3] = 0;
				flag[3] = 0;
				gl_ColliFlag = 0;
			}
			else
			{
				flag[3]++;
			}
		}
		else
		{
			flag[3] = 0;
		}
	}

	
	
	
	if(gl_Senser_Flag[4] == 1)      //1到20号工位顶升气缸检测延时
	{
		if(flag[4] > 500)
		{
			gl_Senser_Flag[4] = 0;
			flag[4] = 0;
			gl_AlertFlag = 1;
			gl_StopFlag = 100;
		}
		else
		{
			flag[4]++;
		}
	}
	else
	{
		flag[4] = 0;
	}
}




void MOTOR_IRQHandler(void)
{
    if(TIM_GetITStatus(MOTOR_TIM, TIM_IT_Update) != RESET)
    {    
        TIM_ClearITPendingBit(MOTOR_TIM , TIM_FLAG_Update);
//        SlowDistance_Antishake();
//				StopDistance_Antishake();
//				DDistance_Antishake();
//				StopDistance_Test();
        EFF_MOTOR();

    }
}


void Periodic_SendDingwei(void)    //定时发送小车旋转到位信号，5s发送一次
{
	static uint8_t flag = 0;
	if(gl_StopFlag == 1  && (gl_car.pos == 15 || gl_car.pos == 16 || gl_car.pos == 13 || gl_car.pos == 18))
	{
		if(flag > 250)
		{
			flag = 0;
			TXD_DINGWEI(EVAL_COM2,gl_Daowei);
		}
		else
		{
			flag++;
		}
	}
	else if(gl_StopFlag == 100 && gl_AlertFlag == 1 && (gl_car.pos == 1 || gl_car.pos == 20 ))
	{
		if(flag > 250)
		{
			flag = 0;
			TXD_DINGWEI(EVAL_COM2,gl_Daowei);
		}
		else
		{
			flag++;
		}
	}
	else
	{
		flag = 0;
	}
}

void YeJing_Display(void)
{
	static uint8_t flag = 0;
	if(gl_flag == 1)   //液晶的标志位
	{
		if(flag >= 250)
    {
			gl_flag = 0;
			flag =0 ;
    }
		else
		{
			flag++;
		}
	}
}


void Xianxia_Dingwei(void)
 {
	static uint8_t flag = 0;
	if(gl_car.pos != gl_pos + 1)
  {
		gl_car.pos1 = 0;
  }
	
	
	if(gl_flag1 == 1 && gl_car_state == 2  && gl_StopFlag == 0 && gl_car.pos == gl_pos + 1)   //小车到达线下:gl_car.opr == gl_opr + 1;并且启动传感器有效:gl_flag1 = 1;防撞传感器无效:gl_ColliFlag == 0 
  {
		if(flag >= 50)
    {
			flag = 0;
			gl_car.pos1++;
			if(gl_car.pos1 > 40)   //gl_car.pos1 上限设置
			{
				gl_car.pos1 = 40;
			}
		}
		else
		{
			if(gl_ColliFlag == 0)
			{
				flag++;
			}
			else
			{
				flag = flag;
			}
		}
	}
	else
	{
		flag = 0;
	}
}
 
void Error_Detect()
{
	static uint16_t flag = 0;
	if(gl_Flag7 == 0 && gl_car_state == 2 && gl_ColliFlag == 0)
	{
		if(gl_car.pos != gl_pos + 1 && gl_car.pos != gl_pos && gl_car.pos != 1)
		{
			if(flag >= 1000)
			{
				flag = 0;
				gl_ErrorData_Flag = 1;
			}
			else
			{
				flag++;
			}
		}
		else 
		{
			if(gl_DirFlag == FOREWARD && gl_car.pos == gl_pos + 1)
			{
				if(flag >= 1000)
				{
					flag = 0;
					gl_ErrorData_Flag = 1;
				}
				else
				{
					flag++;
				}
			}
		}
	}
	else
	{
		flag = 0;
		gl_ErrorData_Flag = 0;
	}
	
}
/***************************************************************************
*****小车上电20s内一直未接收到数据，则开启复位无线模块的定时器TIM12，*******
*****解决小车一直上电开始一直接收不到数据也一直不复位无线模块的问题。*******
***************************************************************************/
void Timer12_Detect()
{
	static uint16_t flag = 0;
	if(gl_Tim12Flag == 1)
	{
		if(flag == 1000)
		{
			flag = 0;
			TIM_Cmd(TIM12,ENABLE);
			TIM_SetCounter(TIM12,0);
			gl_Tim12Flag = 0;
		}
		else
		{
			flag++;
		}
	}
	else
	{
		flag = 0;
	}
}


void Tx_IRQHandler(void)  //20ms定时发送中断
{
		
    if(TIM_GetITStatus(Tx_TIM,TIM_IT_Update) != RESET)  //更新时间中断
    {
        TIM_ClearITPendingBit(Tx_TIM,TIM_IT_Update);
        TXD_USART_Buff(EVAL_COM2); 
				YeJing_Display();
				Xianxia_Dingwei();
				Time_Antishake();		
				StopTime_Test();		
				Periodic_SendDingwei();
				Error_Detect();

    }
}


