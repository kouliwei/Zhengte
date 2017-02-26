#include "abnormal.h"

extern void hardware_detect(void)
{
    PFO_detect();
    WIFI_detect();

}

static void PFO_detect(void)
{
    uint8_t i = 0,j = 0;
    for(i = 0 ;i < 10 ; i ++)
    {
        if(ISEFF_PFO())
        {
            Delay_Nms(500);
            j++;
        }
    }

    if(j > 6) //如果检测低电压次数大于6次，说明供电有问题
    {
        printf("error \r\n");
        while(1);
    }
}

static void WIFI_detect(void)
{
	
}
