/*
 * pcf8576c.h
 *
 *  Created on: 2022年4月21日
 *      Author: mastergong
 */
#ifndef DISPLAY_PCF8576C_H_
#define DISPLAY_PCF8576C_H_

#include "disp_iic.h"

#define LCD_ADDR  0x70               //I2C地址
//#define LCD_ADDR  0x72


#define LCD_WRITE_CMD(addr,dat)      display_iic_set(addr,dat)
#define LCD_WRITE(addr,cmd,dat,len)  display_iic_write_data(addr, cmd, dat, len)

/********* 指令集 ************/
#define LCD_NEXT_CMD             0x80  //单次传输中下一字节是指令
#define LCD_Set_Mode             0x40  //设置显示模式
#define LCD_Set_Mode_PS          0x10  //省电模式（外部时钟）
#define LCD_Set_Mode_E           0x08  //显示开关
#define LCD_Set_Mode_B           0x04  //偏压比选择                   0:1/3    1:1/2
#define LCD_Set_Mode_M1          0x02  //驱动时序选择
#define LCD_Set_Mode_M0          0x01  //驱动时序选择
#define LCD_Set_DDRAM_ADDR       0x00  //设置显存数据指针
#define LCD_Select_Frame_Rate    0x68  //扫描频率选择
#define LCD_Frame_Rate_64Hz      0x00
#define LCD_Frame_Rate_82Hz      0x01
#define LCD_Frame_Rate_110Hz     0x02
#define LCD_Frame_Rate_200Hz     0x03
#define LCD_Frame_Rate_MS        0x04
#define LCD_Select_Device        0x60  //设备地址选择     范围(0,7)
#define LCD_Select_RAM_IO        0x78
#define LCD_Select_Blink         0x70



extern void lcd_pcf8576_init(void);
extern void lcd_pcf8576_off(void);
extern void lcd_pcf8576_on(void);


#endif/* DISPLAY_PCF8576C_H_ */