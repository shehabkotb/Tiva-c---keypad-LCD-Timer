#include "LCD.h"
#include "String.h"

void LCD_command(unsigned char command)
{
    LCD_CTRL_DATA = 0;     	/* RS = 0, R/W = 0 */
    LCD_DATA_DATA = command;
    LCD_CTRL_DATA = EN;    	/* pulse E */
    SysTick_Wait1us(1);		/* Enable pulse Width */
    LCD_CTRL_DATA = 0;
	if(command < 4) 
		SysTick_Wait1ms(2);
	else
		SysTick_Wait1us(40);	
	
}


void LCD_data(unsigned char data)
{
    LCD_CTRL_DATA = RS;    /* RS = 1, R/W = 0 */
    LCD_DATA_DATA = data;
    LCD_CTRL_DATA = EN | RS;   /* pulse E */
    SysTick_Wait1us(1);
    LCD_CTRL_DATA = 0;
    SysTick_Wait1us(40);

}

void LCD_start() {
    SysTick_Wait1ms(20); /* initialization sequence */// Wait >15 ms after power is applied
    LCD_command(0x30);		// command 0x30 = Wake up
    SysTick_Wait1ms(5);
    LCD_command(0x30);		// command 0x30 = Wake up #2
    SysTick_Wait1us(100);
    LCD_command(0x30);		// command 0x30 = Wake up #3
    SysTick_Wait1us(100);
  // Prepare LCD Operation and Function  
    LCD_command(0x38);      /* set 8-bit data, 2-line, 5x7 font */
    LCD_command(0x06);      /* move cursor right */
    LCD_command(0x01);      /* clear screen, move cursor to home */
    LCD_command(0x0F);
}
void LCD_clear(void)
{
	LCD_command(0x1);
}

void LCD_String(char c[]){
	for(int i = 0; i < strlen(c); i++){
		LCD_data(c[i]);
	}
}

void LCD_Sentence(char* c[]){
	for(int i = 0; i < sizeof(c); i++){
		LCD_String(c[i]);
	}
}

//reverses a string
void reverse(char s[]) {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}

// convert from integer to c string
void itoa(int n, char s[]) {
     int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }