#include "nokia_5110.h"
#include "english_6x8_pixel.h"
#include "write_chinese_string_pixel.h"
#include "systick.h"



/*-----------------------------------------------------------------------
LCD_init          : 3310LCD��ʼ��

��д����          ��2004-8-10 
����޸�����      ��2004-8-10 
-----------------------------------------------------------------------*/

#define LCD_CE_H gpio_bit_set(LCD_CE_GPIO_PORT, LCD_CE_GPIO_PIN);
#define LCD_CE_L gpio_bit_reset(LCD_CE_GPIO_PORT, LCD_CE_GPIO_PIN);

#define LCD_RST_H gpio_bit_set(LCD_RST_GPIO_PORT, LCD_RST_GPIO_PIN);
#define LCD_RST_L gpio_bit_reset(LCD_RST_GPIO_PORT, LCD_RST_GPIO_PIN);


#define LCD_DC_H gpio_bit_set(LCD_DC_GPIO_PORT, LCD_DC_GPIO_PIN);
#define LCD_DC_L gpio_bit_reset(LCD_DC_GPIO_PORT, LCD_DC_GPIO_PIN);


#define LCD_DIN_H gpio_bit_set(LCD_DIN_GPIO_PORT, LCD_DIN_GPIO_PIN);
#define LCD_DIN_L gpio_bit_reset(LCD_DIN_GPIO_PORT, LCD_DIN_GPIO_PIN);


#define LCD_CLK_H gpio_bit_set(LCD_CLK_GPIO_PORT, LCD_CLK_GPIO_PIN);
#define LCD_CLK_L gpio_bit_reset(LCD_CLK_GPIO_PORT, LCD_CLK_GPIO_PIN);

void delay_1us(void)                 //1us��ʱ����
  {
   unsigned int i;
  for(i=0;i<5000;i++);
  }


void delay_nms(unsigned int n)       //N ms��ʱ����
  {
   unsigned int i=0;
   for (i=0;i<n;i++)
   delay_1ms(1);
  }

void LCD_GPIO_INIT(void) {

      /* enable the LCD clock */
    rcu_periph_clock_enable(LCD_CLOCK);

    // RST
    gpio_mode_set(LCD_RST_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LCD_RST_GPIO_PIN);
    gpio_output_options_set(LCD_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_RST_GPIO_PIN);

    GPIO_BC(LCD_RST_GPIO_PORT) = LCD_RST_GPIO_PIN;

    // CE
    gpio_mode_set(LCD_CE_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LCD_CE_GPIO_PIN);
    gpio_output_options_set(LCD_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_CE_GPIO_PIN);

    GPIO_BC(LCD_CE_GPIO_PORT) = LCD_CE_GPIO_PIN;

    // DC
    gpio_mode_set(LCD_DC_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LCD_DC_GPIO_PIN);
    gpio_output_options_set(LCD_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_DC_GPIO_PIN);

    GPIO_BC(LCD_DC_GPIO_PORT) = LCD_DC_GPIO_PIN;

    // DIN
    gpio_mode_set(LCD_DIN_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LCD_DIN_GPIO_PIN);
    gpio_output_options_set(LCD_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_DIN_GPIO_PIN);

    GPIO_BC(LCD_DIN_GPIO_PORT) = LCD_DIN_GPIO_PIN;

    // CLK
    gpio_mode_set(LCD_CLK_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LCD_CLK_GPIO_PIN);
    gpio_output_options_set(LCD_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_CLK_GPIO_PIN);

    GPIO_BC(LCD_CLK_GPIO_PORT) = LCD_CLK_GPIO_PIN;

}


void LCD_init(void)
  {
    
    LCD_GPIO_INIT();

            // ����һ����LCD��λ�ĵ͵�ƽ����
   LCD_RST_L
    delay_1us();

   LCD_RST_H
    
		// �ر�LCD
   LCD_CE_L
    delay_1us();
		// ʹ��LCD
   LCD_CE_H
    delay_1us();

    LCD_write_byte(0x21, 0);	// ʹ����չ��������LCDģʽ
    LCD_write_byte(0xa0, 0);	// ����ƫ�õ�ѹ
    LCD_write_byte(0x07, 0);	// �¶�У��
    LCD_write_byte(0x17, 0);	// 1:48
    LCD_write_byte(0x20, 0);	// ʹ�û�������
    LCD_clear();	        // ����
    LCD_write_byte(0x0c, 0);	// �趨��ʾģʽ��������ʾ
        
           // �ر�LCD
   LCD_CE_L
  }

/*-----------------------------------------------------------------------
LCD_clear         : LCD��������

��д����          ��2004-8-10 
����޸�����      ��2004-8-10 
-----------------------------------------------------------------------*/
void LCD_clear(void)
  {
    unsigned int i;

    LCD_write_byte(0x0c, 0);			
    LCD_write_byte(0x80, 0);			

    for (i=0; i<504; i++)
      LCD_write_byte(0, 1);			
  }

