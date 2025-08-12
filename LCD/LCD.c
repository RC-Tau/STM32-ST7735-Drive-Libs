#include "main.h"
#include "LCD.h"
#include "LCD_Init.h"
#include "LCD_Font.h"
#include "LCD_Pictures.h"


/**
 * @brief  在指定区域填充颜色，竖屏坐标范围为(0,0)到(127,159)，横屏坐标范围为(0,0)到(159,127)
 * @param   x1,y1  起点坐标
 * @param   x2,y2  终点坐标
 * @param   color  要填充的颜色
 * @return  none
 */
void LCD_Fill(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
    u16 i,j;
    LCD_Address_Set(x1,y1,x2,y2);
    for(i = y1; i <= y2; i++)
    {
        for(j = x1; j <= x2; j++)
        {
            LCD_WR_DATA16(color);
        }
    }
}


/**
 * @brief  画点函数
 * @param   x,y  点的坐标
 * @param   color 点的颜色
 * @return  none
 */
void LCD_DrawPoint(u16 x,u16 y,u16 color)
{
    LCD_Address_Set(x,y,x,y);
    LCD_WR_DATA16(color);
}


/**
 * @brief  画线函数
 * @param   x1,y1  起点坐标
 * @param   x2,y2  终点坐标
 * @param   color 线的颜色
 * @return  none
 */
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
    int x_err = 0, y_err = 0, delta_x, delta_y, distance;
    int incx,incy,uRow,uCol;

    delta_x = x2 - x1; //计算坐标增量
    delta_y = y2 - y1;
    uRow = x1;//画线起点坐标
    uCol = y1;

    if(delta_x > 0)
        incx = 1; //设置单步方向
    else if (delta_x == 0)
        incx = 0;//垂直线
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }

    if(delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0;//水平线
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }

    if(delta_x > delta_y)
        distance = delta_x; //选取基本增量坐标轴
    else
        distance = delta_y;

    for(int t = 0; t < distance + 1; t++)
    {
        LCD_DrawPoint(uRow,uCol,color);
        x_err += delta_x;
        y_err += delta_y;
        if(x_err > distance)
        {
            x_err -= distance;
            uRow += incx;
        }
        if(y_err > distance)
        {
            y_err -= distance;
            uCol += incy;
        }
    }
}


/**
 * @brief  画矩形函数
 * @param   x1,y1  起点坐标
 * @param   x2,y2  终点坐标
 * @param   color 矩形的颜色
 * @return  none
 */
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
    LCD_DrawLine(x1,y1,x2,y1,color);
    LCD_DrawLine(x1,y1,x1,y2,color);
    LCD_DrawLine(x1,y2,x2,y2,color);
    LCD_DrawLine(x2,y1,x2,y2,color);
}


/**
 * @brief  画圆函数
 * @param   x0,y0  圆心坐标
 * @param   r  半径
 * @param   color 圆的颜色
 * @return  none
 */
void LCD_DrawCircle(u16 x0,u16 y0,u8 r,u16 color)
{
    int a,b;
    a=0;b=r;
    while(a<=b)
    {
        LCD_DrawPoint(x0-b,y0-a,color);             //3
        LCD_DrawPoint(x0+b,y0-a,color);             //0
        LCD_DrawPoint(x0-a,y0+b,color);             //1
        LCD_DrawPoint(x0-a,y0-b,color);             //2
        LCD_DrawPoint(x0+b,y0+a,color);             //4
        LCD_DrawPoint(x0+a,y0-b,color);             //5
        LCD_DrawPoint(x0+a,y0+b,color);             //6
        LCD_DrawPoint(x0-b,y0+a,color);             //7
        a++;
        if((a*a+b*b)>(r*r))//判断要画的点是否过远
        {
            b--;
        }
    }
}


/**
 * @brief  显示单个字符
 * @param   x,y  起点坐标
 * @param   num 要显示的字符
 * @param   font_color 字体颜色
 * @param   back_color 背景颜色
 * @param   size 字体大小，支持12、16、24（可在font字库中自由添加）
 * @param   mode  0: 非叠加模式  1: 叠加模式
 * @return  none
 */
void LCD_ShowChar(u16 x,u16 y,u8 num,u16 font_color,u16 back_color,u8 size,u8 mode)
{
    u8 temp,t1,t;
    u16 y0 = y;
    u8 csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);		//得到字体一个字符对应点阵集所占的字节数
    num = num - ' ';//得到偏移后的值
    for(t = 0; t < csize; t++)
    {
        if(size == 12)
            temp = asc2_1206[num][t]; 	//调用1206字体
        else if(size == 16)
            temp = asc2_1608[num][t];	//调用1608字体
        else if(size == 24)
            temp = asc2_2412[num][t];	//调用2412字体
        else
            return;			     		//没有的字库
        for(t1 = 0; t1 < 8; t1++)
        {
            if(temp & 0x80)
                LCD_DrawPoint(x,y,font_color);
            else if(mode == 0)
                LCD_DrawPoint(x,y,back_color);

            temp <<= 1;
            y++;
            if((y - y0) == size)
            {
                y = y0;
                x++;
                break;
            }
        }
    }
}


