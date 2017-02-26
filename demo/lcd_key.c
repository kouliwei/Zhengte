#include "lcd_key.h"


/***********************
* 全局变量声明区 *
***********************/
struct MenuItem (*MenuPoint) = MainMenu; //结构体指针,指向结构体后由内部函数指针指向功能函数
unsigned char DisplayStart = 0; //显示时的第一个菜单项
unsigned char UserChoose = 0; //用户所选菜单项
unsigned char DisplayPoint = 0; //显示指针
unsigned MaxItems;      //同级最大菜单数
unsigned char ShowCount=2;   //同屏显示菜单数


struct MenuItem MainMenu[5]=
{ //MenuCount   DisplayString            Subs         ChildrenMenus    ParentMenus
{5,              "1.paraset" ,         NullSubs,       Paraset,        Null},
{5,              "2.Voice Center",     NullSubs,       VoiceMenu,      Null},
{5,              "3.Robot Control",    NullSubs,       RobotMenu,      Null},
{5,              "4.Flash Option",     NullSubs,       FlashMenu,      Null},
{5,              "5.Back",             NullSubs,       MainMenu,       MainMenu},
}; 


struct MenuItem Paraset[8]=
{ //MenuCount     DisplayString      Subs          ChildrenMenus        ParentMenus
{8,               "1.car_num",       Carnum_Set,     Null,                MainMenu},
{8,               "2.gl_pos",        Pos_Set,        Null,                MainMenu},
{8,               "3.Speed1",        Speed1_Set,     Null,                MainMenu},
{8,               "4.Speed2",        Speed2_Set,     Null,                MainMenu},
{8,               "5.S_Up",          SpeedUp_Set,    Null,                MainMenu},
{8,               "6.S_Down",        SlowDown_Set,   Null,                MainMenu},
{8,               "7.AlertSet",      NullSubs,       Null,                MainMenu},
{8,               "8.Back",          NullSubs,       MainMenu,            MainMenu},
}; 







struct MenuItem VoiceMenu[5]=
{ //MenuCount     DisplayString              Subs           ChildrenMenus         ParentMenus
{5,               "1.Voice Record" ,         NullSubs,            Null,             MainMenu},
{5,               "2.Play",                  NullSubs,            Null,             MainMenu},
{5,               "3.Pause",                 NullSubs,            Null,             MainMenu},
{5,               "4.Voice Delete",          NullSubs,            Null,             MainMenu},
{5,               "5.Back",                  NullSubs,            MainMenu,         MainMenu},
}; 

 


struct MenuItem RobotMenu[5]=
{ //MenuCount       DisplayString            Subs            ChildrenMenus        ParentMenus
{5,                 "1.Turn Left",          NullSubs,             Null,              MainMenu},
{5,                 "2.Turn Right",         NullSubs,             Null,              MainMenu},
{5,                 "3.Go Ahead",           NullSubs,             Null,              MainMenu},
{5,                 "4.Go Back",            NullSubs,             Null,              MainMenu},
{5,                 "5.Back",               NullSubs,             MainMenu,          MainMenu},
}; 


struct MenuItem FlashMenu[5]=
{ //MenuCount    DisplayString              Subs            ChildrenMenus          ParentMenus
{5,                "1.Flash Record",        NullSubs,             Null,            MainMenu},
{5,                "2.Play",                NullSubs,             Null,            MainMenu},
{5,                "3.Pause",               NullSubs,             Null,            MainMenu},
{5,                "4.Flash Delete",        NullSubs,             Null,            MainMenu},
{5,                "5.Back",                NullSubs,             MainMenu,        MainMenu},
};


/**************************key************************************/

