#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"

int main(void)
{
	init_GP(PA, 0, IN, IPP); // added PA0 as input
	init_GP(PA, 12, OUT50, O_GP_PP); //Added PA12 as output
	init_GP(PC, 13, OUT50, O_GP_PP); //Added PC13 as output
	
	__disable_irq();
	SysTick->CTRL = 0; //Set CRTL register to zero or reset
	SysTick->LOAD = 7200000-1; //set load value to maximum
	SysTick->VAL = 0; // Set current counter value to 0
	SysTick->CTRL = 7;
	__enable_irq();
	


	while (1)
	{
	 W_GP(PA,12,R_GP(PA,0));
	}
}

void SysTick_Handler(void)
{
	toggle_GP(PC,13);
}