/**
 * @brief  显示字符串
 * @param   x,y  起点坐标
 * @param   p  要显示的字符串，最好在字符串前加上(const uint8_t *)，例如 (const uint8_t *) "Hello World"
 * @param   font_color 字体颜色
 * @param   back_color 背景颜色
 * @param   size 汉字大小，支持16、24、32（可在font字库中自由添加）
 * @param   mode  0:非叠加模式  1:叠加模式
 * @return  none
 */
void LCD_ShowString(u16 x,u16 y,const u8 *p,u16 font_color,u16 back_color,u8 size,u8 mode)
{
    while(*p!='\0')
    {
        LCD_ShowChar(x,y,*p,font_color,back_color,size,mode);
        x += size / 2;
        p++;
    }
}


/**
 * @brief   计算幂指数
 * @param   m 底数
 * @param   n 指数
 * @return  m的n次方
 */
u32 mypow(u8 m,u8 n)
{
    u32 result = 1;
    while(n--)
        result *= m;
    return result;
}


/**
 * @brief   显示整数变量
 * @param   x,y 起点坐标
 * @param   num 要显示整数变量
 * @param   len 要显示的位数
 * @param   font_color 字体颜色
 * @param   back_color 背景颜色
 * @param   size 汉字大小，支持12、16、24（可在font字库中自由添加）
 * @return  none
 */
void LCD_ShowIntNum(u16 x,u16 y,u16 num,u8 len,u16 font_color,u16 back_color,u8 size)
{
    u8 t,temp;
    u8 enshow = 0;
    u8 sizex = size / 2;
    for(t = 0; t < len; t++)
    {
        temp = (num / mypow(10,len - t - 1)) % 10;
        if(enshow == 0 && t < (len - 1))
        {
            if(temp == 0)
            {
                LCD_ShowChar(x + t * sizex,y,' ',font_color,back_color,size,0);
                continue;
            }
            else
                enshow = 1;

        }
        LCD_ShowChar(x + t * sizex,y,temp + 48,font_color,back_color,size,0);
    }
}


/**
 * @brief   显示两位小数变量
 * @param   x,y 起点坐标
 * @param   num 要显示小数变量
 * @param   len 要显示的位数
 * @param   font_color 字体颜色
 * @param   back_color 背景颜色
 * @param   size 汉字大小，支持12、16、24（可在font字库中自由添加）
 * @return  none
 */
void LCD_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u16 font_color,u16 back_color,u8 size)
{
    u8 t,temp,sizex;
    u16 num1;
    sizex = size / 2;
    num1 = (u16)num * 100;
    for(t = 0; t < len; t++)
    {
        temp = (num1 / mypow(10,len-t-1) ) % 10;
        if(t == (len - 2) )
        {
            LCD_ShowChar(x+(len-2)*sizex,y,'.',font_color,back_color,size,0);
            t++;
            len += 1;
        }
        LCD_ShowChar(x + t * sizex,y,temp + 48,font_color,back_color,size,0);
    }
}


/**
 * @brief   显示汉字
 * @param   x,y    起点坐标
 * @param   ch 汉字编号
 * @param   font_color 字体颜色
 * @param   back_color 背景颜色
 * @param   font_size 汉字大小，支持16、24（可在font字库中自由添加）
 * @return  none
 */
void LCD_ShowChinese(u16 x, u16 y, char ch, u16 font_color, u16 back_color, u8 font_size)
{
    u16 i, j;
    u16 x_pos, y_pos, size, font_width, font_height;
    u8 *font_ptr;
    u8 bit_width, temp;

    //检查是否越界
    if((x > (LCD_w - font_size)) || (y > (LCD_h - font_size)))
    {
        return;
    }

    x_pos = x;
    y_pos = y;
    font_height = font_size;
    font_width = font_size;
    bit_width = 8;

    size = (font_width / 8 + ((font_width % 8) ? 1 : 0)) * font_height;

    switch(font_size)
    {
        case 16: font_ptr = (uint8_t*)&Chinese_16word[ch]; break;
        case 24: font_ptr = (uint8_t*)&Chinese_24word[ch]; break;
        //case 32: font_ptr = (uint8_t*)&Chinese_32word[ch]; break;
        default : break;
    }

    for (i = 0; i < size; i++)
    {
        temp = *(font_ptr + i);
        for (j = 0; j < bit_width; j++)
        {
            if(temp & 0x80)
            {
                LCD_DrawPoint(x_pos, y_pos, font_color);
            }
            else
            {
                LCD_DrawPoint(x_pos, y_pos, back_color);
            }
            temp <<= 1;
            x_pos++;
        }
        if (x_pos >= (x + font_width))
        {
            y_pos++;
            x_pos = x;
        }
    }
}



/**
 * @brief   显示图片
 * @param   x1,y1    起点坐标
 * @param   x2,y2    终点坐标
 * @return  none
 */
void LCD_ShowPicture(u16 x1,u16 y1,u16 x2,u16 y2)
{
    u32 i,j,k=0;
    u16 picH,picL;

    LCD_Address_Set(x1,y1,x2,y2);
    for(i = 0; i < LCD_w; i++)
    {
        for (j = 0; j < LCD_h; j++)
        {
            picH = gImage_LCD180[k++];
            picL = gImage_LCD180[k++];

            LCD_WR_DATA8(picH);  //写8位显示数据
            LCD_WR_DATA8(picL);

        }
    }

}