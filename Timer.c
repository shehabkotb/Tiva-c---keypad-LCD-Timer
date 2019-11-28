#include "tm4c123gh6pm.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "KeyPad.h"
#include "Systick_Timer.h"
#include "LCD.h"

// blink red led for 5 sec
void BlinkLed (void){
	for(int i = 0; i < 10; ++i) {
    	GPIO_PORTF_DATA_R ^= 0x2;
		SysTick_Wait1ms(500);
    }
}

/* takes input for timer
 *
 * return true if timer was started, false if aborted
 * input: int ptr to retrun the entered timer value
 */
bool handleInput(int* time){
	
	char x;
	unsigned int sw1; 
	unsigned int sw2;
	// string to display entered value on lcd
	char LCDNumber[10] = {'\0'};
	
	for(int i = 0; i < 4; ++i) {
		
		// loop till a number is pressed
		do{
			x = getPress();
			sw1 = GPIO_PORTF_DATA_R & 0x10;
			sw2 = GPIO_PORTF_DATA_R & 0x01;
			
			// start timer
			if(!sw1)
				return true;
			// abort
			else if(!sw2) {
				LCD_clear();
				return false;
			}
			
		}while(x < '0' || x > '9');
		
		LCD_clear();
		size_t len = strlen(LCDNumber);
		
		// append the entered number to LCDNumber
		LCDNumber[len] = x;
		
		// display the all the values entered til now 
		LCD_String(LCDNumber);
		LCD_String(".00");
		
		// update the *time
		int a = ((*time) * 10);
		int b = atoi(&x);
		*time = a + b;	
		SysTick_Wait1ms(400);
		
	}
	
	// busy wait till one of the buttons on board is pressed
	while(1){ 									
		sw1 = GPIO_PORTF_DATA_R & 0x10;
		sw2 = GPIO_PORTF_DATA_R & 0x01;
		if(!sw1)
			return true;
		else if(!sw2) {
			LCD_clear();
			return false;
		}
	}
}

/*
 * start the timer
 *
 * input time to be counted down from
 */

void timerStart(int time){
	unsigned int sw2;
	for(int i = time - 1; i >= 0; i--){
		int msec = 99;	
		while(msec >= 0) {
			// string to be displayed on LCD
			char buffer[10];
			// convert i & put it in buffer string
			itoa(i, buffer);
			strcat(buffer, ".");
			char msec_str[4];
			itoa(msec, msec_str);
			if(msec < 10){
				// if msec < 10 pad zero .9 -> .09
				strcat(buffer, "0");
			}
			strcat(buffer, msec_str);
			LCD_clear();
			LCD_String(buffer);
			msec--;
			sw2 = GPIO_PORTF_DATA_R & 0x01;
			if(!sw2){
				LCD_clear();	
				return;
			}
			// 9ms since displaying on lcd takes 1ms
			SysTick_Wait1ms(9);
		}	
	}
	LCD_clear();
	LCD_String("end");
	BlinkLed();
}