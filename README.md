# STM32-ST7735-Drive-Libs
基于STM32（HAL库）模拟SPI的128*160分辨率TFT屏的驱动库
#

调用方法：

1、在STM32CubeMX中使能要使用的GPIO，将每个端口的用户标签对应改成LED/BLK、SCL、SDA/MOSI、AO/DC、RESET、CS。

2、在LCD_Init.h文件中，“在LCD端口定义”处修改宏定义，确保一一对应。同时可以通过修改USE_HORIZONTAL和LCD_Picture的值设置屏幕显示为竖屏或者横屏。

3、最后在main.c文件中，在main函数的while主循环前添加LCD_Init()函数，完成LCD的初始化。

