#include "senser.h"


extern void Senser_Detect_Mode1(void)
{
    gl_car.pos = gl_pos + 1;                                    //工位信息为gl_pos + 1;
    gl_car.opr = gl_opr + 1;                                    //操作位信息为gl_por + 1;
    gl_StartFlag = 0;                                           //启动清零
    gl_SlowFlag = 0;                                            //减速传感器清零
    gl_StopFlag = 1;                                            //停止传感器置位
    gl_ColliFlag = 0;                                           //防撞传感器清零
    gl_DirFlag = BACKWARD;                                      //方向默认向左
}



extern void Senser_Detect_Mode2(void)
{

    uint8_t Senser0_Flag = 0;
    uint8_t Senser1_Flag = 0;
    uint8_t Senser2_Flag = 0;
    uint8_t Senser3_Flag = 0;
    uint8_t Senser4_Flag = 0;
    uint8_t Senser5_Flag = 0;
    uint8_t Senser6_Flag = 0;
    uint8_t Senser7_Flag = 0;
    uint8_t Senser8_Flag = 0;
	  uint8_t Senser9_Flag = 0;
	

    uint8_t FORE_ColliFlag = 0;
    uint8_t BACK_ColliFlag = 0;
	  uint8_t ColliFlag = 0;
		static uint8_t ColliFlag_Last = 0;
		static  uint8_t flag = 1;         ///   可能上电有问题
	
		uint8_t flag1 = 0;
	 

/*************Senser*_Allow 标志位用于控制是否响应传感器******************/
	
	
    Senser_Detect(&Senser0_Flag,&Senser1_Flag,&Senser2_Flag,&Senser3_Flag,&Senser4_Flag,&Senser5_Flag,&Senser6_Flag,&Senser7_Flag,&Senser8_Flag,&Senser9_Flag);
		/***************人工站，旋转到位***********************/
		if(gl_StopFlag == 1  && (gl_car.pos == 15 || gl_car.pos == 16 || gl_car.pos == 13 || gl_car.pos == 18))
		{
			if(Senser9_Flag == 1)
			{
				gl_DaoWeiFlag = 1;
			} 
			else if(Senser9_Flag == 2)     
			{
				Senser9_Flag = 0;
				gl_DingweiErrorData_Flag = 1;
			}
		}
		else if(gl_StopFlag == 100 && gl_AlertFlag == 1 && (gl_car.pos == 1 || gl_car.pos == 20 ))
		{
			if(Senser9_Flag == 1)
			{
				gl_DaoWeiFlag = 1;
			}
			else if(Senser9_Flag == 2)
			{
				Senser9_Flag = 0;
				gl_DingweiErrorData_Flag = 1;
			}
		}
		else
		{
			gl_DaoWeiFlag = 0;
		}
		
		/***************发送到位信号*********************/
		if(gl_DaoWeiFlag == 1 && Senser9_Flag == 1)
		{
			Senser9_Flag = 0;
			gl_DingweiRightData_Flag = 1;
		}
		
		

    if(Senser6_Flag  && gl_StopFlag)                                          
    {
        if(gl_DirFlag == FOREWARD && gl_car.pos != gl_pos + 1)                          //如果小车向右走，则改为向左走,此时小车处于右边的升降梯
        {
            gl_car.pos = gl_pos + 1;
            gl_car.opr = gl_pos2opr[gl_car.pos];

        }
        else if(gl_DirFlag == BACKWARD && gl_car.pos != 0)                                               //如果小车向左走，则改为向右走，此时小车处于左边的升降梯
        {
            gl_car.opr = 0;
            gl_car.pos = 0; 
        }
    }

		
	

		
//    if(Senser0_Flag)
//    {
//        gl_car.pos1 = 0;
//        gl_car.pos = 0;                                     //工位信息清零
//        gl_car.opr = 0;                                     //有效工位信息清零
//        gl_DirFlag = FOREWARD;                              //方向复位为向右
//        gl_Multi_Flag = 1;
//    }
		

    if(Senser1_Flag  || gl_VirStart_Flag)   //气缸触发  or  上位机启动
    {
        if(gl_VirStart_Flag == 1)
        {
            gl_VirStart_Flag = 0;
        }
        else
        {
				
            if(gl_car.pos == gl_pos + 1 || gl_car.pos == gl_pos + 2)
            {
                gl_DirFlag = BACKWARD;
            }
            else
            {
                gl_DirFlag = FOREWARD;
            }
						
						if(gl_car.pos == gl_pos + 1)    //点击启动后
						{
							gl_flag1 = 1;
						}
            /*******要加上旋转到位的条件才能启动***************/
						Start();
						gl_CheckStop_Flag[0] = 0;
						gl_CheckStop_Flag[1] = 0;
        }
    }
		
		


    if(Senser2_Flag)
    {
				gl_Flag4 = 0;
				if(gl_SlowFlag == 0 )   //检测到减速传感器时如果之前的状态时减速，
				{
					Update_Pos_Opr();
					if(gl_posFlag[gl_car.pos])  
					{
            if(gl_Multi_Flag == 1)
            {
								gl_Flag5 = 1;
								gl_Senser_Flag[1] = 1;
                Slow();
							  gl_pwmslow = gl_pwm / 40;
								gl_CheckStop_Flag[0] = 1;     //检测到了减速传感器,可能会有问题
								gl_SlowDownRightData_Flag = 1;
            }
						else
						{
							gl_Senser_Flag[1] = 0;
							gl_Multi_Flag--;
							gl_Flag5 = 2;
						}
					}
				}
    }
		
		
		

    if((Senser3_Flag  || gl_CheckStop_Flag[1]) && flag == 0 && gl_Flag5 == 1 )
    {
				if(gl_CheckStop_Flag[1] == 1)
				{
					gl_CheckStop_Flag[1] = 0;
					gl_StopErrorData_Flag = 1;
					flag1 = 1;
				}
				else
				{
					gl_StopRightData_Flag = 1;
				}
				
				if(gl_CheckStop_Flag[0] == 0)   //	假如开始并未接收到减速传感器
				{
					Update_Pos_Opr();                 //the slow-down senser  can be located accurately in which position
					gl_SlowDownErrorData_Flag = 1;        //use it to send the slowdown error 
					if(gl_car.pos == gl_pos || gl_car.pos == gl_pos + 1 || gl_car.pos == gl_pos + 2 || gl_car.pos == 0 || gl_car.pos == 1)
					{
						flag1 = 1;
					}
					else
					{
						flag1 = 0;
					}
				}
				else
				{
					flag1 = 1;
				}
				
				
				if(flag1 == 1)
				{
					if(gl_posFlag[gl_car.pos])
					{
            if(gl_Multi_Flag == 1)
            {
								flag = 1;
                Stop();
							  if(gl_car.pos != 1 && gl_car.pos != gl_pos)   //精定位15、 16 要修改
								{
									motor_stop();
								}
                gl_Multi_Flag = gl_posFlag[gl_car.pos];
								if(gl_Store[gl_car.pos+1] > 128)
								{
									gl_Flag6 = 1;
								}
            }
					}
					if(gl_flagStop == 1)    //if the car is stop normally ,set gl_flagStop
					{
            gl_flagStop = 0;
					  motor_stop();
					  gl_car_state = 0;
					}		
				}
				
		

    }
		
		if(gl_StopFlag && gl_flagStop == 1)
		{
			gl_flagStop = 0;
			motor_stop();
			gl_car_state = 0;
		}
		
		if(gl_car.pos != 21)
		{
			gl_flag1 = 0;
		}
		
		if(gl_flag1 == 1 && gl_JiTingFlag == 0)
		{
			Start();
		}
		
		

    if(gl_DirFlag == FOREWARD)                                      //根据小车运行的方向对左右防撞传感器信号进行特殊处理
    {
        BACK_ColliFlag = 0;
        if(gl_car.opr == gl_opr || gl_car.opr ==gl_opr+1)
        {
//						if(gl_car.opr == gl_opr+1)
//						{
//							FORE_ColliFlag = 0;
//						}
//						else
//						{
//							if(gl_SlowFlag == 1 && Senser4_Flag == 1)  //小车在20号工位，减速，遇到防撞传感器，防撞有效//
//							{
//								FORE_ColliFlag = 1;
//							}
//							else
//							{
//								FORE_ColliFlag = 0;
//							}
//						}
					FORE_ColliFlag = 0;
        }
        else
        {
            if(Senser4_Flag == 1)
            {
                FORE_ColliFlag = 1;
            }
            else
            {
                FORE_ColliFlag = 0;
            }
        }
    }
    else
    {
        FORE_ColliFlag = 0;    
        if(gl_car.opr == gl_opr + 2 || gl_car.opr == 0)                                //小车已经走过了线下的传感器
        {
            BACK_ColliFlag = 0;
        }
        else
        {
            if(Senser5_Flag == 1)
            {
                BACK_ColliFlag = 1;
            }
            else
            {
                BACK_ColliFlag = 0;
            }
        }
    }
		 
    ColliFlag = (FORE_ColliFlag || BACK_ColliFlag);          //只要有一个防撞传感器有效，则将gl_ColliFlag 置1
		
		if(ColliFlag == 1 && ColliFlag_Last == 0)
		{
			gl_pwmcolli = gl_pwm / 40;
		}
		ColliFlag_Last = ColliFlag;
		if(ColliFlag == 1)
		{
			gl_ColliFlag = 1;
			gl_Senser_Flag[3] = 0;
		}
		else
		{
			if(gl_ColliFlag == 1)
			{
				gl_Senser_Flag[3] = 1;
			}
		}
		
		
    /***********************特殊处理*****************************/
    if(Senser8_Flag)         //gl_StopFlag = 123,代表急停
    {
        gl_car_state = 0;
        gl_StartFlag = 0;
        gl_SlowFlag = 0;
        gl_StopFlag = 123;     
    }
		
		
		if(gl_StartFlag == 1)
		{
			Change_Multi_Flag(); 
		}
		 
		/******停止传感器保护************/
		if(gl_StartFlag == 1 || gl_SlowFlag == 1)
		{ 
			flag = 0;
		}
		
		if(gl_StopFlag == 0)   
		{
			gl_Daowei = 0;
			gl_DingweiRightData_Flag = 0;
			gl_DingweiErrorData_Flag = 0;
		}
		
		if(gl_car.pos == gl_SpePos[0] || gl_car.pos == gl_SpePos[1] || gl_car.pos == gl_SpePos[2] || gl_car.pos == gl_SpePos[3]) //小车在线上多线操作后到下一个缓存位会防撞，限制最高速度为0.5m
		{
			gl_Flag6 = 0;
		}
		if(gl_car.pos >= 14 || gl_car.pos <= 2)
		{
			gl_Flag6 = 0;
		}
}





