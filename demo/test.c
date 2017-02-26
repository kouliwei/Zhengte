#include "include.h"


#if  DEBUG == 0
void Test(void)
{
    uint8_t ch = 0;
    uint8_t exit_flag = 0;
    uint8_t flag = 0;
    
    while(1){
        if(0 == flag){
            printf("\r\n**************welcome to the menu****************\r\n");
            printf("press a or A to enter the motor control\r\n");
            printf("press b or B to enter the Led control\r\n");
            printf("press c or C to enter the Key control \r\n");
            printf("press d or D to enter the Senser control \r\n");
            printf("press e or E to exit the menu\r\n");
            flag = 1;
        }

        while(USART_GetFlagStatus(EVAL_COM2, USART_FLAG_RXNE) == RESET);
        USART_ClearFlag(EVAL_COM2, USART_FLAG_RXNE);
        ch = USART_ReceiveData(EVAL_COM2);
        switch(ch){
            case 'a':
            case 'A':
                first();
                flag = 0;
                break;
            case 'b':
            case 'B':
                Led_Test();
                flag = 0;
                break;
            case 'c':
            case 'C':
                Key_Test();
                flag = 0;
                break;
            case 'd':
            case 'D':
                Senser_Test();
                flag = 0;
                break;
            case 'e':
            case 'E':
                printf("go home now\t\n");
                exit_flag = 1;
                break;
        }
        if(exit_flag == 1)
            break;
    }
}

 
static void first(void)
 {
     uint8_t ch = 0;
     uint8_t exit_flag = 0;
     uint8_t flag = 0;
     while(1){
         if(0 == flag){
             printf("\r\n******welcome to the motor control**********\r\n");
             printf("press a or A to start the motor\r\n");
             printf("press w or W to speed up\r\n");
             printf("press s or S to shift down\r\n");
             printf("press d or D to stop the motor\r\n");
             printf("press e or E to exit the menu\r\n");
             flag = 1;
         }
         
         while(USART_GetFlagStatus(EVAL_COM2, USART_FLAG_RXNE) == RESET);
         USART_ClearFlag(EVAL_COM2, USART_FLAG_RXNE);
         ch = USART_ReceiveData(EVAL_COM2);
         switch(ch){
             case 'a':
             case 'A':
                 gl_FreRate = 1;
                 break;
             case 'w':
             case 'W':
                 if(gl_FreRate >= 15)
                 {
                     gl_FreRate = 15;
                 }
                 else
                 {
                     gl_FreRate += 1;
                 }
                 break;
             case 's':
             case 'S':
                 if(gl_FreRate > 0)
                 {
                     gl_FreRate = gl_FreRate - 1;
                 }
                 break;
             case 'd':
             case 'D':
                 gl_FreRate = 0;
                 break;
             case 'e':
             case 'E':
                 if(gl_FreRate != 0)
                 {
                     printf("Exit Failed \r\n");
                 }
                 else 
                 {
                     exit_flag = 1;	
                     printf("Exit Success \r\n");					
                 }
         }
         Pwm_Test();
         printf("the value of gl_FreRate is %d\r\n",gl_FreRate);
         if(exit_flag == 1)
             break;
     }
}



 
static void Pwm_Test(void)
{
    uint32_t Period[20]={0,2000,4000,6000,8000,10000,12000,3500,4000,4500,5000,5500,6000,6500,7000,7500,8000,};
    if(gl_FreRate == 0)
        TIM2->CCR3 = Period[0];
    else
    {
        TIM2->ARR = (uint32_t)(60000000/((uint32_t)gl_FreRate*2000)-1);
        TIM2->CCR3 = TIM2->ARR / 2;
    }
}
 
 

static void Led_Test(void)
 {
     uint8_t ch = 0;
     uint8_t exit_flag = 0;
     uint8_t flag = 0;
     while(1){
         printf("\r\n******welcome to the Led_Test *********\r\n");
         printf("press a or A to the drive the led_mode1\r\n");
         printf("press w or W to the drive the led_mode2\r\n");
         printf("press e or E to exit the Led_Test\r\n");
         
         while(USART_GetFlagStatus(EVAL_COM2, USART_FLAG_RXNE) == RESET);
         USART_ClearFlag(EVAL_COM2, USART_FLAG_RXNE);
         ch = USART_ReceiveData(EVAL_COM2);
         switch(ch){
             case 'a':
             case 'A':
                 Led_Mode1();
                 break;
             case 'w':
             case 'W':
                 Led_Mode2();
                 break;
             case 'e':
             case 'E':
                 printf("exit the Led_Test Led\r\n");
                 exit_flag = 1;			
         }
         if(exit_flag == 1)
             break;
     }
}


