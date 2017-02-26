#include "car.h"






extern void Car_Config_Mode(void)
{

    uint8_t i = 0;
    gl_opr = 0;
    for(i = 0;i < 2*gl_pos + 3;i++)
    {
        gl_Store[i] = gl_Buff[i];  //保存配置数据
    }
    gl_car_all = gl_Buff[1];			
    Change_PosFlag(gl_Buff);
		gl_Multi_Flag = gl_posFlag[gl_car.pos];    //根据小车的配置信息来决定小车下次的停止位。
		gl_Double_Flag = 0;                        //配置时将多线作用暂时去掉
		gl_Store[ADDRESS0_INARRAY] = gl_opr;
		sEE_WriteBuffer(&gl_opr,ADDRESS0_INEEPROM,1);
		sEE_WriteBuffer(gl_Store,sEE_WRITE_ADDRESS1+2,60);
		sEE_WaitEepromStandbyState();
		
}

extern void Init_State(void)
{
	gl_Double_Flag = 0;
	gl_Multi_Flag = 1;
	gl_SlowDownErrorData_Flag = 0;
	gl_StopErrorData_Flag = 0;
	gl_CheckStop_Flag[0] = 0;
	gl_CheckStop_Flag[1] = 0;
	gl_car.opr = gl_opr + 1;
	gl_car.pos = gl_pos + 1;
	gl_DirFlag = BACKWARD;
	gl_StartFlag = 0;
  gl_SlowFlag = 0;
  gl_StopFlag = 123;
	gl_Status[0] = 1;
	gl_Status[1] = 0;
	gl_Status[2] = 0;
}



extern void Control_Mode1(void)
{
    Senser_Detect_Mode1();
}

extern void Control_Mode2(void)
{
    Senser_Detect_Mode2(); 
}

extern void Control_Mode3(void)
{
	Senser_Detect_Mode3();
}

extern void Control_Mode4(void)
{
	Senser_Detect_Mode4();
}



extern void Normal_Mode(void)
{
    while(1)
    {
				Data_Inter();
        if(gl_car_state == 1)
        {
            Control_Mode1();
        }
        else if(gl_car_state == 2 ) //正常启动且小车正常配置进入Control_Mode2
        {
            Control_Mode2();
        }
				else if(gl_car_state == 3)
				{
					Control_Mode3();
				}
				else if(gl_car_state == 4)
				{
					Control_Mode4();
				}
				
				if(gl_car_state == 2 || gl_car_state == 3)
				{
					motor_control();
				}
			}
}

