
#ifndef LCD_INIT_H
#define LCD_INIT_H

#define  u8  uint8_t
#define  u16 uint16_t

#define USE_HORIZONTAL 3  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏
#define LCD_Picture   1	  //演示图片选择设置:   0,竖屏图片   1,横屏图片


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_w 127
#define LCD_h 159
#else
#define LCD_w 159
#define LCD_h 127
#endif



//-----------------LCD端口定义----------------

#define LCD_SCLK_Clr() HAL_GPIO_WritePin(SCL_GPIO_Port,SCL_Pin,GPIO_PIN_RESET)//SCL
#define LCD_SCLK_Set() HAL_GPIO_WritePin(SCL_GPIO_Port,SCL_Pin,GPIO_PIN_SET)

#define LCD_MOSI_Clr() HAL_GPIO_WritePin(SDA_GPIO_Port,SDA_Pin,GPIO_PIN_RESET)//SDA
#define LCD_MOSI_Set() HAL_GPIO_WritePin(SDA_GPIO_Port,SDA_Pin,GPIO_PIN_SET)

#define LCD_RES_Clr()  HAL_GPIO_WritePin(RES_GPIO_Port,RES_Pin,GPIO_PIN_RESET)//RES
#define LCD_RES_Set()  HAL_GPIO_WritePin(RES_GPIO_Port,RES_Pin,GPIO_PIN_SET)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(AO_GPIO_Port,AO_Pin,GPIO_PIN_RESET)//DC or AO
#define LCD_DC_Set()   HAL_GPIO_WritePin(AO_GPIO_Port,AO_Pin,GPIO_PIN_SET)

#define LCD_CS_Clr()   HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_RESET)//CS
#define LCD_CS_Set()   HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_SET)

#define LCD_BLK_Clr()  HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET)//BLK or LED
#define LCD_BLK_Set()  HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET)



void LCD_Writ_Bus(u8 dat);//模拟SPI时序
void LCD_WR_DATA8(u8 dat);//写入一个字节
void LCD_WR_DATA16(u16 dat);//写入两个字节
void LCD_WR_REG(u8 dat);//写入一个指令
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//设置坐标函数
void LCD_Init(void);//LCD初始化



#endif //LCD_INIT_H