static uint8_t Key_Scan(uint8_t *KeyNum)
{
    uint32_t i = 0;
    uint8_t Senser1_Flag1 = 1;
    uint8_t Senser1_Flag = 0;
    uint8_t Senser2_Flag = 0;
    uint8_t Senser3_Flag = 0;
    uint8_t Senser4_Flag = 0;
    
	
    while(EFF_VAL_KEY1())                       //按键1有效
    {
        if(EFF_VAL_KEY1())
        {
            i++;
        }
        if(i>30000 && i<100000)
        {
            Senser1_Flag = 1;
        }
        if(i > 100000)
        {
            Senser1_Flag = 1;
            Senser1_Flag1 = 0;
        }
    }
    
    while(EFF_VAL_KEY2())                       //按键2有效
    {
        if(EFF_VAL_KEY2())
        {
            i++;
        }
        if(i>30000 && i<100000)
        {
            Senser2_Flag = 1;
        }
    }
    
    while(EFF_VAL_KEY3())                       //按键3有效
    {
        if(EFF_VAL_KEY3())
        {
            i++;
        }
        if(i>30000 && i<100000)
        {
            Senser3_Flag = 1;
        }

    }
    
    while(EFF_VAL_KEY4())                       //按键4有效
    {
        if(EFF_VAL_KEY4())
        {
            i++;
        }
        if(i>30000 && i<100000)
        {
            Senser4_Flag = 1;
        }
    }
		

    if(Senser1_Flag == 1)
    {
        Led_Drive(0x01);
        *KeyNum = Esc;
    }
    else if(Senser2_Flag == 1)
    {
        Led_Drive(0x02);
        *KeyNum = Enter;
    }
    else if(Senser3_Flag == 1)
    {
        Led_Drive(0x04);
        *KeyNum = Down;
    }
    else 
    {
        if(Senser4_Flag == 1)
        {
            Led_Drive(0x08);
            *KeyNum = Up;
        }
    }

    return Senser1_Flag1;
}


static void Menu_Change(uint8_t  KeyNum)
{
    if(KeyNum)
    {
        switch(KeyNum)
        {     
            case Up:
                UserChoose --;
                if (UserChoose ==255)
                {
                    UserChoose = 0;//上翻截至,如果要回滚赋值MaxItems-1
                }
                break;
            case Esc:
                if (MenuPoint[UserChoose].ParentMenus != Null)
                {
                    MenuPoint = MenuPoint[UserChoose].ParentMenus;
                    UserChoose = 0;
                    DisplayStart = 0;
                }
                break;
            case Down:
                UserChoose ++ ;
                if (UserChoose == MaxItems)
                {
                    UserChoose = MaxItems-1;//下翻截至,如要回滚赋值为0
                }
                break;
            case Enter:
                if (MenuPoint[UserChoose].Subs != NullSubs)
                {
                    (*MenuPoint[UserChoose].Subs)();
                }
                else if (MenuPoint[UserChoose].ChildrenMenus != Null)
                {
                    MenuPoint = MenuPoint[UserChoose].ChildrenMenus;
                    UserChoose = 0;
                    DisplayStart = 0;
                }
                break;
            case Reset:
                MenuPoint = MainMenu;
                UserChoose = 0;
                DisplayStart = 0;
                break;
            default:
                break;
        }
        if (UserChoose%ShowCount==0)           //一屏只能显示ShowCount行
            DisplayStart = UserChoose;
        else if(UserChoose==1||UserChoose== 3)
            DisplayStart = UserChoose-1;     //实现滚屏的关键    
        LCD_En_Command(0x01);      //液晶清屏,根据不同液晶函数自行修改
        Delay_Nms(5);         //液晶为慢速器件
        ShowMenu();
    }
}


static void ShowMenu(void)
{
    unsigned char n;
    MaxItems = MenuPoint[0].MenuCount;//定义最大同级菜单
    DisplayPoint = DisplayStart;
    for(n=0; (DisplayPoint<MaxItems) && (n<ShowCount);n++)
    {
        if(DisplayPoint==UserChoose)
				{
            LCD_Write_String(0,n,"->");
				}
				LCD_Write_String(2,n,MenuPoint[DisplayPoint++].DisplayString);   
    }
}

static void NullSubs(void)
{
	

}