extern void Senser_Detect_Mode3(void)
{

    uint8_t Senser0_Flag = 0;
    uint8_t Senser1_Flag = 0;
    uint8_t Senser2_Flag = 0;
    uint8_t Senser3_Flag = 0;
    uint8_t Senser4_Flag = 0;
    uint8_t Senser5_Flag = 0;
    uint8_t Senser6_Flag = 0;
    uint8_t Senser7_Flag = 0;
    uint8_t Senser8_Flag = 0;
    uint8_t Senser9_Flag = 0;
    uint8_t Dingwei_Pos[4] = {30,30,30,30};
	

    uint8_t FORE_ColliFlag = 0;
    uint8_t BACK_ColliFlag = 0;

/*************Senser*_Allow 标志位用于控制是否响应传感器******************/
	
	
    Senser_Detect(&Senser0_Flag,&Senser1_Flag,&Senser2_Flag,&Senser3_Flag,&Senser4_Flag,&Senser5_Flag,&Senser6_Flag,&Senser7_Flag,&Senser8_Flag,&Senser9_Flag);
		
		

//    if(Senser6_Flag)                                          
//    {
//        if(gl_DirFlag == FOREWARD && gl_car.pos != gl_pos + 1)                          //如果小车向右走，则改为向左走,此时小车处于右边的升降梯
//        {
//            gl_DirFlag = BACKWARD;
//            gl_car.pos = gl_pos + 1;
//            gl_car.opr = gl_pos2opr[gl_car.pos];

//        }
//        else if(gl_DirFlag == BACKWARD && gl_car.pos != 0)                                               //如果小车向左走，则改为向右走，此时小车处于左边的升降梯
//        {
//            gl_DirFlag = FOREWARD;
//            gl_car.opr = 0;
//            gl_car.pos = 0;
//        }
//    }

    if(Senser7_Flag && gl_CorrectNumFlag == 1)
    {
        gl_flag2 = 1;
    }
		
	

		
//    if(Senser0_Flag)
//    {
//        gl_car.pos1 = 0;
//        gl_car.pos = 0;                                     //工位信息清零
//        gl_car.opr = 0;                                     //有效工位信息清零
//        gl_DirFlag = FOREWARD;                              //方向复位为向右
//        gl_Multi_Flag = 1;
//    }
		

    if(Senser1_Flag)   //气缸触发  or  上位机启动
    {
        if(gl_car.pos == Dingwei_Pos[0] || gl_car.pos == Dingwei_Pos[1] || gl_car.pos == Dingwei_Pos[2] || gl_car.pos == Dingwei_Pos[3])
        {
            if(Senser9_Flag)
            {
                Start();
            }
        }
        else
        {
            Start();
        }
			
			
//        if(gl_car.pos == gl_pos + 1)    //Set gl_flag1 for the location of car located the down of the line of production
//        {
//            gl_flag1 = 1;
//        }
//        
//        if(gl_car.pos == gl_pos + 1 || gl_car.pos == gl_pos + 2)
//        {
//            gl_DirFlag = BACKWARD;
//        }
//        else
//        {
//            gl_DirFlag = FOREWARD;
//        }
    }
		
    //  gl_DirFlag1 == 1:点动模式正常运行，gl_DirFlag1 == 2:点动模式异常运行不进行传感器的检测
    if(Senser2_Flag && gl_DirFlag1 == 1)
    {
        Slow();
			  gl_pwmslow = gl_pwm / 40;
    }

    if(Senser3_Flag && gl_DirFlag1 == 1)
    {
        Stop();
			  motor_stop();
    }
		
		


    if(gl_DirFlag == FOREWARD)                                      //根据小车运行的方向对左右防撞传感器信号进行特殊处理
    {
        BACK_ColliFlag = 0;
        if(Senser4_Flag == 1)
        {
            FORE_ColliFlag = 1;
        }
        else
        {
            FORE_ColliFlag = 0;
        }
    }
    else
    {
				FORE_ColliFlag = 0;
        if(Senser5_Flag == 1)
        {
            BACK_ColliFlag = 1;
        }
        else
        {
            BACK_ColliFlag = 0;
        }
    }
    gl_ColliFlag = (FORE_ColliFlag || BACK_ColliFlag);          //只要有一个防撞传感器有效，则将gl_ColliFlag 置1		
}




