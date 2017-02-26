#ifndef __INCLUDE_H
#define __INCLUDE_H



#ifdef __cplusplus
 extern "C" {
#endif

	 
/*****************DEBUG  definition************************/
/****************if DEBUG == 0:  motor test****************/
/****************if DEBUG == 1:  serial communication test*/
/****************if DEBUG == 2:  senser test*************8*/
/****************if DEBUG == 3:  I2C    test***************/
/****************if DEBUG == 4:  normal mode  but Hyper termial ***************/
/****************if DEBUG == 5:  normal mode  and normal terminal ***************/	 
	 
#define DEBUG   5
	 
#define TRUE 	1
#define FALSE 0 


/*****************symtem************************/ 
#include "stm32f2xx.h"
#include "stm32f2xx_conf.h"
#include "stm32f2xx_it.h"
#include <stdio.h>
	 
	 
	 
/******************user*************************/
#include  "user.h"
#include  "adc.h" 
#include  "common.h"
#include  "usart.h"
#include  "test.h"	 
#include  "nvic.h"
#include  "time.h"
#include  "pwr.h"
#include  "motor.h"
#include  "i2c.h"
#include  "senser.h"
#include  "abnormal.h"
#include  "car.h"
#include  "flash.h"
#include  "lcd_key.h"

extern uint8_t gl_Tim12Flag ;
extern uint8_t gl_ResetFlag1;
extern uint8_t gl_ResetFlag;
extern uint8_t gl_OpenFlag[2];
extern uint8_t gl_ErrorData_Flag;
extern uint8_t gl_Flag7;
extern uint8_t gl_Flag6;
extern uint8_t gl_SpePos[4];
extern uint8_t gl_Flag5;
extern uint8_t gl_Flag4;
extern uint8_t gl_DaoWeiFlag; 
extern uint8_t gl_Flag3;
extern uint8_t gl_Daowei;
extern int32_t gl_pwm;
extern int32_t gl_pwmslow ;
extern int32_t gl_pwmcolli;
extern uint8_t gl_AlertFlag;
extern uint8_t gl_Status[6];  
extern uint8_t gl_DingweiRightData_Flag;
extern uint8_t gl_DingweiErrorData_Flag;
extern uint8_t gl_DingweiPos[3];
extern uint8_t gl_VirStart_Flag;
extern uint8_t gl_CheckStop_Flag[2];
extern uint8_t gl_SlowDownErrorData_Flag;
extern uint8_t gl_StopErrorData_Flag;
extern uint8_t gl_SlowDownRightData_Flag ;
extern uint8_t gl_StopRightData_Flag ;
extern uint8_t gl_Senser_Flag[6];
extern uint8_t gl_Multi_Flag;
extern uint8_t gl_Double_Flag;
extern uint8_t gl_Double_Pos_x[3];
extern uint8_t gl_Double_Pos_y[3];
extern uint8_t gl_Init_Flag ;
extern uint8_t gl_AlertStopFlag;
extern uint8_t gl_CheckFlag;
extern uint8_t gl_CheckFlag1;
extern uint8_t gl_Speed1;     
extern uint8_t gl_Speed2 ;
extern uint8_t gl_SpeedUp;
extern uint8_t gl_SlowDown;
extern uint8_t gl_JiTingFlag;
extern uint8_t gl_flagStop;
extern uint8_t gl_flagRx[2];
extern uint8_t gl_CorrectNumFlag;
extern uint8_t gl_flag2;
extern uint8_t gl_flag1;
extern uint8_t gl_flag;
extern uint8_t gl_Buff[255];
extern uint8_t gl_TxBuff[255];
extern uint8_t gl_RxRight;
extern uint8_t gl_TxFlag;
extern uint8_t gl_RxLen;
extern uint16_t gl_FreRate;
extern uint8_t gl_Store[250];
extern uint8_t gl_Restore[250];
extern uint8_t gl_StartFlag ;
extern uint8_t gl_SlowFlag ;
extern uint8_t gl_ColliFlag ;
extern uint8_t gl_StopFlag ;
extern uint8_t gl_Right;
extern uint8_t gl_Left;
extern uint8_t gl_posFlag[30] ;
extern uint8_t gl_pos2opr[30];
extern uint8_t gl_oprDis[21] ;
extern uint8_t gl_DirFlag;
extern uint8_t gl_DirFlag1;
extern Car gl_car ;
extern uint8_t gl_car_all ;
extern uint8_t gl_opr;
extern uint8_t gl_pos;
extern uint8_t gl_motor;
extern uint8_t gl_car_state ;
extern volatile uint16_t NumDataRead ;
	 
	 
#ifdef __cplusplus
}
#endif

#endif
