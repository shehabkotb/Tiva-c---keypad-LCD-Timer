#include "tm4c123gh6pm.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "KeyPad.h"
#include "Port_INIT.h"
#include "Systick_Timer.h"
#include "LCD.h"
#include "Timer.h"

int main()
{
	PORTA_init(); // keypad col PA2-5
	PORTB_init(); // lcd data PB0-7
	PORTC_init(); // lcd EN PC4, RS PC5
	PORTE_init(); // keypad row PE0-4
	PORTF_init(); // sw1, sw2, led

	Configure_SysTick();
	LCD_start();
	
	while(1){
		
		int time = 0;
		int *ptr = &time;
		
		// takes input for timer
		bool start = handleInput(ptr);
		
		// starts timer if sw1 was pressed
		if(start && time != 0){
			timerStart(time);
		}
		SysTick_Wait1ms(300);		
	}
	
  	return 0;
}
