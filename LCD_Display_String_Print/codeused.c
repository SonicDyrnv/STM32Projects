#include "stm32f446xx.h"
#include <stdio.h>

/* First of all Pin connections
 * RS = Pb6
 * RW = Pa7
 * EN = Pa6
 * D0 = Pa10
 * D1 = Pb3
 * D2 = Pb5
 * D3 = Pb4
 * D4 = Pb10
 * D5 = Pa8
 * D6 = Pa9
 * D7 = Pc7
 */

// According to those we need to turn on clocks of
// GPIOA, GPIOB, GPIOC

// Now when we need to turn pins ON and OFF for giving input to LCD
// Since pins of such are same as previous, I will just paste it here.
// DISPLAY_7 function of previous code.

void delay(long i)
{
	while(i--);
}

void LCDIN(unsigned char data)
{
	if((data & 0x01) == 0x01)  // D0
	{
		GPIOA->ODR = GPIOA->ODR | (1<<10);
	}else{
		GPIOA->ODR = GPIOA->ODR & (~(1<<10));
	}
	if((data & 0x02) == 0x02)  // D1
	{
		GPIOB->ODR = GPIOB->ODR | (1<<3);
	}else{
		GPIOB->ODR = GPIOB->ODR & (~(1<<3));
	}
	if((data & 0x04) == 0x04)	 // D2
	{
		GPIOB->ODR = GPIOB->ODR | (1<<5);
	}else{
		GPIOB->ODR = GPIOB->ODR & (~(1<<5));
	}
	if((data & 0x08) == 0x08)  // D3
	{
		GPIOB->ODR = GPIOB->ODR | (1<<4);
	}else{
		GPIOB->ODR = GPIOB->ODR & (~(1<<4));
	}
	if((data & 0x10) == 0x10)  // D4
	{
		GPIOB->ODR = GPIOB->ODR | (1<<10);
	}else{
		GPIOB->ODR = GPIOB->ODR & (~(1<<10));
	}
	if((data & 0x20) == 0x20)  // D5
	{
		GPIOA->ODR = GPIOA->ODR | (1<<8);
	}else{
		GPIOA->ODR = GPIOA->ODR & (~(1<<8));
	}
	if((data & 0x40) == 0x40)  // D6
	{
		GPIOA->ODR = GPIOA->ODR | (1<<9);
	}else{
		GPIOA->ODR = GPIOA->ODR & (~(1<<9));
	}
	if((data & 0x80) == 0x80)  // D7
	{
		GPIOC->ODR = GPIOC->ODR | (1<<7);
	}else{
		GPIOC->ODR = GPIOC->ODR & (~(1<<7));
	}
}

void charIN(char a)
{
	LCDIN(a);
	GPIOB->ODR = GPIOB->ODR | (1<<6);
	GPIOA->ODR = GPIOA->ODR & (~(1<<7));
	GPIOA->ODR = GPIOA->ODR | (1<<6);
	delay(5000);
	GPIOA->ODR = GPIOA->ODR & (~(1<<6));
	delay(100000);
}

void stringIN(char s[])
{
	int lengthofstr=0;
	while(s[lengthofstr]!='\0')
	{
		charIN(s[lengthofstr]);
		lengthofstr++;
	}
}

void commandLCD(char c)
{
	LCDIN(c);
	GPIOB->ODR = GPIOB->ODR & (~(1<<6));
	GPIOA->ODR = GPIOA->ODR & (~(1<<7));
	GPIOA->ODR = GPIOA->ODR | (1<<6);
	delay(5000);
	GPIOA->ODR = GPIOA->ODR & (~(1<<6));
	delay(100000);
}

void LCDinitialize()
{
	commandLCD(0x38); //configuration in 16cols 2 row
	commandLCD(0x06); //display cursor OFF
	commandLCD(0x0C); //auto increment cursor
	commandLCD(0x01); //clear screen
	delay(500000);
}

int main()
{
	// Turning on clocks
	RCC->AHB1ENR = RCC->AHB1ENR | (1<<0) | (1<<1) | (1<<2);
	// Now after turning on clocks we need to convert those
	// GPIO Pins into output mode.
	// A=6,7,8,9,10 ; B=3,4,5,6,10 ; C=7
	GPIOA->MODER = GPIOA->MODER | (1<<12) | (1<<14) | (1<<16) | (1<<18) | (1<<20);
	GPIOA->MODER = GPIOA->MODER & (~(1<<13)) & (~(1<<15)) & (~(1<<17)) & (~(1<<19)) & (~(1<<21));
	GPIOB->MODER = GPIOB->MODER | (1<<6) | (1<<8) | (1<<10) | (1<<12) | (1<<20);
	GPIOB->MODER = GPIOB->MODER & (~(1<<7)) & (~(1<<9)) & (~(1<<11)) & (~(1<<13)) & (~(1<<21));
	GPIOC->MODER = GPIOC->MODER | (1<<14);
	GPIOC->MODER = GPIOC->MODER & (~(1<<15));

	delay(100000);
	LCDinitialize();
	delay(100000);
	while(1)
	{
		commandLCD(0x80);
		stringIN("Dhruv");
		delay(100000); //Some delay to notice whats happening.
		commandLCD(0xC0);
		stringIN("Rathod");
	}
	return 0;
}