extern void Senser_Detect_Mode4(void)
{
	static uint8_t Senser0_Allow = 0;
	static uint8_t timer_flag0 = 0;
	
	if(NON_VAL_SENSER0() && ~Senser0_Allow)                     
	{
		Senser0_Allow = 1;
	}
	if(EFF_VAL_SENSER0()&& Senser0_Allow)                       //零位传感器有效
  {
		Delay_Nus(500);
		if(EFF_VAL_SENSER0())
    {
			if(timer_flag0 > 5)                                    //参数可能要调整
			{
				Senser0_Allow = 0;
				timer_flag0 = 0;
				gl_flag2 = 1;
			}
			else
			{
				timer_flag0++;
			}
		}
		else
		{
			timer_flag0 = 0;
		}
	}
}



static void Update_Pos_Opr(void)
{
    if(gl_car.pos == gl_pos + 2)
    {
        gl_car.pos = 0;
    }
    else
    {
        gl_car.pos++;
    }
    gl_car.opr = gl_pos2opr[gl_car.pos];
}




/*************gl_Buff[2] = {type,1}***********************/

extern void Shang_Xian(void)
{
    if(gl_RxLen == 2 && gl_Buff[1] == 1)  //长度校验+数据校验:当接收的数据长度为2 并且接受到的第二个数据gl_Buff[1] == 1时
    {
			gl_car.opr = gl_opr + 1;
			gl_car.pos = gl_pos + 1;
			gl_DirFlag = BACKWARD;
			Start();
    }
}

