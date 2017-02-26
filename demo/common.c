#include "common.h"


//#define _GNUG__

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

	
	
GPIO_TypeDef* GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT, LED3_GPIO_PORT,
                                 LED4_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN,
                                 LED4_PIN};
const uint32_t GPIO_CLK[LEDn] = {LED1_GPIO_CLK, LED2_GPIO_CLK, LED3_GPIO_CLK,
                                 LED4_GPIO_CLK};
																 
GPIO_TypeDef* PORT_GPIO[GPIOn] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,
                                 	GPIOF,GPIOG,GPIOH,GPIOI
                                 };														 
																 
const uint16_t PIN_GPIO[16] = {GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_3,
	                             GPIO_Pin_4, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_7,
	                             GPIO_Pin_8, GPIO_Pin_9, GPIO_Pin_10,GPIO_Pin_11,
	                             GPIO_Pin_12,GPIO_Pin_13,GPIO_Pin_14,GPIO_Pin_15
                               };

const uint8_t SOUC_GPIO[16] ={GPIO_PinSource0, GPIO_PinSource1, GPIO_PinSource2, GPIO_PinSource3,
	                            GPIO_PinSource4, GPIO_PinSource5, GPIO_PinSource6, GPIO_PinSource7,
	                            GPIO_PinSource8, GPIO_PinSource9, GPIO_PinSource10,GPIO_PinSource11,
	                            GPIO_PinSource12,GPIO_PinSource13,GPIO_PinSource14,GPIO_PinSource15
                             };

																 
const uint32_t CLK_GPIO[GPIOn] = {RCC_AHB1Periph_GPIOA,RCC_AHB1Periph_GPIOB,RCC_AHB1Periph_GPIOC,
                                  RCC_AHB1Periph_GPIOD,RCC_AHB1Periph_GPIOE,RCC_AHB1Periph_GPIOF,
                                  RCC_AHB1Periph_GPIOG,RCC_AHB1Periph_GPIOH,RCC_AHB1Periph_GPIOI};



void Led_Init(Led_TypeDef Led)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /**************GPIO  clock enable**********/
    RCC_AHB1PeriphClockCmd(GPIO_CLK[Led],ENABLE);
    
    /**************GPIO Configuration**********/
    GPIO_InitStructure.GPIO_Pin=GPIO_PIN[Led];
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIO_PORT[Led],&GPIO_InitStructure);
    GPIO_SetBits(GPIO_PORT[Led], GPIO_PIN[Led]);
}

static void GPIO_Led_Init(void)
{
    Led_Init(LED1);
    Led_Init(LED2);
    Led_Init(LED3);
    Led_Init(LED4);
}

void Led_On(Led_TypeDef Led)
{
    GPIO_ResetBits(GPIO_PORT[Led], GPIO_PIN[Led]);
}

void Led_Off(Led_TypeDef Led)
{
    GPIO_SetBits(GPIO_PORT[Led], GPIO_PIN[Led]);
}

void Led_Toggle(Led_TypeDef Led)
{
    GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led];
}

void Led_Drive(uint8_t num)
{
    if(num & 0x01)
        Led_On(LED1);
    else
        Led_Off(LED1);
    if(num & 0x02)
        Led_On(LED2);
    else
        Led_Off(LED2);
    if(num & 0x04)
        Led_On(LED3);
    else
        Led_Off(LED3);
    if(num & 0x08)
        Led_On(LED4);
    else
        Led_Off(LED4);
	
}

void Delay(__IO uint32_t nCount)
{
    __IO uint32_t index = 0;
    for(index = (160000 * nCount); index != 0; index--)
    {
    }
}

void Delay_Nms(__IO uint16_t nCount)
{
    uint16_t i = 0;
    for(i = 0;i<nCount;i++)
    {
        Delay_1ms();
    }
}

void Delay_1ms(void)
{
    __IO uint16_t index = 0;
    for(index = 10000;index != 0;index--)
    {
    }
}

void Delay_Nus(__IO uint16_t nCount)
{
    uint16_t i = 0;
    for(i = 0;i<nCount;i++)
    {
        NOP;
    }
}

void Delay_1us(void)
{
    __IO uint16_t index = 0;
    for(index = 3;index != 0;index--)
    {
    }
}





void myiostr(char* str)
{
    uint8_t  i=0;
    for(i=0;str[i]!='\0';i++)
    {
        printf("%c",str[i]);
	}
    printf("\r\n");
}

/*********change float number to array**************/
void float2array(float num,uint8_t* Tx_Buffer)
{

	
	
}

