#ifndef __LCD_KEY_H
#define __LCD_KEY_H



#ifdef __cplusplus
 extern "C" {
#endif
	 
	 
#include  "include.h"
	 
#define Up        		1
#define Down 					2
#define Esc        		3
#define Enter					4
#define Reset     		5 
	 
#define  LINE1              0
#define  LINE2              1
#define  LINE1_HEAD         0x80
#define  LINE2_HEAD         0xC0
#define  DATA_MODE          0x38
#define  OPEN_SCREEN        0x0C
#define  MODE_SELECT        0x06
#define  DISPLAY_ADDRESS    0x80
#define  CLEARSCREEN()      LCD_En_Command(0x01)


/**********************
* Ŀ¼�ṹ�嶨�� *
**********************/
struct MenuItem
{
    unsigned char MenuCount;    //��ǰ��ڵ���
    unsigned char *DisplayString; //�˵�����
    void (*Subs)();      //�ڵ㺯��
    struct MenuItem *ChildrenMenus; //�ӽڵ�
    struct MenuItem *ParentMenus; //���ڵ�
};








/***********************
*��ʾ������ *
***********************/
#define Null 0
/***********************
* �������� *
***********************/
static void ShowMenu(void);
static void Menu_Change(uint8_t  KeyNum);

//��������������-����Ϊ����,�����ʵ������޸ġ�����������������
extern struct MenuItem Paraset[8];
extern struct MenuItem FlashMenu[5];
extern struct MenuItem VoiceMenu[5];
extern struct MenuItem RobotMenu[5];
extern struct MenuItem MainMenu[5];



/***********************
* �����Ӻ����� *
***********************/
static void NullSubs(void);
//**********************����Ϊ����,�����ʵ������޸�********************/
static void Carnum_Set(void);
static void Pos_Set(void);
static void Speed1_Set(void);
static void Speed2_Set(void);
static void SpeedUp_Set(void);
static void SlowDown_Set(void);
	 
static void LCD_En_Command(uint8_t command);//write command function
static void LCD_En_Data(uint8_t  temp);//write data function
static void LCD_Set_Pos(uint8_t x, uint8_t y );//set display address function
static void LCD_Write_Char(uint16_t x,uint8_t y,uint8_t data);//write lcd a character function
static void LCD_Write_String(uint8_t X,uint8_t Y,uint8_t *s);//write lcd string function
static void LCD_Init(void);//lcd initize function
static void LCD_Data(uint8_t data);//ʹD0-D7�ĵ�ƽ��data����һ��	 


static void Parameter_Set(void);
static uint8_t Key_Scan(uint8_t *KeyNum);
extern void LCD_Set(void);
	 
#ifdef __cplusplus
}
#endif

#endif
