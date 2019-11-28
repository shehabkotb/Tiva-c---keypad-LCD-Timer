#include "tm4c123gh6pm.h"
#include "Systick_Timer.h"

//b port data
//c port ctrl
#define LCD_DATA_DATA (GPIO_PORTB_DATA_R)
#define LCD_CTRL_DATA (GPIO_PORTC_DATA_R)
#define EN (1U << 4) //PC4
#define RS (1U << 5) //PC5

void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_start(void);
void LCD_clear(void);
void LCD_home(void);
void LCD_Sentence(char* c[]);
void LCD_String(char c[]);
void itoa(int n, char s[]);