void array2float(float* num,uint8_t* Rx_Buffer)
{
    uint8_t i=0;
    uint8_t n=0;
    float Buffer[8] ={0};
	
    for(i=0;i<8;i++)
    {
        Buffer[i] = Rx_Buffer[i];
    }
	
    *num = Rx_Buffer[2];
    for(i=1;i<Rx_Buffer[0];i++)
    {
        *num = (*num)*10+Rx_Buffer[i+2];
    }
	
    n=2+Rx_Buffer[0];
    for(i=0;i<Rx_Buffer[1];i++)
    {
        *num =(*num)+Buffer[n+i]/My_pow(10,i+1);
    }
}

/*********change int number to array**************/
/****Tx_Buffer[0]保存的是整数的位数,后面的是有效的数字****/
void int2array(uint16_t num,uint8_t* Tx_Buffer)
{
    uint8_t i=0,j=0;
    uint16_t m=0;
	
    if(num <10)
        Tx_Buffer[0] = 1;
    else if(num < 100)
        Tx_Buffer[0] = 2;
    else if(num < 1000)
        Tx_Buffer[0] = 3;
    else if(num <10000)
        Tx_Buffer[0] = 4;
    else
        Tx_Buffer[0] = 5;
	
    for(i=1,j=1;i<=Tx_Buffer[0];i++)
    {
        m = num/My_pow(10,Tx_Buffer[0]-i);
        num = num%My_pow(10,Tx_Buffer[0]-i);
        Tx_Buffer[j] = m;
        j++;
    }
}

void array2int(uint16_t* num,uint8_t* Rx_Buffer)
{
    uint8_t i=1;
    *num =Rx_Buffer[1];
    for(i=1;i<Rx_Buffer[0];i++)
    {
        *num =(*num)*10+Rx_Buffer[i+1];
    }
}

uint16_t My_pow(uint8_t a,uint8_t b)
{
    uint16_t r=a;
    if(b == 0)
    {
        r = 1;
        return r;
    }
    while(--b)
    {
        r*=a;
    }
    return r;
}



extern  void Sys_InitConfig(void)
{
    SystemInit();                       //系统初始化
    Delay_Nms(5000);                    
    USART_Config(115200,COM2);               //串口初始化,中断未开
    Clock_Config(MOTOR_CLK,MOTOR_TIM);  //电机控制定时中断
    Clock_Config(3500,TIM12);           //3500ms 定时中断	
		Clock_Config(200,TIM13); 						//200ms 定时中断
    PWM_Config();                       //PWM初始化
    sEE_Init();                         //I2C初始化
    PFO_EXTI_Config();                  //电压故障外部中断初始化
//    MOTOR_EXTI_Config(); 			   				//伺服报警外部中断初始化
    Clock_Config(Tx_CLK,Tx_TIM);        //串口发送定时中断
//		Encoder_Init();
//    SysTick_Configuration();
//    IWDG_Init();
    NVIC_Config();                      //中断优先级控制
    GPIO_All_Init();                    //GPIO初始化，包括Led 和 senser
//		Board_Init();
}


/*****flag = 0,GPIO OUT;
******flag = 1,GPIO IN*******/
extern void GPIO_Config(GPIO_typedef GPIO_x,uint8_t pin,uint8_t flag)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /**************GPIO clock enable**********/
    RCC_AHB1PeriphClockCmd(CLK_GPIO[GPIO_x],ENABLE);
    
    /**************GPIO Configuration**********/
    GPIO_InitStructure.GPIO_Pin=PIN_GPIO[pin];
    if(flag == 0)
    {
        GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
        GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;		
    }
    else
    {
        GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;	
    }
    GPIO_Init(PORT_GPIO[GPIO_x],&GPIO_InitStructure);
}


/**********************key     configuration***************************/
static void GPIO_Key_Init(void)
{
    GPIO_Config(GPIO_KEY1,Pin_KEY1,Dir_KEY1);
    GPIO_Config(GPIO_KEY2,Pin_KEY2,Dir_KEY2);
    GPIO_Config(GPIO_KEY3,Pin_KEY3,Dir_KEY3);
    GPIO_Config(GPIO_KEY4,Pin_KEY4,Dir_KEY4);

}
/********************Wifi   configuration*****************************/