static void Carnum_Set(void)
{
	uint8_t high = gl_car.num/10 + 48;
	uint8_t low  = gl_car.num%10 + 48;
	uint8_t KeyNum = 0,flag = 0;
	uint8_t Parameter = 4;
	LCD_Write_Char(14,0,high);
	LCD_Write_Char(15,0,low);

	
	while(1)
	{
		KeyNum = 0;
		Key_Scan(&KeyNum);
		if(KeyNum)
		{
			switch(KeyNum)
			{
				case Up:
					if(gl_car.num >= 41)
					{
						gl_car.num = 0;
					}
					else
					{
						gl_car.num ++;
					}
						
					break;
				case Down:
					if(gl_car.num == 0)
					{
						gl_car.num = 40;
					}
					else
					{
						gl_car.num --;
					}
					break;
				case Esc:
					flag = 1;
					break;
			}
			high = gl_car.num/10 + 48;
			low  = gl_car.num%10 + 48;
			LCD_Write_Char(14,LINE1,high);
			LCD_Write_Char(15,LINE1,low);
			if(flag)
			{
					I2c_Parameter_Write(Parameter);
					break;
			}
		}
	}
}







static void Pos_Set(void)
{
	uint8_t high = gl_pos/10 + 48;
	uint8_t low  = gl_pos%10 + 48;
	uint8_t KeyNum = 0,flag = 0;
	uint8_t Parameter = 11;
	LCD_Write_Char(14,LINE2,high);
	LCD_Write_Char(15,LINE2,low);
	
	while(1)
	{
		KeyNum = 0;
		Key_Scan(&KeyNum);
		if(KeyNum)
		{
			switch(KeyNum)
			{
				case Up:
					
					if(gl_pos >= 31)
					{
						gl_pos = 0;
					}
					else
					{
						gl_pos ++;
					}
					break;
				case Down:
					if(gl_pos == 0)
					{
						gl_pos = 30;
					}
					else
					{
						gl_pos --;
					}
					break;
				case Esc:
					flag = 1;
					break;
			}
			high = gl_pos/10 + 48;
			low  = gl_pos%10 + 48;
			LCD_Write_Char(14,LINE2,high);
			LCD_Write_Char(15,LINE2,low);
			if(flag)
			{
				I2c_Parameter_Write(Parameter);
				break;
			}
		}
	}
}

static void Speed1_Set(void)
{
	uint8_t baiwei = gl_Speed1/100 + 48;
	uint8_t shiwei = (gl_Speed1 - 100*(baiwei-48))/10 + 48;
	uint8_t gewei  = gl_Speed1%10 + 48;
	uint8_t KeyNum = 0,flag = 0;
	uint8_t Parameter = 5;
	LCD_Write_Char(13,0,baiwei);
  LCD_Write_Char(14,0,shiwei);
	LCD_Write_Char(15,0,gewei);

	
	while(1)
	{
		KeyNum = 0;
		Key_Scan(&KeyNum);
		if(KeyNum)
		{
			switch(KeyNum)
			{
				case Up:
					if(gl_Speed1 == 100)
					{
						gl_Speed1= 1;
					}
					else
					{
						gl_Speed1++;
					}
						
					break;
				case Down:
					if(gl_Speed1 == 1)
					{
						gl_Speed1 = 100;
					}
					else
					{
						gl_Speed1--;
					}
					break;
				case Esc:
					flag = 1;
					break;
			}
			baiwei = gl_Speed1/100 + 48;
			shiwei = (gl_Speed1 - 100*(baiwei-48))/10 + 48;
			gewei  = gl_Speed1%10 + 48;
	    LCD_Write_Char(13,0,baiwei);
			LCD_Write_Char(14,0,shiwei);
			LCD_Write_Char(15,0,gewei);
			if(flag)
			{
					I2c_Parameter_Write(Parameter);
					break;
			}
		}
	}
}

