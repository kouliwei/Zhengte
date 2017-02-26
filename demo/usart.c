#include "usart.h"





USART_TypeDef* COM_USART[COMn] = {EVAL_COM1,EVAL_COM2}; 

GPIO_TypeDef* COM_TX_PORT[COMn] = {EVAL_COM1_TX_GPIO_PORT,EVAL_COM2_TX_GPIO_PORT};
 
GPIO_TypeDef* COM_RX_PORT[COMn] = {EVAL_COM1_RX_GPIO_PORT,EVAL_COM2_RX_GPIO_PORT};

const uint32_t COM_USART_CLK[COMn] = {EVAL_COM1_CLK,EVAL_COM2_CLK};

const uint32_t COM_TX_PORT_CLK[COMn] = {EVAL_COM1_TX_GPIO_CLK,EVAL_COM2_TX_GPIO_CLK};
 
const uint32_t COM_RX_PORT_CLK[COMn] = {EVAL_COM1_RX_GPIO_CLK,EVAL_COM2_RX_GPIO_CLK};

const uint16_t COM_TX_PIN[COMn] = {EVAL_COM1_TX_PIN,EVAL_COM2_TX_PIN};

const uint16_t COM_RX_PIN[COMn] = {EVAL_COM1_RX_PIN,EVAL_COM2_RX_PIN};
 
const uint8_t COM_TX_PIN_SOURCE[COMn] = {EVAL_COM1_TX_SOURCE,EVAL_COM2_TX_SOURCE};

const uint8_t COM_RX_PIN_SOURCE[COMn] = {EVAL_COM1_RX_SOURCE,EVAL_COM2_RX_SOURCE};
 
const uint8_t COM_TX_AF[COMn] = {EVAL_COM1_TX_AF,EVAL_COM2_TX_AF};
 
const uint8_t COM_RX_AF[COMn] = {EVAL_COM1_RX_AF,EVAL_COM2_RX_AF};


static void STM_EVAL_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct);



void USART_Config(uint32_t BaudRate,COM_TypeDef COM)
{
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    STM_EVAL_COMInit(COM, &USART_InitStructure);
}


void STM_EVAL_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* Enable GPIO clock */
    
    RCC_AHB1PeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM], ENABLE);
    
    /* Enable UART clock */
    RCC_APB1PeriphClockCmd(COM_USART_CLK[COM], ENABLE);
    
    /* Connect PXx to USARTx_Tx*/
    GPIO_PinAFConfig(COM_TX_PORT[COM], COM_TX_PIN_SOURCE[COM], COM_TX_AF[COM]);
    
    /* Connect PXx to USARTx_Rx*/
    GPIO_PinAFConfig(COM_RX_PORT[COM], COM_RX_PIN_SOURCE[COM], COM_RX_AF[COM]);
    
    /* Configure USART Tx as alternate function  */
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);
    
    /* Configure USART Rx as alternate function  */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
    GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);

    /* USART configuration */
    USART_Init(COM_USART[COM], USART_InitStruct);
    
    /********中断响应函数*************/
		
    USART_ITConfig(COM_USART[COM], USART_IT_RXNE, DISABLE);   //串口接收中断禁能
 
    /* Enable USART */
    USART_Cmd(COM_USART[COM], ENABLE);
}
	
/*****************************************function :小车定时发送的信号*************************************/
/****变量说明:stateFlag = 1:状态改变;stateFlag = 0:状态和上一次的一样**********************************
*************:historyFlag:保存上次的状态***************************************************************
*************:history_gl_flag2:保存上一次的gl_flag2的值************************************************/


