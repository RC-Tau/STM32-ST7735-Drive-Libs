
#ifndef LCD_INIT_H
#define LCD_INIT_H

#define  u8  uint8_t
#define  u16 uint16_t

#define USE_HORIZONTAL 3  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����
#define LCD_Picture   1	  //��ʾͼƬѡ������:   0,����ͼƬ   1,����ͼƬ


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_w 127
#define LCD_h 159
#else
#define LCD_w 159
#define LCD_h 127
#endif



//-----------------LCD�˿ڶ���----------------

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



void LCD_Writ_Bus(u8 dat);//ģ��SPIʱ��
void LCD_WR_DATA8(u8 dat);//д��һ���ֽ�
void LCD_WR_DATA16(u16 dat);//д�������ֽ�
void LCD_WR_REG(u8 dat);//д��һ��ָ��
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��



#endif //LCD_INIT_H
