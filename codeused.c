/* This code will count multiples of 3 with one . , representing
 * that one count till 30 is over and another has started.
 * Basically : 0,3,6,9,2,5,8,1,4,7,.,
 */

#include "stm32f446xx.h"

void DISPLAY_7(unsigned char data);

// First of all find pins that will be used
/*
 * a=PA10
 * b=PB3
 * c=PB5
 * d=PB4
 * e=PB10
 * f=PA8
 * g=PA9
 * DP=PC7
 */

// So we need to turn on GPIOA,GPIOB,GPIOC clocks

void delay(long t)
{
	while(t--);
}


void DISPLAY_7(unsigned char data)
{
	if((data & 0x01) == 0x01)  // A
	{
		GPIOA->ODR = GPIOA->ODR | (1<<10);
	}else{
		GPIOA->ODR = GPIOA->ODR & (~(1<<10));
	}
	if((data & 0x02) == 0x02)  // B
	{
		GPIOB->ODR = GPIOB->ODR | (1<<3);
	}else{
		GPIOB->ODR = GPIOB->ODR & (~(1<<3));
	}
	if((data & 0x04) == 0x04)	 // C
	{
		GPIOB->ODR = GPIOB->ODR | (1<<5);
	}else{
		GPIOB->ODR = GPIOB->ODR & (~(1<<5));
	}
	if((data & 0x08) == 0x08)  // D
	{
		GPIOB->ODR = GPIOB->ODR | (1<<4);
	}else{
		GPIOB->ODR = GPIOB->ODR & (~(1<<4));
	}
	if((data & 0x10) == 0x10)  // E
	{
		GPIOB->ODR = GPIOB->ODR | (1<<10);
	}else{
		GPIOB->ODR = GPIOB->ODR & (~(1<<10));
	}
	if((data & 0x20) == 0x20)  // F
	{
		GPIOA->ODR = GPIOA->ODR | (1<<8);
	}else{
		GPIOA->ODR = GPIOA->ODR & (~(1<<8));
	}
	if((data & 0x40) == 0x40)  // G
	{
		GPIOA->ODR = GPIOA->ODR | (1<<9);
	}else{
		GPIOA->ODR = GPIOA->ODR & (~(1<<9));
	}
	if((data & 0x80) == 0x80)  // DP
	{
		GPIOC->ODR = GPIOC->ODR | (1<<7);
	}else{
		GPIOC->ODR = GPIOC->ODR & (~(1<<7));
	}
}

void DATA_MAP(int i,int j)
{
	if(i==1){
		DISPLAY_7(0x06);
	}else if(i==2){
		DISPLAY_7(0x5B);
	}else if(i==3){
		DISPLAY_7(0x4F);
	}else if(i==4){
		DISPLAY_7(0x66);
	}else if(i==5){
		DISPLAY_7(0x6E);
	}else if(i==6){
		DISPLAY_7(0x7E);
	}else if(i==7){
		DISPLAY_7(0x47);
	}else if(i==8){
		DISPLAY_7(0x7F);
	}else if(i==9){
		DISPLAY_7(0x6F);
	}else if(i==0){
		DISPLAY_7(0x3F);
	}
	if(j==1){
		DISPLAY_7(0x80);
	}
}


int main()
{
	// RCC_AHB1ENR last 3 bits 1 CLOCK ON
	RCC->AHB1ENR = RCC->AHB1ENR | (1<<2) | (1<<1) | (1<<0);
	// Now we make those pins as output pins
	// A-> 8,9,10 B->3,4,5,10 C->5,7
	GPIOA->MODER = GPIOA->MODER | (1<<16) | (1<<18) | (1<<20);
	GPIOB->MODER = GPIOB->MODER | (1<<6) | (1<<8) | (1<<10) | (1<<20);
	GPIOC->MODER = GPIOC->MODER | (1<<10) | (1<<14);

	int m=0;
	int k;
	while(1)
	{
		for(k=0;k<30;k+=3)
		{
			DATA_MAP(k%10,m); // This will count 3,6,9,2,5,8,1....
			delay(600000);
		}
		m=!m;
		delay(600000);
		DATA_MAP(0,m); // Turn on DP
		m=!m; // Again turn off
		delay(600000);
	}
	return 0;
}