extern void TXD_USART_Buff(USART_TypeDef* USARTx)
{
		static uint8_t j = 0;
    static uint8_t stateFlag = 0;
    static uint8_t historyFlag[10] = {0};
		static uint8_t history_gl_flag2 = 0;
		static uint8_t history_gl_Daowei = 0;
		

		history_gl_Daowei = gl_Daowei;
	
    if(historyFlag [0] != gl_car.pos1)
    {
        stateFlag = 1; 
        historyFlag [0] = gl_car.pos1;
    }
		
    if(historyFlag [1] != gl_car.pos)
    {
        stateFlag = 1;
        historyFlag [1] = gl_car.pos;
    }
		
    if(historyFlag [2] != gl_car.opr)
    {
        stateFlag = 1;
        historyFlag [2] = gl_car.opr;
    }

    if(historyFlag [3] != gl_StartFlag)
    {
        stateFlag = 1;
        historyFlag [3] = gl_StartFlag;
    }

    if(historyFlag [4] != gl_ColliFlag)
    {
        stateFlag = 1;
        historyFlag [4] = gl_ColliFlag;
    }

    if(historyFlag [5] != gl_SlowFlag)
    {
        stateFlag = 1;
        historyFlag [5] = gl_SlowFlag;
    }

    if(historyFlag [6] != gl_StopFlag)
    {
        stateFlag = 1;
        historyFlag [6] = gl_StopFlag;
    }

    if(historyFlag [7] != gl_DirFlag)
    {
        stateFlag = 1;
        historyFlag [7] = gl_DirFlag;
    }
		
		if(historyFlag[8] != gl_car_state)
		{
			stateFlag = 1;
			historyFlag [8] = gl_car_state;
		}
		if(historyFlag[9] != gl_AlertFlag)
		{
			stateFlag = 1;
			historyFlag[9] = gl_AlertFlag;
		}

	
		
		if(gl_CheckFlag == 1)
		{
			if(j == 0)
			{
				TXD_ACTIVE_MODE1(USARTx);
				j++;
			}
			else if(j == 1)
			{
				TXD_CONFIG(USARTx);
				j++;
			}
//			else if(j == 2)
//			{
//			  TXD_DINGWEI(USARTx,gl_Daowei);
//				j++;
//				
//			}
			else if(j == 2)
			{
				if(gl_car.num == 0)
				{
					gl_car_state = 4;
					TXD_ACTIVE_MODE4(USARTx);
				}
				j = 0;
				gl_CheckFlag = 0;
			}
		}
		else
		{
			/******************被动发送:发送接收到上位机的数据*********************/
			if(gl_TxFlag == 1)
			{
				  TXD_PASSIVE_MODE1(USARTx);
//				if(gl_Buff [0] != 6)
//				{
//					TXD_PASSIVE_MODE1(USARTx);
//				}
//				else
//				{
//					if((gl_Buff[2] == 1||gl_Buff[2] == 2)&&gl_Buff[1] != 0)    //进入修改小车编号模式，开始的数据发送。
//					{
//						if(gl_flag2 == 1)
//						{
//							TXD_PASSIVE_MODE1(USARTx);
//						}
//					}
//					else
//					{
//						TXD_PASSIVE_MODE1(USARTx);
//					}
//				}
				gl_TxFlag = 0;
			}
			/******************** 主动发送:发送小车自己的信息 ****************************/
			else
			{
				if(gl_car_state != 4)
        {
					
						if(gl_SlowDownErrorData_Flag == 1)       //  send the slowdown error 
						{
							gl_SlowDownErrorData_Flag = 0;
							TXD_ERROR(USARTx,1,gl_car.pos,1);
							
						}
						else if(gl_StopErrorData_Flag == 1)
						{
							gl_StopErrorData_Flag = 0;
							TXD_ERROR(USARTx,1,gl_car.pos,2);
						}
						
						else if(gl_SlowDownRightData_Flag == 1)
						{
							gl_SlowDownRightData_Flag = 0;
							TXD_ERROR(USARTx,1,gl_car.pos,3);   //3代表减速正常了
						}
						
						else if(gl_StopRightData_Flag == 1)
						{
							gl_StopRightData_Flag = 0;
							TXD_ERROR(USARTx,1,gl_car.pos,4);   //4代表停止正常了
						}
						else if(gl_DingweiRightData_Flag == 1)
						{
							gl_DingweiRightData_Flag = 0;         //旋转到位发送
							gl_Daowei = 1;
							if(history_gl_Daowei != gl_Daowei)
							TXD_DINGWEI(USARTx,1);
						}
						else if(gl_DingweiErrorData_Flag == 1)
						{
							gl_DingweiErrorData_Flag = 0;
							gl_Daowei = 0;
							if(history_gl_Daowei != gl_Daowei)
							TXD_DINGWEI(USARTx,0);
						}
						else if(gl_ErrorData_Flag == 1)
						{
							TXD_ERROR_MODE3(USARTx);
							gl_ErrorData_Flag = 0;
						}
            else if(stateFlag == 1)
            {
                stateFlag = 0;
								TXD_ACTIVE_MODE1(USARTx);
            }
				}
				else
				{
            if(gl_flag2 == 1 && history_gl_flag2 == 0)      
            {
							if(gl_CorrectNumFlag == 1)
							{
								TXD_ACTIVE_MODE2(USARTx);
							}
							else
							{
								TXD_ACTIVE_MODE3(USARTx);
							}
            }
						history_gl_flag2 = gl_flag2;
				}
    }
	}
}




