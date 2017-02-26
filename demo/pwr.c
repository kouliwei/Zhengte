#include "pwr.h"


extern void Sys_Standby(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	PWR_WakeUpPinCmd(ENABLE);
	PWR_EnterSTANDBYMode();
}

extern void Sys_Enter_Standby(void)
{
	/**************πÿ±’ ±÷”**********************/
	RCC_AHB1PeriphResetCmd( 0x226011FF, DISABLE );
  RCC_AHB2PeriphResetCmd( 0x000000F1, DISABLE );
  RCC_AHB3PeriphResetCmd( 0x00000001, DISABLE );
  RCC_APB1PeriphResetCmd( 0x36FEC9FF, DISABLE );
  RCC_APB2PeriphResetCmd( 0x00075933, DISABLE );
	
	Sys_Standby();
}