/************gl_Buff[4]={type,car.num,operation of stopping,start/stop,}*************/

extern void Dian_Dong(void)
{
    if(gl_car.num == gl_Buff[1])
    {
        if(gl_Buff[2]) 
        {
            gl_car_state = 3;
					  gl_JiTingFlag = 0;
            Start();
        }
        else
        {
            gl_StartFlag = 0;
            gl_SlowFlag = 0;
            gl_StopFlag = 1+128;
        }
    }
}


/***********gl_Buff[3] ={type, gl_Left,gl_Right}***********************************/
extern void Inter_Action(void)    //交互信息
{
    if(gl_RxLen == 3)     //长度校验
    {
        gl_Left = gl_Buff[1];               //左升降梯的信号
        gl_Right = gl_Buff[2];              //右升降梯的信号
    }                                       
} 



/****************启动小车***********************/
/****************修改日期2016：1104*************/
extern void Start_Car(void)
{
	if(gl_Status[2] == 129 || gl_Status[2] == 123)   //由点动到正常运行的切换
	{
		gl_Status[2] = 1;
	}
	if(gl_StopFlag == 129)                             //由点动到正常运行的切换
	{
		gl_StopFlag = 1;
	}
	
	/*******点动到线下位置在gl_pos = 21 和 gl_pos = 22之间时，点击开始无条件开始运行**********/
	if(gl_car.pos == gl_pos + 1 && gl_DirFlag == BACKWARD && gl_Flag3 == 1)
	{
		gl_Flag3 = 0;
		gl_StartFlag = 1;
		gl_SlowFlag = 0;
		gl_StopFlag = 0;
	}
	else
	{
		if(gl_StopFlag == 123)
		{
			gl_StartFlag = gl_Status[0];
			gl_SlowFlag = gl_Status[1];
			gl_StopFlag = gl_Status[2];
		}
	}
	gl_car_state = 2;
  gl_JiTingFlag = 0;
  gl_flagStop = 0;
  gl_VirStart_Flag = 1;
}

