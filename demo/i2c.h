#ifndef __I2C_H
#define __I2C_H


#include "include.h"

#ifdef __cplusplus
 extern "C" {
#endif
	 
#define ADDRESS0_INARRAY          60   //gl_opr
#define ADDRESS1_INARRAY          61   //gl_car.opr 
#define ADDRESS2_INARRAY          62   //gl_car.pos
#define ADDRESS3_INARRAY          63   //gl_DirFlag
#define ADDRESS4_INARRAY          64   //gl_car.num
#define ADDRESS5_INARRAY          65   //gl_Speed1
#define ADDRESS6_INARRAY          66   //gl_Speed2
#define ADDRESS7_INARRAY          67   //gl_DirFlag1
#define ADDRESS8_INARRAY          68   //gl_SpeedUp
#define ADDRESS9_INARRAY          69   //gl_SlowDown
#define ADDRESS10_INARRAY         70   //gl_car.pos1
#define ADDRESS11_INARRAY         71   //gl_pos
#define ADDRESS12_INARRAY         72   //
#define ADDRESS13_INARRAY         73   //
#define ADDRESS14_INARRAY         74   //
#define ADDRESS15_INARRAY         75   //
#define ADDRESS16_INARRAY         76   //
#define ADDRESS17_INARRAY         77   //
#define ADDRESS18_INARRAY         78   //
#define ADDRESS19_INARRAY         79   //
#define ADDRESS20_INARRAY         80   //
#define ADDRESS21_INARRAY         81   //
#define ADDRESS22_INARRAY         82   //gl_AlertStopFlag 
#define ADDRESS23_INARRAY		      83
#define ADDRESS24_INARRAY  	      84   //gl_flag1

	 
#define ADDRESS0_INEEPROM         62   //gl_opr
#define ADDRESS1_INEEPROM         63	 //gl_car.opr 
#define ADDRESS2_INEEPROM         64   //gl_car.pos
#define ADDRESS3_INEEPROM         65   //gl_DirFlag
#define ADDRESS4_INEEPROM         66   //gl_car.num
#define ADDRESS5_INEEPROM         67   //gl_Speed1
#define ADDRESS6_INEEPROM         68   //gl_Speed2
#define ADDRESS7_INEEPROM         69   //gl_DirFlag1
#define ADDRESS8_INEEPROM         70   //gl_SpeedUp
#define ADDRESS9_INEEPROM         71   //gl_SlowDown
#define ADDRESS10_INEEPROM        72   //gl_car.pos1
#define ADDRESS11_INEEPROM        73   //gl_pos
#define ADDRESS12_INEEPROM        74
#define ADDRESS13_INEEPROM        75
#define ADDRESS14_INEEPROM        76
#define ADDRESS15_INEEPROM        77
#define ADDRESS16_INEEPROM        78
#define ADDRESS17_INEEPROM        79
#define ADDRESS18_INEEPROM        80
#define ADDRESS19_INEEPROM        81
#define ADDRESS20_INEEPROM        82
#define ADDRESS21_INEEPROM        83
#define ADDRESS22_INEEPROM        84    //gl_AlertStopFlag 
#define ADDRESS23_INEEPROM  	    85
#define ADDRESS24_INEEPROM  	    86



	 
#define sEE_WRITE_ADDRESS1        0x00
#define sEE_READ_ADDRESS1         0x00
#define BUFFER_SIZE             (countof(gl_Store)-1)
#define countof(a)              (sizeof(a) / sizeof(*(a)))
#define MAX_SIZE                 8

	 

/******* @brief  I2C EEPROM Interface pins***************/
#define sEE_I2C                          I2C3
#define sEE_I2C_CLK                      RCC_APB1Periph_I2C3
#define sEE_I2C_SCL_PIN                  GPIO_Pin_8                  /* PB.06 */
#define sEE_I2C_SCL_GPIO_PORT            GPIOA                       /* GPIOB */
#define sEE_I2C_SCL_GPIO_CLK             RCC_AHB1Periph_GPIOA
#define sEE_I2C_SCL_SOURCE               GPIO_PinSource8
#define sEE_I2C_SCL_AF                   GPIO_AF_I2C3
#define sEE_I2C_SDA_PIN                  GPIO_Pin_9                  /* PB.09 */
#define sEE_I2C_SDA_GPIO_PORT            GPIOC                       /* GPIOB */
#define sEE_I2C_SDA_GPIO_CLK             RCC_AHB1Periph_GPIOC
#define sEE_I2C_SDA_SOURCE               GPIO_PinSource9
#define sEE_I2C_SDA_AF                   GPIO_AF_I2C3
//#define sEE_M24C64_32
#define sEE_AT24C02

#define sEE_I2C_DMA                      DMA1   
#define sEE_I2C_DMA_CHANNEL              DMA_Channel_3
#define sEE_I2C_DMA_STREAM_TX            DMA1_Stream4
#define sEE_I2C_DMA_STREAM_RX            DMA1_Stream2   
#define sEE_I2C_DMA_CLK                  RCC_AHB1Periph_DMA1
#define sEE_I2C_DR_Address               ((uint32_t)0x40005C10)
#define sEE_USE_DMA
   
#define sEE_I2C_DMA_TX_IRQn              DMA1_Stream4_IRQn
#define sEE_I2C_DMA_RX_IRQn              DMA1_Stream2_IRQn
#define sEE_I2C_DMA_TX_IRQHandler        DMA1_Stream4_IRQHandler
#define sEE_I2C_DMA_RX_IRQHandler        DMA1_Stream2_IRQHandler   
#define sEE_I2C_DMA_PREPRIO              0
#define sEE_I2C_DMA_SUBPRIO              0   
   
#define sEE_TX_DMA_FLAG_FEIF             DMA_FLAG_FEIF4
#define sEE_TX_DMA_FLAG_DMEIF            DMA_FLAG_DMEIF4
#define sEE_TX_DMA_FLAG_TEIF             DMA_FLAG_TEIF4
#define sEE_TX_DMA_FLAG_HTIF             DMA_FLAG_HTIF4
#define sEE_TX_DMA_FLAG_TCIF             DMA_FLAG_TCIF4
#define sEE_RX_DMA_FLAG_FEIF             DMA_FLAG_FEIF2
#define sEE_RX_DMA_FLAG_DMEIF            DMA_FLAG_DMEIF2
#define sEE_RX_DMA_FLAG_TEIF             DMA_FLAG_TEIF2
#define sEE_RX_DMA_FLAG_HTIF             DMA_FLAG_HTIF2
#define sEE_RX_DMA_FLAG_TCIF             DMA_FLAG_TCIF2
   
#define sEE_DIRECTION_TX                 0
#define sEE_DIRECTION_RX                 1  

/* Time constant for the delay caclulation allowing to have a millisecond 
   incrementing counter. This value should be equal to (System Clock / 1000).
   ie. if system clock = 120MHz then sEE_TIME_CONST should be 120. */
#define sEE_TIME_CONST                   120 
	 


	 
/* #define USE_DEFAULT_TIMEOUT_CALLBACK */
   
#if !defined (sEE_M24C08) && !defined (sEE_M24C64_32) && !defined (sEE_AT24C02)
/* Use the defines below the choose the EEPROM type */
/* #define sEE_M24C08*/  /* Support the device: M24C08. */
/* note: Could support: M24C01, M24C02, M24C04 and M24C16 if the blocks and 
   HW address are correctly defined*/
//#define sEE_M24C64_32  /* Support the devices: M24C32 and M24C64 */
#error "you mast define eeprom type"
#endif

#ifdef sEE_M24C64_32
/* For M24C32 and M24C64 devices, E0,E1 and E2 pins are all used for device 
  address selection (ne need for additional address lines). According to the 
  Harware connection on the board (on STM3210C-EVAL board E0 = E1 = E2 = 0) */

 #define sEE_HW_ADDRESS         0xA0   /* E0 = E1 = E2 = 0 */ 

#elif defined (sEE_M24C08)
/* The M24C08W contains 4 blocks (128byte each) with the adresses below: E2 = 0 
   EEPROM Addresses defines */
 #define sEE_Block0_ADDRESS     0xA0   /* E2 = 0 */ 
 /*#define sEE_Block1_ADDRESS     0xA2*/ /* E2 = 0 */  
 /*#define sEE_Block2_ADDRESS     0xA4*/ /* E2 = 0 */
 /*#define sEE_Block3_ADDRESS     0xA6*/ /* E2 = 0 */

#endif /* sEE_M24C64_32 */

/* I2C clock speed configuration (in Hz) 
  WARNING: 
   Make sure that this define is not already declared in other files (ie. 
  stm322xg_eval.h file). It can be used in parallel by other modules. */
#ifndef I2C_SPEED
 #define I2C_SPEED                        100000
#endif /* I2C_SPEED */

#define I2C_SLAVE_ADDRESS7      0xBf

#if defined (sEE_M24C08)
 #define sEE_PAGESIZE           16
#elif defined (sEE_M24C64_32)
 #define sEE_PAGESIZE           32
#elif defined sEE_AT24C02
   #define sEE_PAGESIZE          8
#endif
   
/* Maximum Timeout values for flags and events waiting loops. These timeouts are
   not based on accurate values, they just guarantee that the application will 
   not remain stuck if the I2C communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define sEE_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define sEE_LONG_TIMEOUT         ((uint32_t)(10 * sEE_FLAG_TIMEOUT))

/* Maximum number of trials for sEE_WaitEepromStandbyState() function */
#define sEE_MAX_TRIALS_NUMBER     300
   
/* Defintions for the state of the DMA transfer */   
#define sEE_STATE_READY           0
#define sEE_STATE_BUSY            1
#define sEE_STATE_ERROR           2
   
#define sEE_OK                    0
#define sEE_FAIL                  1   
	 




void sEE_LowLevel_DeInit(void);
void sEE_LowLevel_Init(void);
void sEE_LowLevel_DMAConfig(uint32_t pBuffer, uint32_t BufferSize, uint32_t Direction);


/** @defgroup STM322xG_EVAL_I2C_EE_Exported_Functions
  * @{
  */ 
void     sEE_DeInit(void);
void     sEE_Init(void);
uint32_t sEE_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t* NumByteToRead);
uint32_t sEE_WritePage(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t* NumByteToWrite);
void     sEE_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
uint32_t sEE_WaitEepromStandbyState(void);
uint32_t sEE_TIMEOUT_UserCallback(void);



extern void I2c_Parameter_Read(void);


extern void I2c_Parameter_Write(uint8_t Parameter);



	 
	 
#ifdef __cplusplus
}
#endif

#endif
