#ifndef __USART_H
#define __USART_H

#include "include.h"


#ifdef __cplusplus
 extern "C" {
#endif
	 
	 

typedef enum 
{
  COM1 = 0,
  COM2 = 1
} COM_TypeDef;  

	 


/**
 * @brief Definition for COM port1, connected to USART3
 */ 
	 
#define COMn                            2 
#define EVAL_COM1                       USART3
#define EVAL_COM1_CLK                   RCC_APB1Periph_USART3
#define EVAL_COM1_TX_PIN                GPIO_Pin_10
#define EVAL_COM1_TX_GPIO_PORT          GPIOC
#define EVAL_COM1_TX_GPIO_CLK           RCC_AHB1Periph_GPIOC
#define EVAL_COM1_TX_SOURCE             GPIO_PinSource10
#define EVAL_COM1_TX_AF                 GPIO_AF_USART3
#define EVAL_COM1_RX_PIN                GPIO_Pin_11
#define EVAL_COM1_RX_GPIO_PORT          GPIOC
#define EVAL_COM1_RX_GPIO_CLK           RCC_AHB1Periph_GPIOC
#define EVAL_COM1_RX_SOURCE             GPIO_PinSource11
#define EVAL_COM1_RX_AF                 GPIO_AF_USART3
#define EVAL_COM1_IRQn                  USART3_IRQn
#define EVAL_COM1_IRQHandler            USART3_IRQHandler

#define EVAL_RXFINISH()                 USART_GetFlagStatus(EVAL_COM1,USART_FLAG_RXNE) == SET
#define EVAL_RXNONFINISH()              USART_GetFlagStatus(EVAL_COM1,USART_FLAG_RXNE) == RESET
#define EVAL_CLEARRX()                  USART_ClearFlag(EVAL_COM1,USART_FLAG_RXNE)
#define EVAL_RXDATA()                   ch = USART_ReceiveData(EVAL_COM1)

/*****************WIFI Configuration *********************/
//USART2_RX	PD6
//USART2_TX	PD5
//Link	PE3
//D2_RST	PE2
//Ready	PE4

#define EVAL_COM2                       USART2
#define EVAL_COM2_CLK                   RCC_APB1Periph_USART2
#define EVAL_COM2_TX_PIN                GPIO_Pin_5
#define EVAL_COM2_TX_GPIO_PORT          GPIOD
#define EVAL_COM2_TX_GPIO_CLK           RCC_AHB1Periph_GPIOD
#define EVAL_COM2_TX_SOURCE             GPIO_PinSource5
#define EVAL_COM2_TX_AF                 GPIO_AF_USART2
#define EVAL_COM2_RX_PIN                GPIO_Pin_6
#define EVAL_COM2_RX_GPIO_PORT          GPIOD
#define EVAL_COM2_RX_GPIO_CLK           RCC_AHB1Periph_GPIOD
#define EVAL_COM2_RX_SOURCE             GPIO_PinSource6
#define EVAL_COM2_RX_AF                 GPIO_AF_USART2
#define EVAL_COM2_IRQn                  USART2_IRQn
#define EVAL_COM2_IRQHandler            USART2_IRQHandler



	 

	 
/******************USART  发送数据定时中断相关宏定义***************************/
#define Tx_TIM                      TIM4
#define Tx_CLK                      20
#define Tx_IRQHandler               TIM4_IRQHandler
#define Tx_Enable()                 TIM_ITConfig(Tx_TIM,TIM_IT_Update,ENABLE)           //定时发送中断使能
#define Tx_Cmd() 										TIM_Cmd(Tx_TIM,ENABLE)
#define Tx_Disable()                TIM_ITConfig(Tx_TIM,TIM_IT_Update,DISABLE)          //定时发送中断禁能   
#define Rx_Enable()                 USART_ITConfig(EVAL_COM2,USART_IT_RXNE,ENABLE)      //串口接收中断使能
#define Rx_Disable()                USART_ITConfig(EVAL_COM2,USART_IT_RXNE,DISABLE)      //串口接收中断禁能


/*************USART  configuration***********************/
extern void USART_Config(uint32_t BaudRate,COM_TypeDef COM);
extern void TXD_USART_Buff(USART_TypeDef * USARTx);



/*****************interpret*************************/
/*****TXD_ERROR_MODE1(); senser error detection
******TXD_ERROR_MODE3(); position error detection
******TXD_ACTIVE_MODE1(); send state information
******TXD_ACTIVE_MODE2(); correct number of the car
******TXD_ACTIVE_MODE3(); correct number of the car
******TXD_ACTIVE_MODE4(); correct number of the car
******TXD_CONFIG(); send configuration information

*/

extern void TXD_USART(USART_TypeDef* USARTx,uint16_t data,int8_t type);
static void TXD_USART_DEC(USART_TypeDef* USARTx,uint16_t data);
static void TXD_USART_HEX(USART_TypeDef* USARTx,uint16_t data);
static void TXD_USART_BIN(USART_TypeDef* USARTx,uint16_t data);
static void TXD_USART_CHAR(USART_TypeDef* USARTx,uint16_t data);
extern void TXD_ACTIVE_MODE1(USART_TypeDef* USARTx);
static void TXD_ACTIVE_MODE2(USART_TypeDef* USARTx);
static void TXD_ACTIVE_MODE3(USART_TypeDef* USARTx);
static void TXD_ACTIVE_MODE4(USART_TypeDef* USARTx);
static void TXD_CONFIG(USART_TypeDef* USARTx);
extern void TXD_PASSIVE_MODE1(USART_TypeDef* USARTx);
static void TXD_PASSIVE_MODE2(USART_TypeDef* USARTx);
extern void TXD_ERROR(USART_TypeDef* USARTx,uint8_t error_type,uint8_t position,uint8_t senser);
static void TXD_ERROR_MODE1(USART_TypeDef* USARTx,uint8_t position,uint8_t senser_type);
static void TXD_ERROR_MODE2(USART_TypeDef* USARTx);
extern void TXD_ERROR_MODE3(USART_TypeDef* USARTx);
extern void TXD_DINGWEI(USART_TypeDef* USARTx,uint8_t Type);

#ifdef __cplusplus
}
#endif

#endif