/***********正常运行模式:gl_Buff[1] = 127 && gl_Buff[2] == 128*************************/
extern void Zheng_Chang(void)
{
    if(gl_RxLen == 3)
    {
        if(gl_Buff[1] == 127 && gl_Buff[2] == 128 && gl_car_state != 2)
        {
						gl_OpenFlag[0] = 1;
						gl_OpenFlag[1] = 0;
					  if(gl_Status[2] == 129 || gl_Status[2] == 123)   //由点动到正常运行的切换
						{
							gl_Status[2] = 1;
						}
						if(gl_StopFlag == 129)                             //由点动到正常运行的切换
						{
							gl_StopFlag = 1;
						}
						
						/*******点动到线下位置在gl_pos = 21 和 gl_pos = 22之间时，点击开始无条件开始运行**********/
						if(gl_car.pos == gl_pos + 1 && gl_DirFlag == BACKWARD && gl_Flag3 == 1)
						{
							gl_Flag3 = 0;
							gl_StartFlag = 1;
					    gl_SlowFlag = 0;
					    gl_StopFlag = 0;
						}
						else
						{
							if(gl_StopFlag == 123)
							{
								gl_StartFlag = gl_Status[0];
								gl_SlowFlag = gl_Status[1];
								gl_StopFlag = gl_Status[2];
							}
						}
						gl_car_state = 2;
            gl_JiTingFlag = 0;
            gl_flagStop = 0;
            gl_VirStart_Flag = 1;
//						while(1)
//						{
//							if(NONEFF_MSRDY() || EFF_MALRM())  //点击开始后使能电机
//							{
//								printf("start enable the motor");
//								SET_VAL_MSON();         //伺服禁能
//								RST_VAL_MARST();
//								Delay_Nms(500);
//								SET_VAL_MARST(); 
//								Delay_Nms(500);   //保证电机正常使能
//								RST_VAL_MSON();   //伺服使能
//								Delay_Nms(500);   //保证电机正常使能
//							}
//						}
        }
        else if(gl_Buff[1] == 128 && gl_Buff[2] == 127)
        {
						gl_OpenFlag[0] = 0;
            gl_flagStop = 1;
					  gl_Status[0] = 0;
					  gl_Status[1] = 0;
					  gl_Status[2] = 1;
        }
        else if(gl_Buff[1] == 123 && gl_Buff[2] == 123 && gl_JiTingFlag == 0)
        {
						gl_OpenFlag[0] = 0;
						gl_OpenFlag[1] = 1;
						if(gl_StopFlag != 123)
						{
							gl_Status[0] = gl_StartFlag;
							gl_Status[1] = gl_SlowFlag;
							gl_Status[2] = gl_StopFlag; 
							gl_StartFlag = 0;
							gl_SlowFlag = 0;
							gl_StopFlag = 123; 
							gl_JiTingFlag = 1;
						}
        }
        else if(gl_Buff[1] == 0 && gl_Buff[2] == 0)
        {
            Init_State();
        }
    }
}



