#ifndef __CAR_H
#define __CAR_H



#ifdef __cplusplus
 extern "C" {
#endif
	 
	 
#include  "include.h"
	
	 
extern void Car_Config_Mode(void);
extern void Control_Mode1(void);
extern void Control_Mode2(void);
extern void Control_Mode3(void);
extern void Control_Mode4(void);
extern void Normal_Mode(void);
extern void Load_Config(void);
extern void Init_State(void);
extern void Change_PosFlag(uint8_t *Temp_Data);
extern void Board_Init(void);
static void Board_Init_Mode(void);
static void Data_Inter(void);
	 
	 
#ifdef __cplusplus
}
#endif

#endif
