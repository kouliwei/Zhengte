/*
*******************************************************************************
  Copyright (C), 2010-2012, timll Tech. Co., Ltd.
  FileName	   : stm32_eval_i2c_tsensor.c
  Author       : lichy       
  Version      : 1.0.0     
  Date         : 2011/09/28
  Description	 : LIS33DE Low_level_Drive
  Function List: 
  History      :
  <author>     : lichy       
  <time>       : 2011/09/28
  <version >   : 1.0.0 	
  <desc>       : build this moudle				 
*******************************************************************************
*/
#include "stm32_eval_i2c_tsensor.h"


/*------------------------------------------------------------------------------
    Hardware Configuration 
------------------------------------------------------------------------------*/
/** 
  * @brief  I2C port definitions  
  */ 
#define IOE_I2C                          I2C1
#define IOE_I2C_CLK                      RCC_APB1Periph_I2C1
#define IOE_I2C_SCL_PIN                  GPIO_Pin_6
#define IOE_I2C_SCL_GPIO_PORT            GPIOB
#define IOE_I2C_SCL_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define IOE_I2C_SCL_SOURCE               GPIO_PinSource6
#define IOE_I2C_SCL_AF                   GPIO_AF_I2C1
#define IOE_I2C_SDA_PIN                  GPIO_Pin_9
#define IOE_I2C_SDA_GPIO_PORT            GPIOB
#define IOE_I2C_SDA_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define IOE_I2C_SDA_SOURCE               GPIO_PinSource9
#define IOE_I2C_SDA_AF                   GPIO_AF_I2C1
#define IOE_I2C_DR                       ((uint32_t)0x40005410)

/* I2C clock speed configuration (in Hz) 
  WARNING: 
   Make sure that this define is not already declared in other files (ie. 
  stm322xg_eval.h file). It can be used in parallel by other modules. */
#ifndef I2C_SPEED
 #define I2C_SPEED                        100000
#endif /* I2C_SPEED */

/** 
  * @brief  IOE DMA definitions  
  */
#define IOE_DMA_CLK                      RCC_AHB1Periph_DMA1
#define IOE_DMA_CHANNEL                  DMA_Channel_1
#define IOE_DMA_TX_STREAM                DMA1_Stream6   
#define IOE_DMA_RX_STREAM                DMA1_Stream0
#define IOE_DMA_TX_TCFLAG                DMA_FLAG_TCIF6
#define IOE_DMA_RX_TCFLAG                DMA_FLAG_TCIF0


#define TIMEOUT_MAX    0x3000 /*<! The value of the maximal timeout for I2C waiting loops */
/**
  * @}
  */ 

uint32_t IOE_TimeOut = TIMEOUT_MAX; /*<! Value of Timeout when I2C communication fails */


/** 
  * @brief  IOE DMA Direction  
  */ 
typedef enum
{
  IOE_DMA_TX = 0,
  IOE_DMA_RX = 1
}IOE_DMADirection_TypeDef;

/** 
  * @brief  extern function  
  */
extern uint8_t IOE_TimeoutUserCallback(void);

/**
  * @brief  Initializes the GPIO pins used by the IO expander.
  * @param  None
  * @retval None
  */