/**********跑马灯模式***************/
void Led_Mode1()
{
    uint8_t i = 0;
    for(i = 0;i < 4; i++)
    {
        switch(i)
        {
            case 0:
                Led_Drive(0x01);
                break;
            case 1:
                Led_Drive(0x02);
                break;
            case 2:
                Led_Drive(0x04);
                break;
            case 3:
                Led_Drive(0x08);
                break;
        }
        Delay_Nms(500);
    }
}

/*********全亮全灭模式**************/
void Led_Mode2()
{
    uint8_t i = 0;
    for(i = 0;i < 4;i ++)
    {
        if(i % 2)
        {
            Led_Drive(0x0f);
        }
        else
        {
            Led_Drive(0x00);
        }
        Delay_Nms(500);
    }


}


static void Key_Test(void)
{
    uint8_t ch = 0;
    uint16_t data = 0;
    uint8_t i =0;
    printf("press e or E to exit the Key_Test\r\n");
    
    while(1)
    { 

        if(EFF_VAL_KEY1())
        {
            data |= 0x01;
        }
        else
        {
            data &= ~(0x01);
        }
        if(EFF_VAL_KEY2())
        {
            data |= 0x02;
        }
        else
        {
            data &= ~(0x02);
        }
        if(EFF_VAL_KEY3())
        {
            data |= 0x04;
        }
        else
        {
            data &= ~(0x04);
        }
        if(EFF_VAL_KEY4())
        {
            data |= 0x08;
        }
        else
        {
            data &= ~(0x08);
        }
        Delay_Nms(500);
        TXD_USART(EVAL_COM2,data,2);
        if(USART_GetFlagStatus(EVAL_COM2,USART_FLAG_RXNE) == SET)
        {
            USART_ClearFlag(EVAL_COM2,USART_FLAG_RXNE);
            ch = USART_ReceiveData(EVAL_COM2);
            if(ch == 'e' || ch == 'E')
                break;
        }
    } 
}



static void Senser_Test(void)
{
    uint8_t ch = 0;
    uint16_t data = 0;
    uint8_t i =0;
    printf("press e or E to exit the Senser Test\r\n");
    
    while(1)
    { 

        if(EFF_VAL_SENSER0())
        {
            data |= 0x0001;
        }
        else
        {
            data &= ~(0x0001);
        }
        if(EFF_VAL_SENSER1())
        {
            data |= 0x0002;
        }
        else
        {
            data &= ~(0x0002);
        }
        if(EFF_VAL_SENSER2())
        {
            data |= 0x0004;
        }
        else
        {
            data &= ~(0x0004);
        }
        if(EFF_VAL_SENSER3())
        {
            data |= 0x0008;
        }
        else
        {
            data &= ~(0x0008);
        }
        if(EFF_VAL_SENSER4())
        {
            data |= 0x0010;
        }
        else
        {
            data &= ~(0x0010);
        }
        if(EFF_VAL_SENSER5())
        {
            data |= 0x0020;
        }
        else
        {
            data &= ~(0x0020);
        }
        if(EFF_VAL_SENSER6())
        {
            data |= 0x0040;
        }
        else
        {
            data &= ~(0x0040);
        }
        if(EFF_VAL_SENSER7())
        {
            data |= 0x0080;
        }
        else
        {
            data &= ~(0x0080);
        }       
        if(EFF_VAL_SENSER8())
        {
            data |= 0x0100;
        }
        else
        {
            data &= ~(0x0100);
        }
        if(EFF_VAL_SENSER9())
        {
            data |= 0x0200;
        }
        else
        {
            data &= ~(0x0200);
        }
        if(EFF_VAL_SENSER10())
        {
            data |= 0x0400;
        }
        else
        {
            data &= ~(0x0400);
        }
        if(EFF_VAL_SENSER11())
        {
            data |= 0x0800;
        }
        else
        {
            data &= ~(0x0800);
        }
        if(EFF_VAL_SENSER12())
        {
            data |= 0x1000;
        }
        else
        {
            data &= ~(0x1000);
        }
        if(EFF_VAL_SENSER13())
        {
            data |= 0x2000;
        }
        else
        {
            data &= ~(0x2000);
        }

        Delay_Nms(500);
        TXD_USART(EVAL_COM2,data,2);
        if(USART_GetFlagStatus(EVAL_COM2,USART_FLAG_RXNE) == SET)
        {
            USART_ClearFlag(EVAL_COM2,USART_FLAG_RXNE);
            ch = USART_ReceiveData(EVAL_COM2);
            if(ch == 'e' || ch == 'E')
                break;
        }
    } 
}
#endif