/*-----------------------------------------------------------------------
LCD_set_XY        : ����LCD���꺯��

���������X       ��0��83
          Y       ��0��5

��д����          ��2004-8-10 
����޸�����      ��2004-8-10 
-----------------------------------------------------------------------*/
void LCD_set_XY(unsigned char X, unsigned char Y)
  {
    LCD_write_byte(0x40 | Y, 0);		// column
    LCD_write_byte(0x80 | X, 0);          	// row
  }

/*-----------------------------------------------------------------------
LCD_write_char    : ��ʾӢ���ַ�

���������c       ����ʾ���ַ���

��д����          ��2004-8-10 
����޸�����      ��2004-8-10 
-----------------------------------------------------------------------*/
void LCD_write_char(unsigned char c)
  {
    unsigned char line;

    c -= 32;

    for (line=0; line<6; line++)
      LCD_write_byte(font6x8[c][line], 1);
  }

/*-----------------------------------------------------------------------
LCD_write_english_String  : Ӣ���ַ�����ʾ����

���������*s      ��Ӣ���ַ���ָ�룻
          X��Y    : ��ʾ�ַ�����λ��,x 0-83 ,y 0-5

��д����          ��2004-8-10 
����޸�����      ��2004-8-10 		
-----------------------------------------------------------------------*/
void LCD_write_english_string(unsigned char X,unsigned char Y,char *s)
  {
    LCD_set_XY(X,Y);
    while (*s) 
      {
	 LCD_write_char(*s);
	 s++;
      }
  }
/*-----------------------------------------------------------------------
LCD_write_chinese_string: ��LCD����ʾ����

���������X��Y    ����ʾ���ֵ���ʼX��Y���ꣻ
          ch_with �����ֵ���Ŀ���
          num     ����ʾ���ֵĸ�����  
          line    �����ֵ��������е���ʼ����
          row     ��������ʾ���м��
��д����          ��2004-8-11 
����޸�����      ��2004-8-12 
���ԣ�
	LCD_write_chi(0,0,12,7,0,0);
	LCD_write_chi(0,2,12,7,0,0);
	LCD_write_chi(0,4,12,7,0,0);	
-----------------------------------------------------------------------*/                        
void LCD_write_chinese_string(unsigned char X, unsigned char Y, 
                   unsigned char ch_with,unsigned char num,
                   unsigned char line,unsigned char row)
  {
    unsigned char i,n;
    
    LCD_set_XY(X,Y);                             //���ó�ʼλ��
    
    for (i=0;i<num;)
      {
      	for (n=0; n<ch_with*2; n++)              //дһ������
      	  { 
      	    if (n==ch_with)                      //д���ֵ��°벿��
      	      {
      	        if (i==0) LCD_set_XY(X,Y+1);
      	        else
      	           LCD_set_XY((X+(ch_with+row)*i),Y+1);
              }
      	    LCD_write_byte(write_chinese[line+i][n],1);
      	  }
      	i++;
      	LCD_set_XY((X+(ch_with+row)*i),Y);
      }
  }
  


/*-----------------------------------------------------------------------
LCD_draw_map      : λͼ���ƺ���

���������X��Y    ��λͼ���Ƶ���ʼX��Y���ꣻ
          *map    ��λͼ�������ݣ�
          Pix_x   ��λͼ���أ�����
          Pix_y   ��λͼ���أ�����

��д����          ��2004-8-13
����޸�����      ��2004-8-13 
-----------------------------------------------------------------------*/
void LCD_draw_bmp_pixel(unsigned char X,unsigned char Y,unsigned char *map,
                  unsigned char Pix_x,unsigned char Pix_y)
  {
    unsigned int i,n;
    unsigned char row;
    
    if (Pix_y%8==0) row=Pix_y/8;      //����λͼ��ռ����
      else
        row=Pix_y/8+1;
    
    for (n=0;n<row;n++)
      {
      	LCD_set_XY(X,Y);
        for(i=0; i<Pix_x; i++)
          {
            LCD_write_byte(map[i+n*Pix_x], 1);
          }
        Y++;                         //����
      }      
  }

/*-----------------------------------------------------------------------
LCD_write_byte    : ʹ��SPI�ӿ�д���ݵ�LCD

���������data    ��д������ݣ�
          command ��д����/����ѡ��

��д����          ��2004-8-10 
����޸�����      ��2004-8-13 
-----------------------------------------------------------------------*/
void LCD_write_byte(unsigned char dat, unsigned char command)
  {
    unsigned char i;
    //PORTB &= ~LCD_CE ;		        // ʹ��LCD
    LCD_CE_L
    if (command == 0)
     // PORTB &= ~LCD_DC ;	        // ��������
     LCD_DC_L
    else
     // PORTB |= LCD_DC ;		        // ��������
     LCD_DC_H
		for(i=0;i<8;i++)
		{
			if(dat&0x80)
				LCD_DIN_H
			else
				LCD_DIN_L
			LCD_CLK_L
			dat = dat << 1;
			LCD_CLK_H
		}
   // SPDR = data;			// �������ݵ�SPI�Ĵ���

    //while ((SPSR & 0x80) == 0);         // �ȴ����ݴ������
	
    //PORTB |= LCD_CE ;			// �ر�LCD
     LCD_CE_H
  }


