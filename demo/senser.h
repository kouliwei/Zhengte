#ifndef __SENSER_H
#define __SENSER_H



#ifdef __cplusplus
 extern "C" {
#endif
	 
	 
#include  "include.h"
	
extern void Start_Car(void);	 
extern void Senser_Detect_Mode1(void);
extern void Senser_Detect_Mode2(void);
extern void Senser_Detect_Mode3(void);	 
extern void Senser_Detect_Mode4(void);
extern void Shang_Xian(void);
extern void Dian_Dong(void);
extern void Inter_Action(void);
extern void Zheng_Chang(void);
extern void Chang_Num(void);
extern void Change_Speed(void);
extern void Start(void);
extern void Slow(void);
extern void Stop(void);
static void Change_Multi_Flag(void);
static void Senser_Detect(uint8_t* Senser0_Flag,uint8_t* Senser1_Flag,uint8_t* Senser2_Flag,uint8_t* Senser3_Flag,uint8_t* Senser4_Flag,uint8_t* Senser5_Flag,uint8_t* Senser6_Flag,uint8_t* Senser7_Flag,uint8_t* Senser8_Flag,uint8_t* Senser9_Flag);
static void Update_Pos_Opr(void);
#ifdef __cplusplus
}
#endif

#endif
