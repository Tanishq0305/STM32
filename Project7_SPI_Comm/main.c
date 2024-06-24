#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"
#include "SysTick.h"
#include "SPI_drive.h"

int main()
{
	SysTick_init(); //We observed that if we don't put this then the timer don't initialise
	RCC->APB2ENR |= 0x01; //Enable AFIO
	spi_init(1);

	//-------------------Sending Message---------------------------//
	while(1)
	{
		//Sending 
		Systick_DelayMs(50);
		spi_Tx(1, 'W');
		spi_Tx(1, 'e');
		spi_Tx(1, 'e');
		spi_Tx(1, 'w');
		
		spi_msg(1, "Weew");
		
	}
}