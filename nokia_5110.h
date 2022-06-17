#include "gd32f3x0.h"
#include "gd32f310g_start.h"


// LCD_GPIO_ PORT
# define LCD_GPIO_PORT GPIOA

// LCD_CLOCK
#define LCD_CLOCK RCU_GPIOA

// RST
#define LCD_RST_GPIO_PORT GPIOA
#define LCD_RST_GPIO_PIN GPIO_PIN_2

// CE
#define LCD_CE_GPIO_PORT GPIOA
#define LCD_CE_GPIO_PIN GPIO_PIN_3

// DC
#define LCD_DC_GPIO_PORT GPIOA
#define LCD_DC_GPIO_PIN GPIO_PIN_4

// DIN
#define LCD_DIN_GPIO_PORT GPIOA
#define LCD_DIN_GPIO_PIN GPIO_PIN_5

// CLK
#define LCD_CLK_GPIO_PORT GPIOA
#define LCD_CLK_GPIO_PIN GPIO_PIN_6


void LCD_init(void);
void LCD_clear(void);
void LCD_move_chinese_string(unsigned char X, unsigned char Y, unsigned char T); 
void LCD_write_english_string(unsigned char X,unsigned char Y,char *s);
void LCD_write_chinese_string(unsigned char X, unsigned char Y,
                   unsigned char ch_with,unsigned char num,
                   unsigned char line,unsigned char row);
void chinese_string(unsigned char X, unsigned char Y, unsigned char T);                 
void LCD_write_char(unsigned char c);
void LCD_draw_bmp_pixel(unsigned char X,unsigned char Y,unsigned char *map,
                  unsigned char Pix_x,unsigned char Pix_y);
void LCD_write_byte(unsigned char dat, unsigned char dc);
void LCD_set_XY(unsigned char X, unsigned char Y);
void delay_1us(void);                 
 