static void IOE_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Enable IOE_I2C and IOE_I2C_GPIO_PORT & Alternate Function clocks */
  RCC_APB1PeriphClockCmd(IOE_I2C_CLK, ENABLE);
  RCC_AHB1PeriphClockCmd(IOE_I2C_SCL_GPIO_CLK | IOE_I2C_SDA_GPIO_CLK 
                        , ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Reset IOE_I2C IP */
  RCC_APB1PeriphResetCmd(IOE_I2C_CLK, ENABLE);
  
  /* Release reset signal of IOE_I2C IP */
  RCC_APB1PeriphResetCmd(IOE_I2C_CLK, DISABLE);
  
  /* IOE_I2C SCL and SDA pins configuration */
  GPIO_InitStructure.GPIO_Pin = IOE_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(IOE_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = IOE_I2C_SDA_PIN;
  GPIO_Init(IOE_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(IOE_I2C_SCL_GPIO_PORT, IOE_I2C_SCL_SOURCE, IOE_I2C_SCL_AF);
  GPIO_PinAFConfig(IOE_I2C_SDA_GPIO_PORT, IOE_I2C_SDA_SOURCE, IOE_I2C_SDA_AF);  
}

/**
  * @brief  Configure the I2C Peripheral used to communicate with IO_Expanders.
  * @param  None
  * @retval None
  */
static void IOE_I2C_Config(void)
{
  I2C_InitTypeDef I2C_InitStructure;
  
  /* IOE_I2C configuration */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = 0x00;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = I2C_SPEED;
  
  I2C_Init(IOE_I2C, &I2C_InitStructure);
}

/**
  * @brief  Configure the DMA Peripheral used to handle communication via I2C.
  * @param  None
  * @retval None
  */

static void IOE_DMA_Config(IOE_DMADirection_TypeDef Direction, uint8_t* buffer)
{
  DMA_InitTypeDef DMA_InitStructure;
  
  RCC_AHB1PeriphClockCmd(IOE_DMA_CLK, ENABLE);
  
  /* Initialize the DMA_Channel member */
  DMA_InitStructure.DMA_Channel = IOE_DMA_CHANNEL;
  
  /* Initialize the DMA_PeripheralBaseAddr member */
  DMA_InitStructure.DMA_PeripheralBaseAddr = IOE_I2C_DR;
  
  /* Initialize the DMA_Memory0BaseAddr member */
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)buffer;
  
  /* Initialize the DMA_PeripheralInc member */
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  
  /* Initialize the DMA_MemoryInc member */
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  
  /* Initialize the DMA_PeripheralDataSize member */
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  
  /* Initialize the DMA_MemoryDataSize member */
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  
  /* Initialize the DMA_Mode member */
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  
  /* Initialize the DMA_Priority member */
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  
  /* Initialize the DMA_FIFOMode member */
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
  
  /* Initialize the DMA_FIFOThreshold member */
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
  
  /* Initialize the DMA_MemoryBurst member */
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  
  /* Initialize the DMA_PeripheralBurst member */
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  
  /* If using DMA for Reception */
  if (Direction == IOE_DMA_RX)
  {    
    /* Initialize the DMA_DIR member */
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    
    /* Initialize the DMA_BufferSize member */
    DMA_InitStructure.DMA_BufferSize = 2;
    
    DMA_DeInit(IOE_DMA_RX_STREAM);
    
    DMA_Init(IOE_DMA_RX_STREAM, &DMA_InitStructure);
  }
  /* If using DMA for Transmission */
  else if (Direction == IOE_DMA_TX)
  { 
    /* Initialize the DMA_DIR member */
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    
    /* Initialize the DMA_BufferSize member */
    DMA_InitStructure.DMA_BufferSize = 1;
    
    DMA_DeInit(IOE_DMA_TX_STREAM);
    
    DMA_Init(IOE_DMA_TX_STREAM, &DMA_InitStructure);
  }
}

/*
******************************************************************************
  Function:       LIS33DE_Init
  
  Description:    Init LIS33DR I2C Interface
  Calls:          
  Called By:      
  Input:          
  Output:         
  Return:
  Others:		 
******************************************************************************
*/
void LIS33DE_Init(void)
{
	IOE_GPIO_Config();
	IOE_I2C_Config();
	/* sEE_I2C Peripheral Enable */
	I2C_Cmd(IOE_I2C, ENABLE);
}

/**
  * @brief  Writes a value in a register of the device through I2C.
  * @param  DeviceAddr: The address of the DeviceAddr
  * @param  RegisterAddr: The address register address
  * @param  RegisterValue: The address register value to be written 
  * @retval IOE_OK: if all operations are OK. Other value if error.
  */
uint8_t I2C_WriteDeviceRegister(uint8_t DeviceAddr, uint8_t RegisterAddr, uint8_t RegisterValue)
{
  uint8_t read_verif = 0;
  uint8_t IOE_BufferTX = 0;
  
  /* Get Value to be written */
  IOE_BufferTX = RegisterValue;
  
  /* Configure DMA Peripheral */
  IOE_DMA_Config(IOE_DMA_TX, (uint8_t*)(&IOE_BufferTX));
  
  /* Enable the I2C peripheral */
  I2C_GenerateSTART(IOE_I2C, ENABLE);
  
  /* Test on SB Flag */
  IOE_TimeOut = TIMEOUT_MAX;
  while (I2C_GetFlagStatus(IOE_I2C,I2C_FLAG_SB) == RESET) 
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }
  
  /* Transmit the slave address and enable writing operation */
  I2C_Send7bitAddress(IOE_I2C, DeviceAddr, I2C_Direction_Transmitter);
  
  /* Test on ADDR Flag */
  IOE_TimeOut = TIMEOUT_MAX;
  while (!I2C_CheckEvent(IOE_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }
  
  /* Transmit the first address for r/w operations */
  I2C_SendData(IOE_I2C, RegisterAddr);
  
  /* Test on TXE FLag (data dent) */
  IOE_TimeOut = TIMEOUT_MAX;
  while ((!I2C_GetFlagStatus(IOE_I2C,I2C_FLAG_TXE)) && (!I2C_GetFlagStatus(IOE_I2C,I2C_FLAG_BTF)))  
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }
  
  /* Enable I2C DMA request */
  I2C_DMACmd(IOE_I2C,ENABLE);
  
  /* Enable DMA TX Channel */
  DMA_Cmd(IOE_DMA_TX_STREAM, ENABLE);
  
  /* Wait until DMA Transfer Complete */
  IOE_TimeOut = TIMEOUT_MAX;
  while (!DMA_GetFlagStatus(IOE_DMA_TX_STREAM,IOE_DMA_TX_TCFLAG))
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }  
  
  /* Wait until BTF Flag is set before generating STOP */
  IOE_TimeOut = 2 * TIMEOUT_MAX;
  while ((!I2C_GetFlagStatus(IOE_I2C,I2C_FLAG_BTF)))  
  {
  }
  
  /* Send STOP Condition */
  I2C_GenerateSTOP(IOE_I2C, ENABLE);
  
  /* Disable DMA TX Channel */
  DMA_Cmd(IOE_DMA_TX_STREAM, DISABLE);
  
  /* Disable I2C DMA request */  
  I2C_DMACmd(IOE_I2C,DISABLE);
  
  /* Clear DMA TX Transfer Complete Flag */
  DMA_ClearFlag(IOE_DMA_TX_STREAM,IOE_DMA_TX_TCFLAG);
  