static void Speed2_Set(void)
{
	uint8_t baiwei = gl_Speed2/100 + 48;
	uint8_t shiwei = (gl_Speed2 - 100*(baiwei-48))/10 + 48;
	uint8_t gewei  = gl_Speed2%10 + 48;
	uint8_t KeyNum = 0,flag = 0;
	uint8_t Parameter = 6;
	LCD_Write_Char(13,1,baiwei);
  LCD_Write_Char(14,1,shiwei);
	LCD_Write_Char(15,1,gewei);

	
	while(1)
	{
		KeyNum = 0;
		Key_Scan(&KeyNum);
		if(KeyNum)
		{
			switch(KeyNum)
			{
				case Up:
					if( gl_Speed2 == 100)
					{
						gl_Speed2 = 1;
					}
					else
					{
						gl_Speed2++;
					}
						
					break;
				case Down:
					if(gl_Speed2 == 1)
					{
						gl_Speed2 = 100;
					}
					else
					{
						gl_Speed2--;
					}
					break;
				case Esc:
					flag = 1;
					break;
			}
			baiwei = gl_Speed2/100 + 48;
			shiwei = (gl_Speed2 - 100*(baiwei-48))/10 + 48;
			gewei  = gl_Speed2%10 + 48;
	    LCD_Write_Char(13,1,baiwei);
			LCD_Write_Char(14,1,shiwei);
			LCD_Write_Char(15,1,gewei);
			if(flag)
			{
					I2c_Parameter_Write(Parameter);
					break;
			}
		}
	}
}



static void SpeedUp_Set(void)
{
	uint8_t high = gl_SpeedUp/10 + 48;
	uint8_t low  = gl_SpeedUp%10 + 48;
	uint8_t KeyNum = 0,flag = 0;
	uint8_t Parameter = 8;
	LCD_Write_Char(14,LINE1,high);
	LCD_Write_Char(15,LINE1,low);
	
	while(1)
	{
		KeyNum = 0;
		Key_Scan(&KeyNum);
		if(KeyNum)
		{
			switch(KeyNum)
			{
				case Up:
					
					if(gl_SpeedUp == 5)
					{
						gl_SpeedUp = 1;
					}
					else
					{
						gl_SpeedUp ++;
					}
					break;
				case Down:
					if(gl_SpeedUp == 1)
					{
						gl_SpeedUp = 5;
					}
					else
					{
						gl_SpeedUp --;
					}
					break;
				case Esc:
					flag = 1;
					break;
			}
			high = gl_SpeedUp/10 + 48;
			low  = gl_SpeedUp%10 + 48;
			LCD_Write_Char(14,LINE1,high);
			LCD_Write_Char(15,LINE1,low);
			if(flag)
			{
				I2c_Parameter_Write(Parameter);
				break;
			}
		}
	}
}

static void SlowDown_Set(void)
{
	uint8_t high = gl_SlowDown/10 + 48;
	uint8_t low  = gl_SlowDown%10 + 48;
	uint8_t KeyNum = 0,flag = 0;
	uint8_t Parameter = 9;
	LCD_Write_Char(14,LINE2,high);
	LCD_Write_Char(15,LINE2,low);
	
	while(1)
	{
		KeyNum = 0;
		Key_Scan(&KeyNum);
		if(KeyNum)
		{
			switch(KeyNum)
			{
				case Up:
					
					if(gl_SlowDown ==5)
					{
						gl_SlowDown = 1;
					}
					else
					{
						gl_SlowDown ++;
					}
					break;
				case Down:
					if(gl_SlowDown == 1)
					{
						gl_SlowDown = 5;
					}
					else
					{
						gl_SlowDown --;
					}
					break;
				case Esc:
					flag = 1;
					break;
			}
			high = gl_SlowDown/10 + 48;
			low  = gl_SlowDown%10 + 48;
			LCD_Write_Char(14,LINE2,high);
			LCD_Write_Char(15,LINE2,low);
			if(flag)
			{
				I2c_Parameter_Write(Parameter);
				break;
			}
		}
	}
}