extern void Load_Config(void)
{
    uint8_t flag1 = 0;
    uint8_t flag2 = 0;
    uint8_t temp_car_num = 0;	
		uint8_t temp_Speed1 = 0;
		uint8_t temp_Speed2 = 0;
		uint8_t temp_SpeedUp = 0;
		uint8_t temp_SlowDown = 0;
		uint8_t temp_Multi_Flag = 0;
		uint8_t temp_Flag5 = 0;
    volatile uint16_t NumDataRead = 0;
    gl_opr = 0;



    /******************读特征字*************************/
    NumDataRead = 1;
    sEE_ReadBuffer(&flag1,sEE_READ_ADDRESS1,(uint16_t* )(&NumDataRead));
    sEE_ReadBuffer(&flag2,sEE_READ_ADDRESS1+1,(uint16_t* )(&NumDataRead));
    Delay(100);
    NumDataRead = 160;                                                                  //读出100个字节的数据
    if(flag1 == 0x55 && flag2 == 0xaa)                                                  //从EEPROM读取配置信息
    {
        sEE_ReadBuffer(gl_Store,sEE_READ_ADDRESS1+2,(uint16_t* )(&NumDataRead));        //读出100个字节的数据
        Delay(100);
				gl_pos = gl_Store[ADDRESS11_INARRAY];
				Change_PosFlag(gl_Store);
        if(gl_opr == gl_Store[ADDRESS0_INARRAY])                                                //自校验，保存的配置信息逻辑正常
        {
            gl_car.opr = gl_Store[ADDRESS1_INARRAY];
            gl_car.pos = gl_Store[ADDRESS2_INARRAY];
            gl_DirFlag = gl_Store[ADDRESS3_INARRAY];
            temp_car_num = gl_Store[ADDRESS4_INARRAY];
            if(temp_car_num != gl_car.num)
            {
                gl_car.num = temp_car_num;
            }
						temp_Speed1 = gl_Store[ADDRESS5_INARRAY];
						if(temp_Speed1 <101 && temp_Speed1 > 0)
						{
							gl_Speed1 = temp_Speed1;
						}
						temp_Speed2 = gl_Store[ADDRESS6_INARRAY];
						if(temp_Speed2 <101 && temp_Speed2 > 0)
						{
							gl_Speed2 = temp_Speed2;
						}
						gl_DirFlag1 = gl_Store[ADDRESS7_INARRAY];
						
						temp_SpeedUp = gl_Store[ADDRESS8_INARRAY];
						if(temp_SpeedUp > 0 && temp_SpeedUp < 21)
						{
							gl_SpeedUp = temp_SpeedUp;
						}
						temp_SlowDown = gl_Store[ADDRESS9_INARRAY];
						if(temp_SlowDown > 0 && temp_SlowDown < 21)
						{
							gl_SlowDown = temp_SlowDown;
						}
						gl_car.pos1 = gl_Store[ADDRESS10_INARRAY];
						 
						gl_Double_Flag = gl_Store[ADDRESS12_INARRAY];       //是否响应双线操作
						
						temp_Multi_Flag = gl_Store[ADDRESS13_INARRAY];
						if(temp_Multi_Flag > 0)
						{
							gl_Multi_Flag = temp_Multi_Flag;
						}
						
						gl_CheckStop_Flag[0] =gl_Store[ADDRESS14_INARRAY];
						
						gl_StartFlag = gl_Store[ADDRESS15_INARRAY];
						gl_SlowFlag = gl_Store[ADDRESS16_INARRAY];
						gl_ColliFlag = gl_Store[ADDRESS17_INARRAY];
						gl_StopFlag = gl_Store[ADDRESS18_INARRAY];
						
						gl_Status[0] = gl_Store[ADDRESS19_INARRAY];
						gl_Status[1] = gl_Store[ADDRESS20_INARRAY];
						gl_Status[2] = gl_Store[ADDRESS21_INARRAY];
						gl_AlertFlag = gl_Store[ADDRESS22_INARRAY];
						temp_Flag5 = gl_Store[ADDRESS23_INARRAY];
						if(temp_Flag5 != 0)
						{
							gl_Flag5 = temp_Flag5;
						}
						gl_flag1 = gl_Store[ADDRESS24_INARRAY];

        }
        else
        {
            Board_Init_Mode();
        }
    }
    else
    {
        Board_Init_Mode();
    }
}


/*****************上位机发送指令进行用户配置****************************/
/*******example:
 *小车总数gl_Buff[0] = 25
 *小车总工位数25
 *小车有效操作台数13:  1 0 1 1 0 0 1 0 1 1 1 0 1 1 1 0 1 1 1
 *小车双操作台位置所在工位号: 3 4; 9 10 11
 *则变换后的gl_posFlag[21] = {1,2,0,2,1,0,0,3,0,3,2,1,0,1,1,1,0,1,1,1,1};
 ***********************************************************************/