#ifdef VERIFY_WRITTENDATA
  /* Verify (if needed) that the loaded data is correct  */
  
  /* Read the just written register*/
  read_verif = I2C_ReadDeviceRegister(DeviceAddr, RegisterAddr);
  /* Load the register and verify its value  */
  if (read_verif != RegisterValue)
  {
    /* Control data wrongly transfered */
    read_verif = IOE_FAILURE;
  }
  else
  {
    /* Control data correctly transfered */
    read_verif = 0;
  }
#endif
  
  /* Return the verifying value: 0 (Passed) or 1 (Failed) */
  return (read_verif);
}

/**
  * @brief  Reads a register of the device through I2C.
  * @param  DeviceAddr: The address of the device
  * @param  RegisterAddr: The target register address
  * @retval The value of the read register (0xAA if Timeout occurred)
  */
uint8_t I2C_ReadDeviceRegister(uint8_t DeviceAddr, uint8_t RegisterAddr)
{
  uint8_t IOE_BufferRX[2] = {0x00, 0x00};  
  
  /* Configure DMA Peripheral */
  IOE_DMA_Config(IOE_DMA_RX, (uint8_t*)IOE_BufferRX);
  
  /* Enable DMA NACK automatic generation */
  I2C_DMALastTransferCmd(IOE_I2C, ENABLE);
  
  /* Enable the I2C peripheral */
  I2C_GenerateSTART(IOE_I2C, ENABLE);
  
  /* Test on SB Flag */
  IOE_TimeOut = TIMEOUT_MAX;
  while (!I2C_GetFlagStatus(IOE_I2C,I2C_FLAG_SB)) 
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }
  
  /* Send device address for write */
  I2C_Send7bitAddress(IOE_I2C, DeviceAddr, I2C_Direction_Transmitter);
  
  /* Test on ADDR Flag */
  IOE_TimeOut = TIMEOUT_MAX;
  while (!I2C_CheckEvent(IOE_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) 
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }
  
  /* Send the device's internal address to write to */
  I2C_SendData(IOE_I2C, RegisterAddr);  
  
  /* Test on TXE FLag (data dent) */
  IOE_TimeOut = TIMEOUT_MAX;
  while ((!I2C_GetFlagStatus(IOE_I2C,I2C_FLAG_TXE)) && (!I2C_GetFlagStatus(IOE_I2C,I2C_FLAG_BTF)))  
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }
  
  /* Send START condition a second time */  
  I2C_GenerateSTART(IOE_I2C, ENABLE);
  
  /* Test on SB Flag */
  IOE_TimeOut = TIMEOUT_MAX;
  while (!I2C_GetFlagStatus(IOE_I2C,I2C_FLAG_SB)) 
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }
  
  /* Send IOExpander address for read */
  I2C_Send7bitAddress(IOE_I2C, DeviceAddr, I2C_Direction_Receiver);
  
  /* Test on ADDR Flag */
  IOE_TimeOut = TIMEOUT_MAX;
  while (!I2C_CheckEvent(IOE_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))   
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }
    
  /* Enable I2C DMA request */
  I2C_DMACmd(IOE_I2C,ENABLE);
  
  /* Enable DMA RX Channel */
  DMA_Cmd(IOE_DMA_RX_STREAM, ENABLE);
  
  /* Wait until DMA Transfer Complete */
  IOE_TimeOut = 2 * TIMEOUT_MAX;
  while (!DMA_GetFlagStatus(IOE_DMA_RX_STREAM,IOE_DMA_RX_TCFLAG))
  {
    if (IOE_TimeOut-- == 0) return(IOE_TimeoutUserCallback());
  }        
  
  /* Send STOP Condition */
  I2C_GenerateSTOP(IOE_I2C, ENABLE);
  
  /* Disable DMA RX Channel */
  DMA_Cmd(IOE_DMA_RX_STREAM, DISABLE);
  
  /* Disable I2C DMA request */  
  I2C_DMACmd(IOE_I2C,DISABLE);
  
  /* Clear DMA RX Transfer Complete Flag */
 DMA_ClearFlag(IOE_DMA_RX_STREAM,IOE_DMA_RX_TCFLAG);
  
  /* return a pointer to the IOE_Buffer */
  return (uint8_t)IOE_BufferRX[0];
}

