#include <string.h>
#include "STC8H.h"
#include "my_type.h"
#include "disp_iic.h"
#include "lcd_watch.h"
#include "pcf8576c.h"

/****************变量定义*****************************/
_flag            xdata  ucFlag;                     /* 标志位变量 */



_disp_buff_st xdata dispBuff;

uint16_t xdata  displayCount;
uint16_t xdata  displayNum;

extern void timer1_init(void);
/*******************************************
函数名称：cycle_delay
功    能：10ms周期实现函数
参    数：无
返回值  ：无
********************************************/
static void cycle_delay(void)
{
    while(ucFlag.BIT.CYCLE_FLAG != SET){

    }
    ucFlag.BIT.CYCLE_FLAG = CLR;
}




static void display_handle(void)
{
    uint8_t i;
    displayCount++;
    if(displayCount > 50){ //500ms 切换下一个显示
        displayCount = 0;
    
        displayNum++;  //显示的编号
        if(displayNum > 29){
            displayNum = 0;
        }
    }
		
		
    memset(&dispBuff,0,sizeof(_disp_buff_st));
    //-----显示赋值---
    //如 显示1 =》 dispBuff.grid_data[i] = 1;
    //   显示A =》 dispBuff.grid_data[i] = LED_SIGE_A;
    //   显示E =》 dispBuff.grid_data[i] = LED_SIGE_E;
    //   不显示 =》 dispBuff.grid_data[i] = LED_SIGE_OFF;
    for(i=0;i<18;i++){
        dispBuff.grid_data[i] = displayNum; 
    }
  
		
   
    if(displayNum%2){
        dispBuff.sec_flash = 1;  // == 1   秒冒号显示    
			  dispBuff.iconMonth = 1;    // == 1   月日显示         
        dispBuff.iconFace = 1;     // == 1   笑脸显示
        dispBuff.iconFlower = 1;   // == 1   花显示
        dispBuff.iconStep = 1;     // == 1   步显示
    }else{
        dispBuff.sec_flash = 0;
    }
		
		
		
		
		
		
    //驱动调用
    drive_lcd_09inch(dispBuff);
}

static void all_congfig(void)
{ 

    INTCLKO = 0x40;
    ucFlag.BYTE = 0;
   
    init_display_iic_gpio();  //显示端口初始化

    timer1_init(); //1ms定时基础
    EA = 1;     //打开总中断
}



int main(void)
{     
    all_congfig();

    while(1)
    {   
        //----------10ms循环一次主函数---------------
        cycle_delay();

        display_handle();

   }
}



