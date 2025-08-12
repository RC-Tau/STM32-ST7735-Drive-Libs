#include "main.h"
#include "LCD_Init.h"


/**
 * @brief  LCD串行数据写入函数
 * @param   dat  要写入的串行数据
 * @return  none
 */
void LCD_Writ_Bus(u8 dat)
{
    u8 i;
    LCD_CS_Clr();
    for(i=0;i<8;i++)
    {
        LCD_SCLK_Clr();
        if(dat&0x80)
        {
            LCD_MOSI_Set();
        }
        else
        {
            LCD_MOSI_Clr();
        }
        LCD_SCLK_Set();
        dat<<=1;
    }
    LCD_CS_Set();
}


/**
 * @brief  LCD写入一个字节数据
 * @param   dat  写入的数据
 * @return  none
 */
void LCD_WR_DATA8(u8 dat)
{
    LCD_Writ_Bus(dat);
}


/**
 * @brief  LCD写入两个字节数据
 * @param   dat  写入的数据
 * @return  none
 */
void LCD_WR_DATA16(u16 dat)
{
    LCD_Writ_Bus(dat>>8);
    LCD_Writ_Bus(dat);
}


/**
 * @brief  LCD写入命令
 * @param   dat  写入的命令
 * @return  none
 */
void LCD_WR_REG(u8 dat)
{
    LCD_DC_Clr();//写命令
    LCD_Writ_Bus(dat);
    LCD_DC_Set();//写数据
}


/**
 * @brief  设置起点和终点坐标
 * @param   x1,y1 设置起点坐标
 * @param   x2,y2 设置终点坐标
 * @return  none
 */
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
    if(USE_HORIZONTAL==0)
    {
        LCD_WR_REG(0x2a);//列地址设置
        LCD_WR_DATA16(x1);
        LCD_WR_DATA16(x2);
        LCD_WR_REG(0x2b);//行地址设置
        LCD_WR_DATA16(y1);
        LCD_WR_DATA16(y2);
        LCD_WR_REG(0x2c);//储存器写
    }
    else if(USE_HORIZONTAL==1)
    {
        LCD_WR_REG(0x2a);//列地址设置
        LCD_WR_DATA16(x1);
        LCD_WR_DATA16(x2);
        LCD_WR_REG(0x2b);//行地址设置
        LCD_WR_DATA16(y1);
        LCD_WR_DATA16(y2);
        LCD_WR_REG(0x2c);//储存器写
    }
    else if(USE_HORIZONTAL==2)
    {
        LCD_WR_REG(0x2a);//列地址设置
        LCD_WR_DATA16(x1);
        LCD_WR_DATA16(x2);
        LCD_WR_REG(0x2b);//行地址设置
        LCD_WR_DATA16(y1);
        LCD_WR_DATA16(y2);
        LCD_WR_REG(0x2c);//储存器写
    }
    else
    {
        LCD_WR_REG(0x2a);//列地址设置
        LCD_WR_DATA16(x1);
        LCD_WR_DATA16(x2);
        LCD_WR_REG(0x2b);//行地址设置
        LCD_WR_DATA16(y1);
        LCD_WR_DATA16(y2);
        LCD_WR_REG(0x2c);//储存器写
    }
}


/**
 * @brief  LCD初始化函数
 * @param   none
 * @return  none
 */
void LCD_Init(void)
{

    LCD_RES_Clr();//复位
    HAL_Delay(100);
    LCD_RES_Set();
    HAL_Delay(100);

    LCD_BLK_Set();//打开背光
    HAL_Delay(100);

    //************* Start Initial Sequence **********//
    LCD_WR_REG(0x11); //Sleep out
    HAL_Delay(120);              //Delay 120ms
    //------------------------------------ST7735S Frame Rate-----------------------------------------//
    LCD_WR_REG(0xB1);
    LCD_WR_DATA8(0x05);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x3C);
    LCD_WR_REG(0xB2);
    LCD_WR_DATA8(0x05);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x3C);
    LCD_WR_REG(0xB3);
    LCD_WR_DATA8(0x05);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x05);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x3C);
    //------------------------------------End ST7735S Frame Rate---------------------------------//
    LCD_WR_REG(0xB4); //Dot inversion
    LCD_WR_DATA8(0x03);
    //------------------------------------ST7735S Power Sequence---------------------------------//
    LCD_WR_REG(0xC0);
    LCD_WR_DATA8(0x28);
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x04);
    LCD_WR_REG(0xC1);
    LCD_WR_DATA8(0XC0);
    LCD_WR_REG(0xC2);
    LCD_WR_DATA8(0x0D);
    LCD_WR_DATA8(0x00);
    LCD_WR_REG(0xC3);
    LCD_WR_DATA8(0x8D);
    LCD_WR_DATA8(0x2A);
    LCD_WR_REG(0xC4);
    LCD_WR_DATA8(0x8D);
    LCD_WR_DATA8(0xEE);
    //---------------------------------End ST7735S Power Sequence-------------------------------------//
    LCD_WR_REG(0xC5); //VCOM
    LCD_WR_DATA8(0x1A);
    LCD_WR_REG(0x36); //MX, MY, RGB mode
    if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
    else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
    else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
    else LCD_WR_DATA8(0xA0);
    //------------------------------------ST7735S Gamma Sequence---------------------------------//
    LCD_WR_REG(0xE0);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x22);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x0A);
    LCD_WR_DATA8(0x2E);
    LCD_WR_DATA8(0x30);
    LCD_WR_DATA8(0x25);
    LCD_WR_DATA8(0x2A);
    LCD_WR_DATA8(0x28);
    LCD_WR_DATA8(0x26);
    LCD_WR_DATA8(0x2E);
    LCD_WR_DATA8(0x3A);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x01);
    LCD_WR_DATA8(0x03);
    LCD_WR_DATA8(0x13);
    LCD_WR_REG(0xE1);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x16);
    LCD_WR_DATA8(0x06);
    LCD_WR_DATA8(0x0D);
    LCD_WR_DATA8(0x2D);
    LCD_WR_DATA8(0x26);
    LCD_WR_DATA8(0x23);
    LCD_WR_DATA8(0x27);
    LCD_WR_DATA8(0x27);
    LCD_WR_DATA8(0x25);
    LCD_WR_DATA8(0x2D);
    LCD_WR_DATA8(0x3B);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x01);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x13);
    //------------------------------------End ST7735S Gamma Sequence-----------------------------//
    LCD_WR_REG(0x3A); //65k mode
    LCD_WR_DATA8(0x05);
    LCD_WR_REG(0x29); //Display on
}