# PCF8576c

手表屏驱动程序
--------------------------------

文件夹《drive》   驱动程序。

文件夹《example》 STC8H1K08芯片的使用例程工程参考。

文件夹《doc》     芯片的用户手册。

![显示图片][1]


功能： 

码表有常规数字和字符显示（0-9，ABCDdEFHLrPN-_oU）。


驱动说明：

《disp_i2c》 文件夹为模拟IIC实现，可在 disp_iic.h 文件中修改对应的引脚初始化，另不同的芯片要调整延迟函数。




注：本示例程序只针对特定手表屏使用。

适用见：https://gongqijunhui.taobao.com/category-1663332070.htm?spm=a1z10.5-c-s.w4010-22753595293.9.122a7a1cfOQ5dy&search=y&catName=%CF%D4%CA%BE%C4%A3%D7%E9#bd

 [1]: https://github.com/master-gong/PCF8576c/blob/main/example/Video_20220623_032849_743.gif