/**********修改小车编号的模式******************/
extern void Chang_Num(void)
{
    uint8_t temp_Array[3] = {0};
    uint8_t i = 0;
    for(i=0 ; i<3 ; i++)
    {
        temp_Array[i] = gl_Buff[i];
    }

    if(temp_Array[1] == 0 && temp_Array[2] == 0)   //进入修改模式 6 0 0 
    {
				Stop();
			  gl_flag2 = 0;
        gl_car.num = 0;
        gl_CorrectNumFlag = 1;
				gl_car_state = 4;                  //用于修改小车编号。
    }
    else
    {
        if(gl_car_state == 4 && gl_flag2 == 1)  //开始修改,小车进入了修改模式，并且检测到了相应的传感器。
        {
					  gl_car_state = 0;   
            gl_CorrectNumFlag = 0;
            gl_flag2 = 0;
            gl_car.num = temp_Array[1];
            sEE_WriteBuffer(&gl_car.num,ADDRESS4_INEEPROM,1); 
						TXD_PASSIVE_MODE1(EVAL_COM2);
						
        }
    }
}


extern void Change_Speed(void)
{
    uint8_t temp_gl_buff[6] = {0};
    uint8_t i = 0;
    for(i = 0;i < 6;i++)
    {
        temp_gl_buff[i] = gl_Buff[i];
    }
    
    if(gl_StopFlag == 1|| 1)                 //小车停止时修改速度才有效
    {
        if(temp_gl_buff[1] > 0 && gl_Speed1 != temp_gl_buff[1])
        {
            gl_Speed1 = temp_gl_buff[1];
            gl_Store[ADDRESS5_INARRAY] = gl_Speed1;
            sEE_WriteBuffer(&gl_Speed1,ADDRESS5_INEEPROM,1);
            sEE_WaitEepromStandbyState();			
        }

        if(temp_gl_buff[2] > 0 && gl_Speed2 != temp_gl_buff[2])
        {
            gl_Speed2 = temp_gl_buff[2];
            gl_Store[ADDRESS6_INARRAY] = gl_Speed2;
            sEE_WriteBuffer(&gl_Speed2,ADDRESS6_INEEPROM,1);
            sEE_WaitEepromStandbyState();
        }

        if(temp_gl_buff[3] == 1 && gl_DirFlag1 != 1)
        {
            gl_DirFlag1 = 1;
            gl_Store[ADDRESS7_INARRAY] = gl_DirFlag1;
            sEE_WriteBuffer(&gl_DirFlag1,ADDRESS7_INEEPROM,1);
            sEE_WaitEepromStandbyState();
        }

				else if(temp_gl_buff[3] == 2 && gl_DirFlag1 != 2)
				{
					gl_DirFlag1 = 2;
					gl_Store[ADDRESS7_INARRAY] = gl_DirFlag1;
					sEE_WriteBuffer(&gl_DirFlag1,ADDRESS7_INEEPROM,1);
					sEE_WaitEepromStandbyState();
				}
				
				if(gl_SpeedUp != temp_gl_buff[4])
				{
					gl_SpeedUp = temp_gl_buff[4];
					gl_Store[ADDRESS8_INARRAY] = gl_SpeedUp;
					sEE_WriteBuffer(&gl_SpeedUp,ADDRESS8_INEEPROM,1);
					sEE_WaitEepromStandbyState();
					
				}
				
				if(gl_SlowDown != temp_gl_buff[5])
				{
					gl_SlowDown = temp_gl_buff[5];
					gl_Store[ADDRESS9_INARRAY] = gl_SlowDown;
					sEE_WriteBuffer(&gl_SlowDown,ADDRESS9_INEEPROM,1);
					sEE_WaitEepromStandbyState();
					
				}	
    }
}



