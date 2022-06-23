/*
 * pcf8576c.c
 *
 *  Created on: 2022年4月21日
 *      Author: mastergong
 */



#include "pcf8576c.h"



/*********************************
函数名称：lcd_pcf8576_on
功能：LCD开启显示
输入：无
输出：无
备注：
*********************************/
void lcd_pcf8576_on(void)
{
    LCD_WRITE_CMD(LCD_ADDR, LCD_Set_Mode|LCD_Set_Mode_E|LCD_NEXT_CMD);
}

/*********************************
函数名称：lcd_pcf8576_off
功能：LCD关闭显示
输入：无
输出：无
备注：
*********************************/
void lcd_pcf8576_off(void)
{
    LCD_WRITE_CMD(LCD_ADDR, LCD_Set_Mode|LCD_NEXT_CMD);
}

/*********************************
函数名称：pcf8576_init
功能：LCD初始化
输入：无
输出：无
备注：
*********************************/
void lcd_pcf8576_init(void)
{

        LCD_WRITE_CMD(LCD_ADDR, LCD_Select_Device|0|LCD_NEXT_CMD);         //选择设备地址
        LCD_WRITE_CMD(LCD_ADDR, LCD_Set_Mode|LCD_Set_Mode_E|LCD_NEXT_CMD); //设置模式
}



