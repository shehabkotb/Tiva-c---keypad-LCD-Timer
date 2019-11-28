#include "tm4c123gh6pm.h"
#include "KeyPad.h"


const unsigned char keymap[4][4] = {
        { '1', '2', '3', 'A'},
        { '4', '5', '6', 'B'},
        { '7', '8', '9', 'C'},
        { 'E', '0', 'F', 'D'},
};


bool AnyPressed(unsigned int keys){
	
	if( !(keys == 0x3c) ){
		return true;
	}
	else
		return false;
}

unsigned char getPressedChar(unsigned int keys) {
	for(int i=0;i < 4; i++) {
		GPIO_PORTE_DATA_R |= 0x0f; 						// pull rows high
		GPIO_PORTE_DATA_R &= ~(1U << i); 				//ground a single row
		unsigned int test = (GPIO_PORTA_DATA_R & 0x3c);
		if( AnyPressed(test) ){						   // if button is in this row			
			return detectChar(test, i);
		}
	}
	return '\0';
}

unsigned char detectChar(unsigned int keys, int row) {
	for(int j = 0;j < 4;j++) {				   // loop on columns
		keys = GPIO_PORTA_DATA_R & (1U << (2 + j)); //(2 + j) cause we start from PA2
		if(!keys) {									// if key is this column
//			GPIO_PORTB_DATA_R = ~charTo7Seg(keymap[row][j]);
			return keymap[row][j];
		}
	}
	return '\0';
}

unsigned char getPress(void){

	GPIO_PORTE_DATA_R &= ~(0x0f);
	unsigned int keys = (GPIO_PORTA_DATA_R & 0x3c);
	if(AnyPressed(keys)){
		return getPressedChar(keys);					
	}
	return '\0'; //return null if no key is pressed
	
	
}

unsigned int charTo7Seg(unsigned char character) {
	switch(character) {
		case '0':
			return 0x3f;
		case '1':
			return 0x06;
		case '2':
			return 0x5b;
		case '3':
			return 0x4f;
		case '4':
			return 0x66;
		case '5':
			return 0x6d;
		case '6':
			return 0x7d;
		case '7':
			return 0x07;
		case '8':
			return 0x7f;
		case '9':
			return 0x67;
		case 'A':
			return 0x77;
		case 'B':
			return 0x7c;
		case 'C':
			return 0x39;
		case 'D':
			return 0x5e;
		case 'E':
			return 0x79;
		case 'F':
			return 0x71;
		default:
			return 0x40;
	}
}	