static void LCD_En_Command(uint8_t command)
{
    LCD_Data(command);
    CLR_LCD_RS();
    CLR_LCD_RW();
    CLR_LCD_E();
    Delay_Nus(500);
    SET_LCD_E();
}
static void LCD_En_Data(uint8_t  temp)//write data function
{
    LCD_Data(temp);
    SET_LCD_RS();
    CLR_LCD_RW();
    CLR_LCD_E();
    Delay_Nus(500);
    SET_LCD_E();
}
static void LCD_Set_Pos(uint8_t x, uint8_t y )//set display address function
{
    uint8_t address;
    if(y == LINE1)
    {
        address = LINE1_HEAD + x;
    }
    else
    {
        address = LINE2_HEAD + x;
    }
    LCD_En_Command(address);
}

static void LCD_Write_Char(uint16_t x,uint8_t y,uint8_t data)//write lcd a character function
{
    LCD_Set_Pos(x,y);
    LCD_En_Data(data);
}
static void LCD_Write_String(uint8_t X,uint8_t Y,uint8_t *s)//write lcd string function
{
    LCD_Set_Pos(X,Y);
    while(*s != '\0')
    {
        LCD_En_Data(*s++);
    }
}

static void LCD_Init(void)//lcd initize function
{
    CLEARSCREEN();
    LCD_En_Command(DATA_MODE);
    LCD_En_Command(OPEN_SCREEN);
    LCD_En_Command(MODE_SELECT);
    LCD_En_Command(DISPLAY_ADDRESS);
    CLEARSCREEN();
}



static void LCD_Data(uint8_t data)
{
    if(data & 0x01)
    {
        SET_LCD_D0();
    }
    else
    {
        CLR_LCD_D0();
    }
    if(data & 0x02)
    {
        SET_LCD_D1();
    }
    else
    {
        CLR_LCD_D1();
    }
    if(data & 0x04)
    {
        SET_LCD_D2();
    }
    else
    {
        CLR_LCD_D2();
    }
    if(data & 0x08)
    {
        SET_LCD_D3();
    }
    else
    {
        CLR_LCD_D3();
    }
    if(data & 0x10)
    {
        SET_LCD_D4();
    }
    else
    {
        CLR_LCD_D4();
    }
    if(data & 0x20)
    {
        SET_LCD_D5();
    }
    else
    {
        CLR_LCD_D5();
    }
    if(data & 0x40)
    {
        SET_LCD_D6();
    }
    else
    {
        CLR_LCD_D6();
    }
    if(data & 0x80)
    {
        SET_LCD_D7();
    }
    else
    {
        CLR_LCD_D7();
    }
}


static void Parameter_Set(void)
{
    uint8_t KeyNum = 0;
		uint8_t flag = 0;    //flag标志是否进入参数设置界面
		Key_Scan(&flag);     
		while(flag)
		{
			KeyNum = 0;
			flag = Key_Scan(&KeyNum);
			Menu_Change(KeyNum);
		}
}


extern void LCD_Set(void)
{
		if(gl_Init_Flag == 0)
		{
			Load_Config();
		}
		LCD_Init();
    Tx_Enable();                    //串口定时发送中断开启
		Tx_Cmd();												//串口定时器使能
    Led_Drive(0x0f);
    while(gl_flag == 1) 
    {
        Parameter_Set();
    }
    Led_Drive(0x00);
    CLEARSCREEN();
    Delay_Nms(5);
    LCD_Write_String(2,LINE1,"Normal mode");
    Rx_Enable();                    //串口接收中断开启 
		MOTOR_IT_ENABLE(); 							//电机定时中断开启
		MOTOR_Cmd_ENABLE();             //电机定时器开启
		TIM_ITConfig(TIM12,TIM_IT_Update,ENABLE);
		gl_Tim12Flag = 1;

//		TIM_ITConfig(TIM13,TIM_IT_Update,ENABLE);
}
