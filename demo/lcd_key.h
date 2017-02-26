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
* 目录结构体定义 *
**********************/
struct MenuItem
{
    unsigned char MenuCount;    //当前层节点数
    unsigned char *DisplayString; //菜单标题
    void (*Subs)();      //节点函数
    struct MenuItem *ChildrenMenus; //子节点
    struct MenuItem *ParentMenus; //父节点
};








/***********************
*显示函数区 *
***********************/
#define Null 0
/***********************
* 函数声明 *
***********************/
static void ShowMenu(void);
static void Menu_Change(uint8_t  KeyNum);

//———————-以下为例子,请根据实际情况修改—————————
extern struct MenuItem Paraset[8];
extern struct MenuItem FlashMenu[5];
extern struct MenuItem VoiceMenu[5];
extern struct MenuItem RobotMenu[5];
extern struct MenuItem MainMenu[5];



/***********************
* 调用子函数区 *
***********************/
static void NullSubs(void);
//**********************以下为例子,请根据实际情况修改********************/
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
static void LCD_Data(uint8_t data);//使D0-D7的电平和data保持一致	 


static void Parameter_Set(void);
static uint8_t Key_Scan(uint8_t *KeyNum);
extern void LCD_Set(void);
	 
#ifdef __cplusplus
}
#endif

#endif
