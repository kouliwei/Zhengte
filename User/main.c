#include "include.h"

uint8_t gl_Tim12Flag = 0;
uint8_t gl_ResetFlag1 = 0;
uint8_t gl_ResetFlag = 0;
uint8_t gl_OpenFlag[2] = {0};
uint8_t gl_ErrorData_Flag = 0;
uint8_t gl_Flag7 = 0;
uint8_t gl_Flag6 = 0;      //����ʱ����ٶȽ�Ϊ0.7m�ı�־λ
uint8_t gl_SpePos[4] = {30,30,30,30};
uint8_t gl_Flag5 = 1;
uint8_t gl_Flag4 = 0;
uint8_t gl_DaoWeiFlag = 0; 
uint8_t gl_Flag3 = 0;
uint8_t gl_Daowei = 0;
int32_t gl_pwm = 0 ;
int32_t gl_pwmslow = 0 ;
int32_t gl_pwmcolli = 0 ;
uint8_t gl_AlertFlag = 0;
uint8_t gl_Status[6] = {0};
uint8_t gl_DingweiRightData_Flag = 0;
uint8_t gl_DingweiErrorData_Flag = 0;
uint8_t gl_DingweiPos[3] = {30,30,30};
uint8_t gl_VirStart_Flag = 0;
uint8_t gl_CheckStop_Flag[2] = {0};
uint8_t gl_SlowDownErrorData_Flag = 0;
uint8_t gl_StopErrorData_Flag = 0;
uint8_t gl_SlowDownRightData_Flag = 0;
uint8_t gl_StopRightData_Flag = 0;
uint8_t gl_Senser_Flag[6] = {1,1,1,0,0,0};  //gl_Senser_Flag[0]:������ʱ gl_Senser_Flag[1]:ֹͣ��ʱ��gl_Senser_Flag[2]��������ʱ��gl_Senser_Flag[3]����ײ��gl_Senser_Flag[4]:������ʱ;gl_Senser_Flag[5]:���������ʱ;
uint8_t gl_SlowSenser_Flag = 1;
uint8_t gl_StopSenser_Flag = 1;
uint8_t gl_Multi_Flag = 1;  
uint8_t gl_Double_Flag = 0;
uint8_t gl_Double_Pos_x[3] = {0};   
uint8_t gl_Double_Pos_y[3] = {0};
uint8_t gl_Init_Flag = 0;
uint8_t gl_AlertStopFlag = 0;
uint8_t gl_CheckFlag = 0;
uint8_t gl_CheckFlag1 = 1;
uint8_t gl_Speed1 = 80;     //��ʶ���������ٶ�Ϊmotor_max_speed = MAX_SPEED* 80%
uint8_t gl_Speed2 = 20; 		//��ʶ���ٵ�ƽ���ٶ�Ϊ�������ٶȵ�20% motor_slow_speed = motor_max_speed * 20%
uint8_t gl_SpeedUp = 2;
uint8_t gl_SlowDown = 2;
uint8_t gl_JiTingFlag = 0;
uint8_t gl_flagStop = 0;     //����ֹͣ��־λ
uint8_t gl_flagRx[2]={0};
uint8_t gl_CorrectNumFlag = 0;
uint8_t gl_flag2 = 0;    //�����޸�С����ŵı�־λ
uint8_t gl_flag1 = 0;    //�������¶�λ�ı�־λ
uint8_t gl_flag = 1;     //LCD ���õı�־λ
uint8_t gl_Buff[255] = {1,30,1,0,0,4,0,0,135,0,0,138,0,140,13,14,143,0,0,0,147,0,0,22};
uint8_t gl_TxBuff[255] = {0};
uint8_t gl_RxRight = 0; //gl_RxRight = 1:����ɹ����յ���λ�����͹�����ָ��
uint8_t gl_TxFlag = 0;  //gl_TxFlag = 0:�����͵���С���Լ��������͵���Ϣ��gl_TxFlag = 1:�����͵�����λ�����͸�С������Ϣ
uint8_t gl_RxLen = 0;
uint16_t gl_FreRate = 0; 
uint8_t gl_Store[250] = {1,30,1,2,131,132,5,6,135,136,9,10,0,12,13,142,143,144,17,18,19,20,1,1,1,1,1,1,1,1,1,1};
uint8_t gl_Restore[250] = {0};
uint8_t gl_StartFlag = 0;
uint8_t gl_SlowFlag = 0;
uint8_t gl_ColliFlag = 0;
uint8_t gl_StopFlag = 1; 
uint8_t gl_Right = 1;           //�ұ������ݵ�λ�źţ�
uint8_t gl_Left = 2;            //��������ݵ�λ�ź�
uint8_t gl_posFlag[30]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
uint8_t gl_pos2opr[30]={0};
uint8_t gl_oprDis[21] = {0};
uint8_t gl_DirFlag = FOREWARD;  //FOREWARD:������ת;BACKWARD:���·�ת��
uint8_t gl_DirFlag1 = 1;				//�Ƿ���Ϊ�˷�ֹ���װ����
Car gl_car={0,0,0,0};   
uint8_t gl_car_all= 0;          //С������
uint8_t gl_opr = 0;             //��Ч��λ��
uint8_t gl_pos = 0;
uint8_t gl_motor = 0;           //�������ʹ��
uint8_t gl_car_state = 0;       //С��Ĭ��״̬Ϊ��������ģʽ
volatile uint16_t NumDataRead = 0;