extern void Change_PosFlag(uint8_t *Temp_Data)
{
    uint8_t i = 0,j = 0,k = 0;
    uint8_t i_temp = 1;
		uint8_t flag = 1;
		
		gl_opr = 0;
		gl_pos = 20;
		
		for(i = 0;i < 3;i++)
		{
			gl_Double_Pos_x[i] = 0;
			gl_Double_Pos_y[i] = 0;
		}
		
    for(i = 0;i < gl_pos+3 ; i++)
    {
        gl_posFlag[i] = 0;
    }
		
		for(i = 0;i < 4 ; i++)
		{
			gl_SpePos[i] = 30;
		}
    
    for(i = 2 ; i < 2 + gl_pos ; i++)
    {
        gl_posFlag[i-1] = 0;
        if(Temp_Data[i] != 0)
        {
            gl_opr++;
            gl_posFlag[i-1] = 1;
            if(Temp_Data[i] == i - 1 + 128)
            {
                i++;
                while(Temp_Data[i] != i-1)
                {
                    if(Temp_Data[i] == i - 1 + 128)
                    {
                        gl_posFlag[i_temp-1]++;
                        gl_posFlag[i-1] = 1;
                        gl_opr++;
                    }
                    i++;
                }
                gl_posFlag[i-1] = 1;
                gl_opr++;
            }
            i_temp = i;
        }
    }

    for(i = 2; i < 2 + gl_pos ; i++)
    {
        if(gl_posFlag[i-1] ==2)
        {
            while(gl_posFlag[i-1] != 1)
            {
                i++;
            }
            gl_posFlag[i-1] = 2;

        }
        else if(gl_posFlag[i-1] ==3)
        {
            while(gl_posFlag[i-1] != 1)
            {
                i++;
            }
            gl_posFlag[i-1] = 3;
            while(gl_posFlag[i-1] != 1)
            {
                i++;
            }
            gl_posFlag[i-1] = 2;
        }
    }
		
		
		
		j = 1;
		for(i = 1;i < gl_pos;i++)
		{
			if(gl_posFlag[i+1] == 1)
			{
				j = i + 1;
				flag = 1;
				continue;
			}
			else if(gl_posFlag[i+1] == 0)
			{
				continue;
			}
			else if(gl_posFlag[i+1] > 1 && flag == 1)
			{
				flag = 0;
				gl_Double_Pos_x[k] = j;
				gl_Double_Pos_y[k] = i+1;
				k++;
			}
		}	

    gl_posFlag[0] = 1;
    gl_posFlag[gl_pos + 1] = 1;
    gl_posFlag[gl_pos + 2] = 1;
		
		j = 0;
		for(i = 2;i < 2 + gl_pos;i++)
		{
			if(Temp_Data[i] != 0)
			{
				j++;
			}
			gl_pos2opr[i-1] = j;
		}
		gl_pos2opr[0] = 0;                  //0 号工位， 对应左升降梯
		gl_pos2opr[gl_pos + 1] = j + 1;     //gl_pos+1号工位，对应右升降梯
		gl_pos2opr[gl_pos + 2] = j + 2;     //gl_pos+2号工位，对应线下的工位
		
		j = 0;
		
		for(i = 2;i < 2 + gl_pos;i++)
		{
			if(Temp_Data[i] > 128 && Temp_Data[i+1] < 128)
			{
				gl_SpePos[j] = i ;
				j++;
				if(j > 3)
				{
					j = 3;
				}
			}
		}
		
		if(Temp_Data[gl_car.pos+1] > 128)
		{
			gl_Flag6 = 1;
		}
		else
		{
			gl_Flag6 = 0;
		}
		
}


extern void Board_Init(void)
{
    if(EFF_INIT())
    {
			Board_Init_Mode();
			gl_Init_Flag = 1;
		}
}


static void Board_Init_Mode(void)
{
    uint8_t flag1 = 0x55;
    uint8_t flag2 = 0xaa;
    gl_car.num = 0;
    gl_pos = 20 ;
    gl_DirFlag = BACKWARD;
    gl_DirFlag1 = 1;
    gl_Speed1 = 80;
    gl_Speed2 = 20;
    gl_SpeedUp = 2;
    gl_SlowDown = 2;
		gl_StartFlag = 0;
	  gl_SlowFlag = 0;
	  gl_ColliFlag = 0;
	  gl_StopFlag = 1;
	  gl_AlertFlag = 0;
    Change_PosFlag(gl_Store);
    gl_Store[ADDRESS0_INARRAY] = gl_opr;
    gl_Store[ADDRESS1_INARRAY] = gl_car.opr;
    gl_Store[ADDRESS2_INARRAY] = gl_car.pos;
    gl_Store[ADDRESS3_INARRAY] = gl_DirFlag;
    gl_Store[ADDRESS4_INARRAY] = gl_car.num;
    gl_Store[ADDRESS5_INARRAY] = gl_Speed1;
    gl_Store[ADDRESS6_INARRAY] = gl_Speed2;
    gl_Store[ADDRESS7_INARRAY] = gl_DirFlag1;
    gl_Store[ADDRESS8_INARRAY] = gl_SpeedUp;
    gl_Store[ADDRESS9_INARRAY] = gl_SlowDown;
    gl_Store[ADDRESS10_INARRAY] = gl_car.pos1;
		gl_Store[ADDRESS11_INARRAY] = gl_pos;
		gl_Store[ADDRESS12_INARRAY] = gl_Double_Flag;
		gl_Store[ADDRESS13_INARRAY] = gl_Multi_Flag;
		gl_Store[ADDRESS14_INARRAY] = gl_CheckStop_Flag[0];
		gl_Store[ADDRESS15_INARRAY] = gl_StartFlag;
		gl_Store[ADDRESS16_INARRAY] = gl_SlowFlag;
		gl_Store[ADDRESS17_INARRAY] = gl_ColliFlag;
		gl_Store[ADDRESS18_INARRAY] = gl_StopFlag;
		gl_Store[ADDRESS22_INARRAY] = gl_AlertFlag;
		gl_Store[ADDRESS23_INARRAY] = gl_Flag5;
    sEE_WriteBuffer(&flag1,sEE_WRITE_ADDRESS1,1);   										//第一个字节写特征值0x55
    sEE_WriteBuffer(&flag2,sEE_WRITE_ADDRESS1+1,1); 										//第二个字节写特征值0xaa
    sEE_WriteBuffer(gl_Store,sEE_WRITE_ADDRESS1+2,BUFFER_SIZE);
    sEE_WaitEepromStandbyState();	
}