extern void TXD_USART(USART_TypeDef* USARTx,uint16_t data,int8_t type)
{
	switch(type)
	{
		case 0:
			TXD_USART_CHAR(USARTx,data);
			break;
		case 2:
			TXD_USART_BIN(USARTx,data);
			break;
		case 10:
			TXD_USART_DEC(USARTx,data);
			break;
		case 16:
			TXD_USART_HEX(USARTx,data);
			break;
		default:
			TXD_USART_DEC(USARTx,data);
			break;
	}
}


static void TXD_USART_DEC(USART_TypeDef* USARTx,uint16_t data)
{
	uint16_t num[5]={0},m=0;
	int8_t i=0;
	for(i=0;;)  //将data的每一位倒序存入num[5]的数组中，例如data=3456,则num[5]={6,5,4,3,0};for循环后i=3
	{
		m=data/10;
		num[i]=data%10;
		data=m;
		if(data==0)
			break;
		else
			i++;
	}
	for(;i>=0;i--)
	{
		USART_SendData(USARTx,num[i]+48);
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
	}
}

static void TXD_USART_HEX(USART_TypeDef* USARTx,uint16_t data)
{
	uint16_t num[5]={0},m=0;
	int8_t i=0;
	for(i=0;;)  
	{
		m=data/16;
		num[i]=data%16;
		data=m;
		if(data==0)
			break;
		else
			i++;
	}
	for(;i>=0;i--)
	{
		if(num[i]>9)
		{
			num[i]=num[i]+7;
		}
		USART_SendData(USARTx,num[i]+48);
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
	}
	printf("\r\n");
}



/**
  * @brief  output the data as binary system
  * @param  USARTx:Specifies the USART
  * @param  data:
            This parameter must be a number between 0x0000 and 0xFFFF.
  * @retval None
  */

static void TXD_USART_BIN(USART_TypeDef* USARTx,uint16_t data)
{
	uint8_t i;
	for(i=0;i<16;i++)
	{
		if(data&(1<<(15-i)))
		{
			USART_SendData(USARTx,'1');
			while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
		}
		else
		{
			USART_SendData(USARTx,'0');
			while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
		}
			
	}
	printf("\r\n");

}

static void TXD_USART_CHAR(USART_TypeDef* USARTx,uint16_t data)
{
	USART_SendData(USARTx,data);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE) == RESET);
//	printf("\r\n");
}





