#ifndef   _TEST_H_
#define   _TEST_H_


#ifdef __cplusplus
 extern "C" {
#endif

#include  "include.h"
	 
	

#if    DEBUG == 0
extern void Test(void);
static void first(void);
static void Led_Test(void);
static void Key_Test(void);
static void Senser_Test(void);
static void Pwm_Test(void);
static void Led_Mode1(void);
static void Led_Mode2(void);
#endif 



	 

#ifdef __cplusplus
}
#endif


#endif