static void Data_Inter(void)
{
	      if(gl_RxRight)  //成功接收到上位机的指令
        { 
					if(gl_OpenFlag[1] == 2)
					{
						gl_OpenFlag[1] = 0;
						Start_Car();
					}

					if(gl_CheckFlag == 0 && gl_CheckFlag1 == 1)   //gl_CheckFlag1 == 1:表示通讯之前断开过;
						{
							gl_CheckFlag = 1;
							gl_CheckFlag1 = 0;
						}
	
            gl_RxRight = 0;
            
						if(gl_Buff[0] == 9 && gl_Buff[1] == 4)  //上位机查询小车状态
						{
							gl_TxFlag = 0;  //不通过中断发送状态
						}
						else if(gl_Buff[0] == 6 && (gl_Buff[2] == 1||gl_Buff[2] == 2) && gl_Buff[1] != 0)    //进入修改小车编号模式，开始的数据发送。
						{
							gl_TxFlag = 0;
						}
						else if(gl_Buff[0] == 10 && gl_Buff[1] != gl_car.num && gl_Buff[3] != gl_car.num) //执行多线操作时，针对跳过的车进行数据发送
						{
							gl_TxFlag = 0;
						}
						else if(gl_Buff[0] == 4 && gl_Buff[1] != gl_car.num)    //点动时，只针对被点动的车进行数据交互
						{
							gl_TxFlag = 0;
						}
						else if(gl_Buff[0] == 11 && gl_Buff[1] != gl_car.num)   //上位机主动修改小车位置，只针对被修改的小车进行数据交互
						{
							gl_TxFlag = 0;
						}
						else 
						{
							gl_TxFlag = 1;
						}

            switch(gl_Buff[0])
            {
                case 1:
                    Car_Config_Mode();
                    break;
                case 2:
                    Inter_Action();
                    break;
                case 3:
                    Shang_Xian();
                    break;
                case 4:
                    Dian_Dong();
                    break;
                case 5:
                    Zheng_Chang();
                    break;
                case 6:
                    Chang_Num();
                    break;
                case 8:
                    Change_Speed();
                    break;
								case 9:
										if(gl_Buff[1] == 2 && gl_car.num == gl_Buff[2])  //通过扫码枪更新工位
										{
											gl_car.pos = gl_Buff[3];
											gl_car.opr = gl_pos2opr[gl_car.pos];
										}
										
										if(gl_Buff[1] == 4 && gl_car.num == gl_Buff[2] )   //上位机查询小车状态
										{
											TXD_ACTIVE_MODE1(EVAL_COM2);
										}
									break;
								case 10: //双线操作
										if(gl_Buff[1] == gl_car.num)
										{
											gl_Double_Flag = gl_Buff[2];
										}
										else if(gl_Buff[3] == gl_car.num)
										{
											gl_Double_Flag = gl_Buff[4];
										}
										break;
								case 11:
									if(gl_Buff[1] == gl_car.num)     //上位机主动修改小车的编号，用于调试
									{
										gl_car.pos = gl_Buff[2];
										gl_car.opr = gl_pos2opr[gl_car.pos];
										if(gl_car.pos == gl_pos + 1 || gl_car.pos == gl_pos + 2 )   
										{
											gl_DirFlag = BACKWARD;
										}
										else
										{
											gl_DirFlag = FOREWARD;
										}
										gl_Multi_Flag = gl_posFlag[gl_car.pos];
									}
									break;
            }          
            Tx_Enable();	
        }
}
