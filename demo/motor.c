#include "motor.h"


extern void motor_control(void)
{
    static int32_t pwm = 0 ;
    if(ISEFF_MOTOR())
    {
        NONEFF_MOTOR();
        dangwei_control(&pwm);
        motor_out(&pwm);
    }
}





static void motor_out(int32_t * PWM)
{
    int32_t dangwei = *PWM;
    static uint8_t flag = 0;
    static int32_t dangwei_last = 0;

    if(dangwei_last != dangwei)   //�ϴεĵ�λ����εĵ�λ��һ�����ñ�־λflag = 1;
    {
        dangwei_last = dangwei;
        flag = 1;
    }
    
    if(flag == 1)
    {
        if(ISDIR_FOREWARD())
        {
            if(gl_DirFlag1 == 1)
            {
                TIM2->CCR3 = 0;
                if(dangwei == 0)
                {
                    TIM2->CCR4 = 0;
                }
                else
                {
                    TIM2->ARR = (uint32_t)(60000000 / dangwei - 1);
                    TIM2->CCR4 = TIM2->ARR / 2; 
                }
            }
            else if(gl_DirFlag1 == 2)
            {
                TIM2->CCR4 = 0;
                if(dangwei == 0)
                {
                    TIM2->CCR3 = 0;
                }
                else
                {
                    TIM2->ARR = (uint32_t)(60000000 / dangwei - 1);
                    TIM2->CCR3 = TIM2->ARR / 2; 
                }
            }
        }
        else
        {
            if(gl_DirFlag1 == 1)
            {
                TIM2->CCR4 = 0;
                if(dangwei == 0)
                {
                    TIM2->CCR3 = 0;
                }
                else
                {
                    TIM2->ARR = (uint32_t)(60000000 / dangwei - 1);
                    TIM2->CCR3 = TIM2->ARR / 2; 
                }
            }
            else if(gl_DirFlag1 == 2)
            {
                TIM2->CCR3 = 0;
                if(dangwei == 0)
                {
                    TIM2->CCR4 = 0;
                }
                else
                {
                    TIM2->ARR = (uint32_t)(60000000 / dangwei - 1);
                    TIM2->CCR4 = TIM2->ARR / 2; 
                }
            }
        }
    }
}


extern void motor_stop(void)
{
	TIM2->CCR3 = 0;
	TIM2->CCR4 = 0;
	TIM2->ARR = (uint32_t)(60000000 / 5000 - 1);
}




/*************�Ķ�����λ��λ��������**************/