extern  void TXD_ACTIVE_MODE1(USART_TypeDef* USARTx)
{
    uint8_t sum_check = 0;
    
    TXD_USART(USARTx,0x55,0);        
    TXD_USART(USARTx,13,0);
    TXD_USART(USARTx,13,0);
    TXD_USART(USARTx,0xAA,0);
	
        
    TXD_USART(USARTx,0,0);
    TXD_USART(USARTx,gl_car.num,0);
    
    TXD_USART(USARTx,7,0);
    TXD_USART(USARTx,gl_car.pos1,0);           //根据此数据使小车位置更精确
    TXD_USART(USARTx,gl_car.pos,0);           //发送小车实际位置
    TXD_USART(USARTx,gl_car.opr,0);          //发送小车位置信息 
    TXD_USART(USARTx,gl_StartFlag,0);        //发送小车启动信号
    TXD_USART(USARTx,gl_ColliFlag,0);       //发送小车防撞信号（线上）
    TXD_USART(USARTx,gl_SlowFlag,0);         //发送小车减速信号                    
    TXD_USART(USARTx,gl_StopFlag,0);         //发送小车停止信号
    TXD_USART(USARTx,gl_DirFlag,0);         //发送小车方向信号
	  TXD_USART(USARTx,gl_car_state,0);         //发送小车状态信号
		TXD_USART(USARTx,gl_AlertFlag,0);         //发送报警信号
    sum_check = gl_car.num + 7 + gl_car.pos1 + gl_car.pos + gl_car.opr + gl_StartFlag + gl_ColliFlag + gl_SlowFlag + gl_StopFlag + gl_DirFlag + gl_car_state + gl_AlertFlag;
    TXD_USART(USARTx,sum_check,0);	
}

 
static void TXD_ACTIVE_MODE2(USART_TypeDef* USARTx)
{
	 /*******************数据头********************/

    TXD_USART(USARTx,0x55,0);
    TXD_USART(USARTx,5,0);
    TXD_USART(USARTx,5,0);
    TXD_USART(USARTx,0xAA,0);

    TXD_USART(USARTx,0,0);
    TXD_USART(USARTx,0,0);
								
    TXD_USART(USARTx,6,0);
    TXD_USART(USARTx,0,0);
    TXD_USART(USARTx,1,0);
    TXD_USART(USARTx,7,0);
}

static void TXD_ACTIVE_MODE3(USART_TypeDef* USARTx)
{
	 /*******************数据头********************/

    TXD_USART(USARTx,0x55,0);
    TXD_USART(USARTx,5,0);
    TXD_USART(USARTx,5,0);
    TXD_USART(USARTx,0xAA,0);

    TXD_USART(USARTx,0,0);
    TXD_USART(USARTx,0,0);
								
    TXD_USART(USARTx,6,0);
    TXD_USART(USARTx,0,0);
    TXD_USART(USARTx,2,0);
    TXD_USART(USARTx,8,0);
}

static void TXD_ACTIVE_MODE4(USART_TypeDef* USARTx)
{
	 /*******************数据头********************/

    TXD_USART(USARTx,0x55,0);
    TXD_USART(USARTx,5,0);
    TXD_USART(USARTx,5,0);
    TXD_USART(USARTx,0xAA,0);

    TXD_USART(USARTx,0,0);
    TXD_USART(USARTx,0,0);
								
    TXD_USART(USARTx,6,0);
    TXD_USART(USARTx,0,0);
    TXD_USART(USARTx,6,0);
    TXD_USART(USARTx,12,0);
}


extern void TXD_PASSIVE_MODE1(USART_TypeDef* USARTx)
{
    uint8_t i = 0;
    uint8_t sum_check = 0;
    /*******************数据头********************/

    TXD_USART(USARTx,0x55,0);
    TXD_USART(USARTx,gl_RxLen+2,0);
    TXD_USART(USARTx,gl_RxLen+2,0);
    TXD_USART(USARTx,0xAA,0);
					
    TXD_USART(USARTx,1,0);
    sum_check += 1;
    TXD_USART(USARTx,gl_car.num,0);
    sum_check += gl_car.num;
					
    for(i = 0; i < gl_RxLen; i++)
    {
        TXD_USART(USARTx,gl_Buff[i],0);
        sum_check += gl_Buff[i];
    }
    TXD_USART(USARTx,sum_check,0);
}



static void TXD_PASSIVE_MODE2(USART_TypeDef* USARTx)
{
	
    TXD_USART(USARTx,0x55,0);
    TXD_USART(USARTx,5,0);
    TXD_USART(USARTx,5,0);
    TXD_USART(USARTx,0xaa,0);


    TXD_USART(USARTx,0,0);
    TXD_USART(USARTx,0,0);							
    TXD_USART(USARTx,6,0);
    TXD_USART(USARTx,0,0);
    TXD_USART(USARTx,0,0);
    TXD_USART(USARTx,6,0);
}



static void TXD_CONFIG(USART_TypeDef* USARTx)
{
    uint8_t i =0,sum_check = 0;
    TXD_USART(USARTx,0x55,0);
    TXD_USART(USARTx,45,0);
    TXD_USART(USARTx,45,0);
    TXD_USART(USARTx,0xAA,0);
        
    TXD_USART(USARTx,0,0);
    TXD_USART(USARTx,gl_car.num,0);
    sum_check += gl_car.num;
	 
    for(i = 0; i < 43; i++)
    {
        TXD_USART(USARTx,gl_Store[i],0);
        sum_check += gl_Store[i];
    }
    TXD_USART(USARTx,sum_check,0);
	 
}

