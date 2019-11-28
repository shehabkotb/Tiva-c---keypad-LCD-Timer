#ifndef __KEYPAD__
#define __KEYPAD__

#include <stdbool.h>

extern const unsigned char keymap[4][4];

bool AnyPressed(unsigned int keys);
unsigned char getPressedChar(unsigned int keys);
unsigned char detectChar(unsigned int keys,int row);
unsigned char getPress(void);
unsigned int charTo7Seg(unsigned char character);

#endif