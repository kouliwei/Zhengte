#ifndef __MOTOR_H
#define __MOTOR_H

#include "include.h"


#ifdef __cplusplus
 extern "C" {
#endif
	
#define FOREWARD 0
#define BACKWARD 1
	 
	 
	 
#define NORMAL_MAX_SPEED 				400000
#define SLOW_MAX_SPEED 					100000	  
#define SLOW_DANGWEI  					2000
#define UP_DANGWEI 							2000

	 

#define ISDIR_FOREWARD()    gl_DirFlag == FOREWARD
#define ISDIR_BACKWARD()    gl_DirFlag == BACKWARD

#define DIR_FOREWARD()      gl_DirFlag = FOREWARD
#define DIR_BACKWARD()      gl_DirFlag = BACKWARD


#define ISEFF_MOTOR()       gl_motor == 1
#define EFF_MOTOR()         gl_motor = 1
#define NONEFF_MOTOR()      gl_motor = 0
	 
	 
/************************电机控制定时中断相关宏****************************/
#define MOTOR_TIM           TIM5
#define MOTOR_CLK           20
#define MOTOR_IRQHandler    TIM5_IRQHandler
#define MOTOR_IT_ENABLE() 	TIM_ITConfig(MOTOR_TIM,TIM_IT_Update,ENABLE)
#define MOTOR_IT_DISABLE() 	TIM_ITConfig(MOTOR_TIM,TIM_IT_Update,DISABLE)
#define MOTOR_Cmd_ENABLE()  TIM_Cmd(MOTOR_TIM,ENABLE)
#define MOTOR_Cmd_DISABLE() TIM_Cmd(MOTOR_TIM,DISABLE)


static void motor_out(int32_t * PWM); 
static void dangwei_control(int32_t * PWM);
extern void motor_control(void);
extern void motor_stop(void);

#ifdef __cplusplus
}
#endif

#endif