static void dangwei_control(int32_t * PWM)
{
    int32_t dangwei = *PWM;
    static uint32_t dangwei_SpeedUp = 0;
    static uint32_t dangwei_SlowDown = 0;
    static uint32_t dangwei_Colli = 0;
    static uint32_t motor_max_speed = 0;
    static uint32_t motor_slow_speed = 0;
    static uint32_t temp_motor_max_speed = 0;
    gl_pwm = *PWM;
	
		if(gl_Flag6 == 1)
		{
			motor_max_speed =  (uint32_t)(NORMAL_MAX_SPEED * 70 / 100) ; 
		}
		else
		{
			if(gl_car.pos == gl_pos + 2 || gl_car.pos == 0)    //С��������������ʱ����С������ٶ�Ϊ0.2m
			{
        motor_max_speed =  (uint32_t)(NORMAL_MAX_SPEED * 20 / 100) ; 
			}
			else if(gl_car.pos == gl_pos)                      //С������������ʱ����С������ٶ�Ϊ0.4m
			{
				motor_max_speed =  (uint32_t)(NORMAL_MAX_SPEED * 40 / 100) ; 
			}
			else  // С����������ʱ������ٶ�Ϊ1m
			{
				motor_max_speed = (uint32_t)(NORMAL_MAX_SPEED * (uint32_t)gl_Speed1/ 100);
			}
		}
		
		if(gl_car.pos == gl_pos + 1) //С������������ʱǰ5s����С������ٶ�Ϊ0.4m/s,5-35sС���ٶ�Ϊ1m/s,35s������С���ٶ�Ϊ0.6m/s
		{
			if(gl_car.pos1 < 5)
			{
				motor_max_speed = (uint32_t)(NORMAL_MAX_SPEED * 40 / 100);
			}
			else if(gl_car.pos1 < 35)
			{
				motor_max_speed = (uint32_t)(NORMAL_MAX_SPEED * gl_Speed1 / 100);
			}
			else
			{
				motor_max_speed = (uint32_t)(NORMAL_MAX_SPEED * 60 / 100);
			}
			
		}
		
		
    motor_slow_speed = (uint32_t)(SLOW_MAX_SPEED * (uint32_t)gl_Speed2 / 100);
		if(gl_car.pos == gl_pos + 2)
		{
			motor_slow_speed = (uint32_t)(SLOW_MAX_SPEED * 10 / 100);
		}
		
    temp_motor_max_speed = motor_max_speed / 40;
	
    
    /******��������1***************/
    if(dangwei > 380000)
    {
        dangwei_SlowDown = 10000;
    }
    else if(dangwei > 330000)
    {
        dangwei_SlowDown = 50000;
    }
    else if(dangwei > 250000)
    {
        dangwei_SlowDown = 80000;
    }
    else if(dangwei > 150000)
    {
        dangwei_SlowDown = 100000;
    }
    else if(dangwei > 70000)
    {
        dangwei_SlowDown = 80000;
    }
    else if(dangwei > 20000)
    {
        dangwei_SlowDown = 50000;
    }
    else 
    {
        dangwei_SlowDown = 10000;
    }
    dangwei_Colli = dangwei_SlowDown;
		

	if(gl_car.pos != 21)
	{
		if(dangwei > 38 * gl_pwmcolli)
    {
        dangwei_Colli = 1 * gl_pwmcolli;
    }
    else if(dangwei > 33 * gl_pwmcolli)
    {
        dangwei_Colli = 5 * gl_pwmcolli;
    }
    else if(dangwei > 25 * gl_pwmcolli)
    {
        dangwei_Colli = 8 * gl_pwmcolli;
    }
    else if(dangwei > 15 * gl_pwmcolli)
    {
        dangwei_Colli = 10 * gl_pwmcolli;
    }
    else if(dangwei > 7 * gl_pwmcolli)
    {
        dangwei_Colli = 8 * gl_pwmcolli;
    }
    else if(dangwei > 2 * gl_pwmcolli)
    {
        dangwei_Colli = 5 * gl_pwmcolli;
    }
    else 
    {
        dangwei_Colli = 1 * gl_pwmcolli;
    }	

    /********����dangwei_Colli����Ϊ10000***********/
    if(dangwei_Colli < 10000)
    {
        dangwei_Colli = 10000;
    }
	}
    

		
		
    /******��������1***************/
    if(gl_SlowFlag == 1 )
    {
        if(dangwei > 38 * gl_pwmslow)
        {
            dangwei_SlowDown = 1 * gl_pwmslow;
        }
        else if(dangwei > 33 * gl_pwmslow)
        {
            dangwei_SlowDown = 5 * gl_pwmslow;
        }
        else if(dangwei > 25 * gl_pwmslow)
        {
            dangwei_SlowDown = 8 * gl_pwmslow;
        }
        else if(dangwei > 15 * gl_pwmslow)
        {
            dangwei_SlowDown = 10 * gl_pwmslow;
        }
        else if(dangwei > 7 * gl_pwmslow)
        {
            dangwei_SlowDown = 8 * gl_pwmslow;
        }
        else if(dangwei > 2 * gl_pwmslow)
        {
            dangwei_SlowDown = 5 * gl_pwmslow;
        }
        else 
        {
            dangwei_SlowDown = 1 * gl_pwmslow;
        }	
				if(gl_SlowDown == 0)
				{
					gl_SlowDown = 2;
				}
				
				if(gl_car.pos != 0 && gl_car.pos != 1 && gl_car.pos != gl_pos + 1 && gl_car.pos != gl_pos + 2) //located in the position of 0/1/21,the gl_SlowDown parameter should be keep 1.
				{
					dangwei_SlowDown = dangwei_SlowDown / gl_SlowDown;
				}
    }
    /*********��dangwei_SlowDown ���б���,��֤ʼ�ղ�Ϊ��***********/
    if(dangwei_SlowDown == 0)
    {
        dangwei_SlowDown = 10000;
    }
	
    /******��������1***************/
    if(dangwei < 20000)
    {
        dangwei_SpeedUp = 10000;
    }
    else if(dangwei < 70000)
    {
        dangwei_SpeedUp = 50000;
    }
    else if(dangwei < 150000)
    {
        dangwei_SpeedUp = 80000;
    }
    else if(dangwei < 250000)
    {
        dangwei_SpeedUp = 100000;
    }
    else if(dangwei < 330000)
    {
        dangwei_SpeedUp = 80000;
    }
    else if(dangwei < 380000)
    {
        dangwei_SpeedUp = 50000;
    }
    else 
    {
        dangwei_SpeedUp = 10000;
    }
	
    /******��������1***************/
    if(dangwei < 2 * temp_motor_max_speed)
    {
        dangwei_SpeedUp = 1 * temp_motor_max_speed;
    }
    else if(dangwei < 7 * temp_motor_max_speed)
    {
        dangwei_SpeedUp = 5 * temp_motor_max_speed;
    }
    else if(dangwei < 15 * temp_motor_max_speed)
    {
        dangwei_SpeedUp = 8 * temp_motor_max_speed;
    }
    else if(dangwei < 25 * temp_motor_max_speed)
    {
        dangwei_SpeedUp = 10 * temp_motor_max_speed;
    }
    else if(dangwei < 33 * temp_motor_max_speed)
    {
        dangwei_SpeedUp = 8 * temp_motor_max_speed;
    }
    else if(dangwei < 38 * temp_motor_max_speed)
    {
        dangwei_SpeedUp = 5 * temp_motor_max_speed;
    }
    else 
    {
        dangwei_SpeedUp = 1 * temp_motor_max_speed;
    }
		if(gl_SpeedUp == 0)
		{
			gl_SpeedUp = 2;
		}
		
		if(gl_car.pos != 0  && gl_car.pos != gl_pos + 1) //located in the position of 0/1/21,the gl_SlowDown parameter should be keep 1.
		{
			dangwei_SpeedUp = dangwei_SpeedUp / gl_SpeedUp;
		}
		
    if(gl_AlertStopFlag == 1)
    {
        gl_AlertStopFlag = 0;
        dangwei = 0;
    }
    
    /**************1,15,16,20��ͣ����λ********************/
	
//	if (!(gl_StopFlag == 1 && (gl_car.pos == 1 || gl_car.pos == gl_pos ||(gl_car.pos == 15  )||((gl_car.pos == 16)))))  //  1��20�Ź�λ 
//	{
//		gl_AlertFlag = 0;
//	}
//
    /**************1,20��ͣ����λ********************/
//    if (!(gl_StopFlag == 1 && (gl_car.pos == 1 || gl_car.pos == gl_pos )))  //  1��20�Ź�λ 
//    {
//        gl_AlertFlag = 0;
//    }
		
		if(gl_StartFlag == 1)
		{
			gl_AlertFlag = 0;
			gl_Senser_Flag[4] = 0;  
		}
		
    if(gl_StopFlag)
    {
        if(gl_StopFlag == 129 || gl_StopFlag == 123) 
        {
            if(dangwei <= dangwei_SlowDown)
            {
                gl_car_state = 0;    //�㶯�ͼ�ͣ��
                dangwei = 0;
            }
            else
            {
                dangwei -= dangwei_SlowDown;
            }
        }
        else
        {
            if(gl_AlertFlag == 1)
            {
                dangwei = 0;
							  gl_StopFlag = 100;
								gl_Senser_Flag[4] = 0;
            }
            else
            {					
                /**************1,15,16,20��ͣ����λ********************/
//			    if(gl_car.pos == 1 || gl_car.pos == gl_pos || gl_car.pos == 15 || gl_car.pos == 16)
//				{
//				    dangwei = motor_slow_speed / 5;
//				}
								
                /**************1,20��ͣ����λ********************/
                if(gl_car.pos == 1 || gl_car.pos == gl_pos)
                {
                    dangwei = motor_slow_speed / 5;
										gl_Senser_Flag[4] = 1;
                }
                else
                {
                    dangwei = 0;
                }
            }
        }
    }	
    else if(gl_SlowFlag)
    {
        if(gl_ColliFlag)
        {
            if(dangwei <= dangwei_Colli)
            {
                dangwei = 0;
            }
            else
            {
                dangwei -= dangwei_Colli;
            }
        }
        else
        {
            if(dangwei <= motor_slow_speed )
            {
                dangwei = motor_slow_speed;
            }
            else
            {
                dangwei -= dangwei_SlowDown;
            }
            
            /********�����쳣����:dangwei Ϊ0 ���Ǹ���ʱ�����б���*********/
            if(dangwei <= 0)
            {
                dangwei = motor_slow_speed;
            }
        }
    }
    
    else
    {
        if(gl_StartFlag)    //�ŷ����ײ�������
        {
            if(gl_ColliFlag)
            {
                if(dangwei <= dangwei_Colli)
                {
                    dangwei = 0;
                }
                else
                {
                    dangwei -= dangwei_Colli;
                }
            }
            else
            {
                if(dangwei >= motor_max_speed)
                {
                    dangwei = motor_max_speed;
                }
                else
                {
                    dangwei += dangwei_SpeedUp;
                }
                if(dangwei <= 0)
                {
                    dangwei = dangwei_SpeedUp;
                }
            }
        }
    }
    
		
		
//    /******�ŷ���������**************/
//    if(NONEFF_MSRDY())
//    {
////			/**************1,15,16,20��ͣ����λ********************/
////			  if(gl_StopFlag == 1 && (gl_car.pos == 1 || gl_car.pos == gl_pos ||(gl_car.pos == 15 )||((gl_car.pos == 16 ))))   //  
////				{
////					 gl_AlertFlag = 1;
////				}
//        /**************1,20��ͣ����λ********************/
//        if(gl_StopFlag == 1 && (gl_car.pos == 1 || gl_car.pos == gl_pos))
//        {
//            gl_AlertFlag = 1;
//        }
//        
//        TXD_ACTIVE_MODE1(EVAL_COM2);
//        SET_VAL_MSON();         //�ŷ�����
//        SET_VAL_MARST(); 
//        Delay_Nms(100);
//        RST_VAL_MARST();

//				 SET_VAL_MSON();
//         Delay_Nms(100);
//         RST_VAL_MSON();   //�ŷ�ʹ��
//				 Delay_Nms(500);   //��֤�������ʹ��
//    }
    /******�ŷ���������**************/
    if(NONEFF_MSRDY() || EFF_MALRM())
    {
//			/**************1,15,16,20��ͣ����λ********************/
//			  if(gl_StopFlag == 1 && (gl_car.pos == 1 || gl_car.pos == gl_pos ||(gl_car.pos == 15 )||((gl_car.pos == 16 ))))   //  
//				{
//					 gl_AlertFlag = 1;
//				}
        /**************1,20��ͣ����λ********************/
        if(gl_StopFlag == 1 && (gl_car.pos == 1 || gl_car.pos == gl_pos))
        {
            gl_AlertFlag = 1;
        }
				dangwei = 0;
        
        TXD_ACTIVE_MODE1(EVAL_COM2);
				printf("hello world");
        SET_VAL_MSON();         //�ŷ�����
        RST_VAL_MARST();
				Delay_Nms(500);
				SET_VAL_MARST(); 
				Delay_Nms(500);   //��֤�������ʹ��
        RST_VAL_MSON();   //�ŷ�ʹ��
				Delay_Nms(500);   //��֤�������ʹ��
    }
    *PWM = dangwei;
}

