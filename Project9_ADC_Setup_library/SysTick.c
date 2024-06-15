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

void SysTick_int_start()
{
		__disable_irq();
	SysTick->CTRL = 0; //Reset register
	SysTick->LOAD = 1080000; //Load register to Maximum
	SysTick->VAL = 0; //Current counter value to 0
	SysTick->CTRL = 7; // 7- means initiating the interrupt
	__enable_irq();
}

void SysTick_int(unsigned short usart_1_mgr[], unsigned short usart_2_mgr[], unsigned short usart_3_mgr[])
{
//--------------------if the count i other than 0 for USART1 ---------------------------------//
	if(usart_1_mgr[0] != 0) 
	{
						if(usart_1_mgr[6] == 0) //time counter is reached 0 i.e. its counting is done for the USART1
						{
							usart_1_mgr[0] = 0; //re-initialize the counter
							usart_1_mgr[1] = 1; //set the signal to HIGH
							SysTick_init(); //this will disable the interrupts
						}else
						{
							usart_1_mgr[6]--; //decrement the counters
						}
						
	}
//--------------------if the count i other than 0 for USART2 ---------------------------------//
	else if(usart_2_mgr[0] != 0)
	{
					if(usart_2_mgr[6] == 0) //time counter is reached 0 i.e. its counting is done for USART2
						{
							usart_2_mgr[0] = 0; //same
							usart_2_mgr[1] = 1; 
							SysTick_init(); 
						}else
						{
							usart_2_mgr[6]--; 
						}
	}
//--------------------if the count i other than 0 for USART3 ---------------------------------//
	else if(usart_3_mgr[0] != 0)
	{
					if(usart_3_mgr[6] == 0) //time counter is reached 0 i.e. its counting is done for USART3
						{
							usart_3_mgr[0] = 0; //same
							usart_3_mgr[1] = 1; 
							SysTick_init(); 
						}else
						{
							usart_3_mgr[6]--; 
						}
	}
		
}