extern void Start(void)
{	
    gl_StartFlag = 1;
    gl_SlowFlag = 0;
    gl_StopFlag = 0;
}

extern void Slow(void)
{
    gl_StartFlag = 0;
    gl_SlowFlag = 1;
    gl_StopFlag = 0;
}

extern void Stop(void)
{
//    RST_VAL_MOPST();     //伺服急停使能
//    Delay_Nms(5);
//    SET_VAL_MOPST();     //伺服急停禁能

    gl_StartFlag = 0;
    gl_SlowFlag = 0;
    gl_StopFlag = 1;
}

static void Change_Multi_Flag(void)
{
	if(gl_car.pos != 0)
		{
			if((gl_car.pos >= gl_Double_Pos_x[0] && gl_car.pos < gl_Double_Pos_y[0])|| (gl_car.pos >= gl_Double_Pos_x[1] && gl_car.pos < gl_Double_Pos_y[1]) || (gl_car.pos >= gl_Double_Pos_x[2] && gl_car.pos < gl_Double_Pos_y[2]))
			{
				if(gl_Double_Flag != 0)
				{
					gl_Multi_Flag = gl_Double_Flag + 1;
					gl_Double_Flag = 0;
				}
			}
		}
}



static void Senser_Detect(uint8_t* Senser0_Flag,uint8_t* Senser1_Flag,uint8_t* Senser2_Flag,uint8_t* Senser3_Flag,uint8_t* Senser4_Flag,uint8_t* Senser5_Flag,uint8_t* Senser6_Flag,uint8_t* Senser7_Flag,uint8_t* Senser8_Flag,uint8_t* Senser9_Flag)
{
		static uint8_t Senser0_Allow = 0;
    static uint8_t Senser1_Allow = 0;
    static uint8_t Senser2_Allow = 0;
    static uint8_t Senser3_Allow = 0;
    static uint8_t Senser6_Allow = 0;
	  static uint8_t timer_flag6 = 0;     //用于senser6:方向传感器
		static uint8_t timer_flag90 = 0;     //用于senser9的旋转定位
    static uint8_t timer_flag91 = 0; 
		static uint8_t timer_flag1 = 0;       //启动传感器电平检测

		
		if(EFF_VAL_SENSER9() && gl_StopFlag)
		{
			Delay_Nus(500);
			if(EFF_VAL_SENSER9() && gl_StopFlag)
			{
				timer_flag91 = 0;
				if(timer_flag90 > 19)
				{
					*Senser9_Flag = 1;
					timer_flag90 = 0;
				}
				else
				{
					timer_flag90++;
				}
			}
		}
		else
    {
        *Senser9_Flag = 0;
			  timer_flag90 = 0;
			  gl_DaoWeiFlag = 0;
    }
		
		
		
		if(NON_VAL_SENSER9() && gl_StopFlag)
		{
			Delay_Nus(500);
			if(NON_VAL_SENSER9() && gl_StopFlag)
			{
				timer_flag90 = 0;
				if(timer_flag91 > 19)
				{
					*Senser9_Flag = 2;
					timer_flag91 = 0;
				}
				else
				{
					timer_flag91++;
				}
			}
		}
		
		
		
		
		
	
		if(EFF_VAL_SENSER0()&& Senser0_Allow)                       //零位传感器有效
    {
        Delay_Nus(500);
        if(EFF_VAL_SENSER0())
        {
            *Senser0_Flag = 1;
            Senser0_Allow = 0;
        }
    }
		

    if(NON_VAL_SENSER0() && ~Senser0_Allow)                     
    {
        Senser0_Allow = 1;
    }
		
		
		
    
    if(EFF_VAL_SENSER1() && Senser1_Allow)                       //启动传感器有效
    {
        Delay_Nus(500);
        if(EFF_VAL_SENSER1())
        {
            *Senser1_Flag = 1;
						gl_Senser_Flag[1] = 0;   //屏蔽停止传感器1.5s
            Senser1_Allow = 0;
						
        }
    }

    if(NON_VAL_SENSER1() && ~Senser1_Allow)     
    {
        Senser1_Allow = 1;
    }
		
		
		
		
		if(EFF_VAL_SENSER1() && gl_StopFlag)   //	启动传感器电平检测 ，通过此模拟一个触发气缸的noneffective level:Senser1_Allow = 1;
		{
			Delay_Nus(500);
			if(EFF_VAL_SENSER1() && gl_StopFlag)
			{
				if(timer_flag1 > 20)
				{
					timer_flag1 = 0;
					Senser1_Allow = 1;
				}
				else
				{
					timer_flag1++;
				}
			}
		}
		else
		{
			timer_flag1 = 0;
		}
		
		


    if(NON_VAL_SENSER2() && ~Senser2_Allow && gl_Senser_Flag[0])                     
    {
				Delay_Nms(5);
				if(NON_VAL_SENSER2())
				{
					Senser2_Allow = 1;
				}
    }

    if(EFF_VAL_SENSER2() && Senser2_Allow && gl_Senser_Flag[0])                       //减速传感器有效
    {
				Delay_Nms(5);
        if(EFF_VAL_SENSER2())
        {  
					Senser2_Allow = 0;
					*Senser2_Flag = 1;
					gl_Senser_Flag[0] = 0;
        }
    }



		
		if(NON_VAL_SENSER3() && ~Senser3_Allow && gl_Senser_Flag[1])                     
    {
				Delay_Nms(5);
				if(NON_VAL_SENSER3())
				{
					Senser3_Allow = 1;
				}
    }

		
		if(EFF_VAL_SENSER3() && Senser3_Allow && gl_Senser_Flag[1])               //停止传感器
    {
				Delay_Nms(5);
        if(EFF_VAL_SENSER3())
        {
					*Senser3_Flag = 1;
					Senser3_Allow = 0;
					gl_Senser_Flag[1] = 0;
        }
    }
		
		if(EFF_VAL_SENSER3())
		{
			Delay_Nms(5);
			{
				if(EFF_VAL_SENSER3())
				{
					gl_Flag7 = 1;
				}
				else
				{
					gl_Flag7 = 0;
				}
			}
		}
		else
		{
			gl_Flag7 = 0;
		}
		
    
    if(EFF_VAL_SENSER4())                                      //右防撞传感器有效
    {
        Delay_Nus(500);
        if(EFF_VAL_SENSER4())
        {
            *Senser4_Flag = 1;
        }
    }
    else
    {
        *Senser4_Flag = 0;
    }

    if(EFF_VAL_SENSER5())                                      //左防撞传感器有效
    {
        Delay_Nus(500);
        if(EFF_VAL_SENSER5())
        {
            *Senser5_Flag = 1;
        }
    }
    else
    {
        *Senser5_Flag = 0;
    }
		

   
    
		if(NON_VAL_SENSER6() && ~Senser6_Allow && gl_Senser_Flag[2])                //换向传感器         
    {
				Delay_Nms(5);
				if(NON_VAL_SENSER6())
				{
					Senser6_Allow = 1;
					timer_flag6 = 0;
				}
    }
		

		
		if(EFF_VAL_SENSER6() && Senser6_Allow && gl_Senser_Flag[2] && gl_StopFlag)               
    {
				Delay_Nms(5);
        if(EFF_VAL_SENSER6())
        {
					if(timer_flag6 > 5)   //参数可能要调整,
					{
						gl_Senser_Flag[2] = 0;
						*Senser6_Flag = 1;
						Senser6_Allow = 0;
						timer_flag6 = 0;
					}
					else
					{
						timer_flag6++;
					}
        }
				else
				{
					timer_flag6 = 0;
				}
    }
}






