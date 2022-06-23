/*
 * lcd_watch.h
 *
 *  Created on: 2022年4月21日
 *      Author: mastergong
 */
#ifndef DISPLAY_LCD_WATCH_H_
#define DISPLAY_LCD_WATCH_H_

#include "STC8H.h"
#include "my_type.h"
#include "disp_iic.h"




// 45 月 67日  笑脸
// 01:23
// 89 花 10 11 12 13 14 步

//图标编号定义
#define  ICON_MONTH  0//月
#define  ICON_DAY    1//日
#define  ICON_FACE   2//笑脸
#define  ICON_COLON  3//冒号
#define  ICON_FLOWER 4//小花
#define  ICON_STEP   5//步

//图标码表结构体
typedef struct{
   unsigned char num;  //编号
   unsigned char codeSeg; //码表
}_icon_tab_st;       


#define LCD_SIGE_A     10
#define LCD_SIGE_B     11
#define LCD_SIGE_C     12
#define LCD_SIGE_d     13
#define LCD_SIGE_E     14
#define LCD_SIGE_F     15
#define LCD_SIGE_H     16
#define LCD_SIGE_L     17
#define LCD_SIGE_r     18
#define LCD_SIGE_P     19
#define LCD_SIGE_N     20
#define LCD_SIGE_M_    21
#define LCD_SIGE_U_    22
#define LCD_SIGE_D_    23
#define LCD_SIGE_Uo    24
#define LCD_SIGE_Do    25
#define LCD_SIGE_OFF   30
#define LCD_SIGE_U     26
#define LCD_SIGE_S     5
#define LCD_SIGE_Z     28
#define LCD_SIGE_Y     29

typedef struct {
    char         grid_data[18]; // 显示
    char         sec_flash;    // == 1   秒 冒号点亮   
    char         off;          // == 1   关闭显示               
    char         iconMonth;    // == 1   月日显示         
    char         iconFace;     // == 1   笑脸显示
    char         iconFlower;   // == 1   花显示
    char         iconStep;     // == 1   步显示
}_disp_buff_st;

extern void drive_lcd_09inch(_disp_buff_st info);


#endif/* DISPLAY_LCD_WATCH_H_ */