/**
  * @brief  
  * @param  error_type :the type of the error
	*         This parameter can be one of the following values:
	*         	     @0: the error of the communication
	*         	     @1: the error of the senser
	*         	     @2: the error of the motor 
	*         position: the position of the senser which break down, is only effective when the error_type is equal to 1.
	*         senser  : the type of the senser which break down, is only effective when the error_type is equal to 1.
	*         This parameter can be one of the following values:
	*                @0: the senser is normal
	*                @1: the slow-down senser broke down
	*                @2: the stop senser broke down
  * @retval None
  */

extern void TXD_ERROR(USART_TypeDef* USARTx,uint8_t error_type,uint8_t position,uint8_t senser_type)
{
	switch(error_type)
	{
		case 0:
			break;
		case 1:
			TXD_ERROR_MODE1(USARTx,position,senser_type);
			break;
		case 2:
			TXD_ERROR_MODE2(USARTx);
			break;
	}
}

static void TXD_ERROR_MODE1(USART_TypeDef* USARTx,uint8_t position,uint8_t senser_type)
{
		uint8_t sum_check = 0;
	  TXD_USART(USARTx,0x55,0);
    TXD_USART(USARTx,6,0);
    TXD_USART(USARTx,6,0);
    TXD_USART(USARTx,0xAA,0);
	
		TXD_USART(USARTx,0,0);
    TXD_USART(USARTx,gl_car.num,0);
	
		TXD_USART(USARTx,9,0);
		TXD_USART(USARTx,1,0);
		TXD_USART(USARTx,position,0);
		TXD_USART(USARTx,senser_type,0);
	
		sum_check = gl_car.num + 9 + 1 + position + senser_type;
		TXD_USART(USARTx,sum_check,0);
	
}
static void TXD_ERROR_MODE2(USART_TypeDef* USARTx)
{
		uint8_t sum_check = 0;
	  TXD_USART(USARTx,0x55,0);
    TXD_USART(USARTx,5,0);
    TXD_USART(USARTx,5,0);
    TXD_USART(USARTx,0xAA,0);
	
	  TXD_USART(USARTx,0,0);
    TXD_USART(USARTx,gl_car.num,0);
	
		TXD_USART(USARTx,9,0);
		TXD_USART(USARTx,2,0);
		TXD_USART(USARTx,1,0);
	
		sum_check = gl_car.num  + 9 + 2 + 1;
		TXD_USART(USARTx,sum_check,0);
}

extern void TXD_ERROR_MODE3(USART_TypeDef* USARTx)
{
		uint8_t sum_check = 0;
	  TXD_USART(USARTx,0x55,0);
    TXD_USART(USARTx,5,0);
    TXD_USART(USARTx,5,0);
    TXD_USART(USARTx,0xAA,0);
	
	  TXD_USART(USARTx,0,0);
    TXD_USART(USARTx,gl_car.num,0);
	
		TXD_USART(USARTx,9,0);
		TXD_USART(USARTx,4,0);
		TXD_USART(USARTx,1,0);
	
		sum_check = gl_car.num  + 9 + 4 + 1;
		TXD_USART(USARTx,sum_check,0);
	
}


/****************用于定位发送:类型12数据类型*******************/
extern void TXD_DINGWEI(USART_TypeDef* USARTx,uint8_t Type)
{
		uint8_t sum_check = 0;
	  TXD_USART(USARTx,0x55,0);
    TXD_USART(USARTx,5,0);
    TXD_USART(USARTx,5,0);
    TXD_USART(USARTx,0xAA,0);
	
	  TXD_USART(USARTx,0,0);
    TXD_USART(USARTx,gl_car.num,0);
	
		TXD_USART(USARTx,12,0);
		TXD_USART(USARTx,gl_car.pos,0);
	  TXD_USART(USARTx,Type,0);
		sum_check = gl_car.num  + 12 + gl_car.pos + Type;
		TXD_USART(USARTx,sum_check,0);
	
}