extern void Wifi_RST(void)
{
	  SET_VAL_RST();        //每次上电时无线模块必须复位
    Delay_Nms(100);
    RST_VAL_RST();
    Delay_Nms(100);
    SET_VAL_RST();
}
static void GPIO_Wifi_Init(void)
{
    GPIO_Config(GPIO_LINK,Pin_LINK,Dir_LINK);
    GPIO_Config(GPIO_READY,Pin_READY,Dir_READY);
    GPIO_Config(GPIO_D2_RST,Pin_D2_RST,Dir_D2_RST);
		Wifi_RST();
}
/********************Motor  configuration*****************************/
static void GPIO_Motor_Init(void)
{
    GPIO_Config(GPIO_MSON,Pin_MSON,Dir_MSON);
    GPIO_Config(GPIO_MARST,Pin_MARST,Dir_MARST);
    GPIO_Config(GPIO_MOPST,Pin_MOPST,Dir_MOPST);
    GPIO_Config(GPIO_MSRDY,Pin_MSRDY,Dir_MSRDY);
    GPIO_Config(GPIO_MZSPD,Pin_MZSPD,Dir_MZSPD);
    GPIO_Config(GPIO_MALRM,Pin_MALRM,Dir_MALRM);
	
    SET_VAL_MSON();         //伺服禁能
	  RST_VAL_MOPST();        //急停,先给急停信号，用来测试小车的报警清除信号是否有效
		Delay_Nms(100);
		SET_VAL_MOPST();
	  SET_VAL_MARST(); 
		Delay_Nms(100);
		RST_VAL_MARST();
		Delay_Nms(500);
		SET_VAL_MARST(); 
    RST_VAL_MSON();   //伺服使能
    Delay_Nms(500);   //保证电机正常使能
	
}
/**********************senser   configuration*************************/
static void GPIO_Senser_Init(void)
{
    GPIO_Config(GPIO_SENSER0,Pin_SENSER0,Dir_SENSER0);
    GPIO_Config(GPIO_SENSER1,Pin_SENSER1,Dir_SENSER1);
    GPIO_Config(GPIO_SENSER2,Pin_SENSER2,Dir_SENSER2);
    GPIO_Config(GPIO_SENSER3,Pin_SENSER3,Dir_SENSER3);
    GPIO_Config(GPIO_SENSER4,Pin_SENSER4,Dir_SENSER4);
    GPIO_Config(GPIO_SENSER5,Pin_SENSER5,Dir_SENSER5);
    GPIO_Config(GPIO_SENSER6,Pin_SENSER6,Dir_SENSER6);
    GPIO_Config(GPIO_SENSER7,Pin_SENSER7,Dir_SENSER7);
    GPIO_Config(GPIO_SENSER8,Pin_SENSER8,Dir_SENSER8);
    GPIO_Config(GPIO_SENSER9,Pin_SENSER9,Dir_SENSER9);
    GPIO_Config(GPIO_SENSER10,Pin_SENSER10,Dir_SENSER10);
    GPIO_Config(GPIO_SENSER11,Pin_SENSER11,Dir_SENSER11);
    GPIO_Config(GPIO_SENSER12,Pin_SENSER12,Dir_SENSER12);
    GPIO_Config(GPIO_SENSER13,Pin_SENSER13,Dir_SENSER13);
}


static void GPIO_RST_Init(void)
{
		GPIO_Config(GPIO_INIT,Pin_INIT,Dir_INIT);
}

extern void GPIO_All_Init()
{
    GPIO_Led_Init();
    GPIO_Key_Init();
    GPIO_Senser_Init();
    GPIO_LCD_Init();
    GPIO_Wifi_Init();
		GPIO_RST_Init();
    GPIO_Motor_Init();
}

/*********************************the function about LCD1602**********************************/
static void GPIO_LCD_Init(void)
{

    GPIO_Config(GPIO_LCD_RS,Pin_LCD_RS,Dir_LCD_RS);
    GPIO_Config(GPIO_LCD_RW,Pin_LCD_RW,Dir_LCD_RW);
    GPIO_Config(GPIO_LCD_E,Pin_LCD_E,Dir_LCD_E);

    GPIO_Config(GPIO_LCD_D0,Pin_LCD_D0,Dir_LCD_D0);
    GPIO_Config(GPIO_LCD_D1,Pin_LCD_D1,Dir_LCD_D1);
    GPIO_Config(GPIO_LCD_D2,Pin_LCD_D2,Dir_LCD_D2);
    GPIO_Config(GPIO_LCD_D3,Pin_LCD_D3,Dir_LCD_D3);
    GPIO_Config(GPIO_LCD_D4,Pin_LCD_D4,Dir_LCD_D4);
    GPIO_Config(GPIO_LCD_D5,Pin_LCD_D5,Dir_LCD_D5);
    GPIO_Config(GPIO_LCD_D6,Pin_LCD_D6,Dir_LCD_D6);
    GPIO_Config(GPIO_LCD_D7,Pin_LCD_D7,Dir_LCD_D7);
}

static void IWDG_Init(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  IWDG_SetPrescaler(IWDG_Prescaler_32);  //4096*32/32768=4s看门狗最大的喂狗时间间隔为4s
  IWDG_SetReload(0xfff);
  IWDG_ReloadCounter();
	IWDG_Enable();
}	

PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    USART_SendData(EVAL_COM2, (uint8_t) ch);
    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(EVAL_COM2, USART_FLAG_TXE) == RESET)
    {
    }
    return ch;
}