int main(void)
{
	
#if DEBUG == 3	
    for(i = 0;i <256;i++)
    {
        gl_Store[i] = 255-i;
    }
#endif
		
    Sys_InitConfig();
//		Change_PosFlag(gl_Store);

		
		
#if DEBUG == 3	
    NumDataRead=BUFFER_SIZE;
		NumDataRead=1;
    //sEE_ReadBuffer(gl_Restore,sEE_READ_ADDRESS1,(uint16_t* )(&NumDataRead));
		sEE_ReadBuffer(&gl_Restore[0],sEE_READ_ADDRESS1,(uint16_t* )(&NumDataRead));
		sEE_ReadBuffer(&gl_Restore[1],sEE_READ_ADDRESS1+1,(uint16_t* )(&NumDataRead));
    Delay(100);


#endif
		
	
#if     DEBUG == 0
		Led_On(LED4);
		Test();
//        while(1)
//        {
//            Delay_Nms(500);
//            TXD_USART(EVAL_COM2,ch,2);
//        }
		
		
#elif   DEBUG == 1	
    gl_opr = 11;	
    Led_On(LED1);
    while(1)
    {
        Control_Mode1();
    }
#elif   DEBUG == 2

    while(1)
    {
        Led_On(LED4);
        while(EVAL_RXFINISH())
        {
            EVAL_CLEARRX();
            EVAL_RXDATA();
            switch(ch)
            {
                case '1':
                    printf("start\r\n");
                    break;
                case '2':
                    printf("slow down\r\n");
                    break;
                case '3':
                    printf("stop\r\n");
                    break;
            }
							
            if(EFF_VAL_SENSER0()) //reset senser
            {
               gl_car.pos = 0;
            }
             if(EFF_VAL_SENSER2()) //slow_down senser
            {
                gl_car.pos++;
                if(gl_car.pos == 20)
                {
                    gl_car.pos = 0;
                }
                if(gl_posFlag[gl_car.pos])
                {
                    gl_SlowFlag = 1;
                    gl_StartFlag = 0;
                }
            }
            if(EFF_VAL_SENSER3()) //stop senser
            {
                if(gl_posFlag[gl_car.pos] == 1)
                {
										gl_car.opr++;
                    gl_StopFlag = 1;
                    gl_StartFlag = 0;
                    gl_SlowFlag = 0;
                    if(gl_car.opr == 12 )
                    {
                        gl_car.opr = 0;
                    }
										printf("position is in %d\r\n",gl_car.pos);
                    printf("operation is in %d\r\n",gl_car.opr);
										
    
                }
                
            }
            if(EFF_VAL_SENSER1()) //start senser
            {
                if((gl_car.pos <19)||(gl_car.pos == 19 && gl_Right == 1))  //����������δ����19�Ź�λ�����ߵ���19�Ź�λ����������̨�Ѿ�������λ
                {
                    gl_StartFlag = 1;
                    gl_StopFlag = 0;
                    gl_SlowFlag = 0;
                }								
            }
           
        }

    }

#elif DEBUG == 3
    while(1)
    {
        Led_Drive(0x02);
//        if(gl_Restore[0] == 249 && gl_Restore[249] == 0)
//        {
//            if(gl_Restore [35] == 214 && gl_Restore [128] == 121)
//                if(gl_Restore [50] == 199 && gl_Restore [234] == 15)
//                    if(gl_Restore [74] == 175 && gl_Restore [132] == 117)
//                        if(gl_Restore [100] == 149 && gl_Restore [203] == 46)
					if(gl_Restore[0] == 0x55 && gl_Restore[1] == 0xaa )
								Led_Drive(0x03);
    }
#elif DEBUG == 6
		Led_On(LED1);
		Delay(100);
		Led_Off(LED1);
		Rx_Enable();
		while(1)
		{
			if(gl_RxRight == 1)
			{
				gl_RxRight = 0;
				gl_zhongduan_test = 0;
				Led_Toggle(LED1);
			}
		}

#else
        hardware_detect();
        LCD_Set();
				Normal_Mode();
//			while(1)
//			{
//				if(NONEFF_MSRDY() || EFF_MALRM())
//				{
//					printf("hello world");
//					SET_VAL_MSON();         //�ŷ�����
//					RST_VAL_MARST();
//					Delay_Nms(500);
//					SET_VAL_MARST(); 
//					Delay_Nms(500);   //��֤�������ʹ��
//					RST_VAL_MSON();   //�ŷ�ʹ��
//					Delay_Nms(500);   //��֤�������ʹ��
//				}
//				
//			}


#endif
}
 





#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
//		Led_On(LED2);
		printf("Wrong parameters value: file %s on line %d\r\n", file, line);
//		Led_On(LED1);
  }
}
#endif
