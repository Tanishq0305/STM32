#include "SysTick.h"
#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"

//Configuration of delay
void SysTick_init()
{
	__disable_irq();
	SysTick->CTRL = 0; //Reset register
	SysTick->LOAD = 0x00FFFFFF; //Load register to Maximum
	SysTick->VAL = 0; //Current counter value to 0
	SysTick->CTRL = 5;
	__enable_irq();
}

//1 millisecond delay 
void Dealay_Mills()
{
	SysTick->LOAD = 108000-1; //Puting load value to AHB
	SysTick->VAL = 0; //current counter to zero 
}

//User input delay
void Systick_DelayMs(unsigned int t)
{
	for(;t>0;t--)
	{
		Dealay_Mills();
	}
}

//SysTick Handler or IRQ Function
void SysTick_Handler(void)
{
	toggle_GP(PC,13);
}