/*
 * lcd_watch.c
 *
 *  Created on: 2022年4月21日
 *      Author: mastergong
 */
#include "lcd_watch.h"
#include "pcf8576c.h"


static char xdata dispBuff[20]; //显存
//第1行码表
const char  seg_code_tab1[]={
0x5f,  /* 0:  0 */
0x50,  /* 1:  1 */
0x3d,  /* 2:  2 */
0x79,  /* 3:  3 */
0x72,  /* 4:  4 */
0x6b,  /* 5:  5 */
0x6f,  /* 6:  6 */
0x51,  /* 7:  7 */
0x7f,  /* 8:  8*/
0x7b,  /* 9:  9 */
0x77,  /* 10: A */
0x6e,  /* 11: B */
0x0f,  /* 12: C */
0x7c,  /* 13: d */
0x2f,  /* 14: E */
0x27,  /* 15: F */
0x76,  /* 16: H */
0x0E,  /* 17: L */
0x24,  /* 18: r */
0x37,  /* 19：p */
0x57,  /* 20：N */
0x20,  /* 21: - 中- */
0x01,  /* 22：- 上- */
0x08,  /* 23：_ 下- */
0x33,  /* 24：o 上o */
0x6C,  /* 25：o 下o */
0x5E,  /* 26: U */
0x2C,  /* 27：c */
0x3B,  /* 28：上o 下-*/
0x6D,  /* 29：下o 上-*/
0x00,  /* 30：  */
};
//第2、3行码表
const char code seg_code_tab2[]={
0x5f,  /* 0:  0 */
0x06,  /* 1:  1 */
0x3d,  /* 2:  2 */
0x2f,  /* 3:  3 */
0x66,  /* 4:  4 */
0x6b,  /* 5:  5 */
0x7b,  /* 6:  6 */
0x0e,  /* 7:  7 */
0x7f,  /* 8:  8*/
0x6f,  /* 9:  9 */
0x7e,  /* 10: A */
0x73,  /* 11: B */
0x59,  /* 12: C */
0x37,  /* 13: d */
0x79,  /* 14: E */
0x78,  /* 15: F */
0x76,  /* 16: H */
0x51,  /* 17: L */
0x30,  /* 18: r */
0x7C,  /* 19：p */
0x5E,  /* 20：N */
0x20,  /* 21: - 中- */
0x08,  /* 22：- 上- */
0x01,  /* 23：_ 下- */
0x6C,  /* 24：o 上o */
0x33,  /* 25：o 下o */
0x57,  /* 26: U */
0x31,  /* 27：c */
0x6D,  /* 28：上o 下-*/
0x3B,  /* 29：下o 上-*/
0x00,  /* 30：  */
};

// #define  ICON_MONTH  0//月
// #define  ICON_DAY    1//日
// #define  ICON_FACE   2//笑脸
// #define  ICON_COLON  3//冒号
// #define  ICON_FLOWER 4//小花
// #define  ICON_STEP   5//步
const _icon_tab_st code st_icon_tab[6]={
    {2 , 0x01},  //月
    {0 , 0x10},  //日
    {0 , 0x80},  //笑脸
    {7 , 0x80},  //冒号
    {11, 0x10},  //小花
    {16, 0x01},  //步
};

#define  ICON_DISP_ON(x)   dispBuff[st_icon_tab[x].num]|=st_icon_tab[x].codeSeg
#define  ICON_DISP_OFF(x)  dispBuff[st_icon_tab[x].num]&=~st_icon_tab[x].codeSeg




/*********************************
函数名称：lcd_display_digit
功能：LCD屏幕显示数字
输入：序号，显示数字
输出：无
*********************************/
void lcd_display_digit(unsigned char seg,unsigned char num)
{
    if(seg>14){
        return;
    }
    switch(seg){
        //第一行
        case 0:
        case 1:
            dispBuff[4-seg]&=0x80;
            dispBuff[4-seg]|=seg_code_tab1[num];
            break;
        case 2:
        case 3:
            dispBuff[4-seg]&=0x0f;
            dispBuff[3-seg]&=0xf8;
            dispBuff[4-seg]|=seg_code_tab1[num]<<4;
            dispBuff[3-seg]|=seg_code_tab1[num]>>4;
            break;
        //第二行
        case 4:
        case 5:
        case 6:
        case 7:
        //第三行
        case 8:
        case 9:
            dispBuff[seg+1]&=0x80;
            dispBuff[seg+1]|=seg_code_tab2[num];
            break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            dispBuff[seg+1]&=0xf8;
            dispBuff[seg+2]&=0x0f;
            dispBuff[seg+1]|=seg_code_tab2[num]>>4;
            dispBuff[seg+2]|=seg_code_tab2[num]<<4;
            break;
    }
}

/*********************************
函数名称：lcd_display_refresh
功能：LCD刷新
输入：无
输出：无
*********************************/
static void lcd_display_refresh(void)
{
    LCD_WRITE(LCD_ADDR, 0, dispBuff, 19);//同步显存
}



/*********************************
函数名称：lcd_display_icon_on
功能：LCD图标显示开
输入：图标编号定义
输出：无
*********************************/
static void lcd_display_icon_on(unsigned char icon)
{
    if(icon > 5){
        return;
    }
    ICON_DISP_ON(icon);
}

/*********************************
函数名称：lcd_display_icon_off
功能：LCD图标显示关
输入：图标编号定义
输出：无
*********************************/
static void lcd_display_icon_off(unsigned char icon)
{
    if(icon > 5){
        return;
    }
    ICON_DISP_OFF(icon);
}


//显示接口 
//LCD 0.9寸 液晶屏
void drive_lcd_09inch(_disp_buff_st info)
{
    uint8_t i;

    for(i=0;i<20;i++){
        dispBuff[i] = 0;
    }

    lcd_pcf8576_init();
    
    if(info.off){ //关闭显示
        lcd_pcf8576_off();
    }else{
        lcd_pcf8576_on();
    }

    lcd_display_digit(0, info.grid_data[4]);
    lcd_display_digit(1, info.grid_data[5]);
    lcd_display_digit(2, info.grid_data[6]);
    lcd_display_digit(3, info.grid_data[7]);
    lcd_display_digit(4, info.grid_data[0]);
    lcd_display_digit(5, info.grid_data[1]);
    lcd_display_digit(6, info.grid_data[2]);
    lcd_display_digit(7, info.grid_data[3]);
    lcd_display_digit(8, info.grid_data[8]);
    lcd_display_digit(9, info.grid_data[9]);
    lcd_display_digit(10, info.grid_data[10]);
    lcd_display_digit(11, info.grid_data[11]);
    lcd_display_digit(12, info.grid_data[12]);
    lcd_display_digit(13, info.grid_data[13]);
    lcd_display_digit(14, info.grid_data[14]);

    //-------月日标志-----------
    if(info.iconMonth){
        lcd_display_icon_on(ICON_MONTH);
        lcd_display_icon_on(ICON_DAY);
    }

    //-------笑脸显示-----------
    if(info.iconFace){
        lcd_display_icon_on(ICON_FACE);
    }

    //-------花显示-----------
    if(info.iconFlower){
        lcd_display_icon_on(ICON_FLOWER);
    }

    //-------步显示-----------
    if(info.iconStep){
        lcd_display_icon_on(ICON_STEP);
    }

    //-------冒号显示------------
    if(info.sec_flash){
        lcd_display_icon_on(ICON_COLON);
    }

    lcd_display_refresh();
    
}