#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"
#include "SysTick.h"

int main()
{
	SysTick_init(); //We observed that if we don't put this then the timer don't initialise
	RCC->APB2ENR |= 0x01; //Enable AFIO
	RCC->APB2ENR |= 0x1000; //Enable SPI1 bit
	
	//--------------------Pin Setup---------------------------//
	init_GP(PA, 4, OUT50, O_GP_PP); //PA4 - SS - General OUT
	init_GP(PA, 5, OUT50, O_AF_PP); //PA5 - CLK - Alternate OUT
	init_GP(PA, 6, IN, IPP);				//PA6 - MISO - Alternat In
	init_GP(PA, 7, OUT50, O_AF_PP); //PA6 - MOSI - Alternate OUT 
	
	//-------------SPI Peripheral Setup------------------------//
	SPI1->CR1 |= 0x4; //Master mode
	SPI1->CR1 |= 0x31; //Clock Speed/ 256
	SPI1->CR2 |= 0x4; //SSOE
	SPI1->CR1 |= 0x40; // SPE i.e. enable SPI peri
	W_GP(PA,4,HIGH); //select line HIGH
	
	//-------------------Sending Message---------------------------//
	
	while(1)
	{
		//Sending 
		Systick_DelayMs(50);
		W_GP(PA,4,LOW); //Low select pin data loading
		SPI1->DR = 'W'; //load data to send in register
		while(SPI1->SR & 0x80) {} //When the controller is busy then just wait
		W_GP(PA,4,HIGH); //Select Pin HIGH 
			

		W_GP(PA,4,LOW); //Low select pin data loading
		SPI1->DR = 'e'; //load data to send in register
		while(SPI1->SR & 0x80) {} //When the controller is busy then just wait
		W_GP(PA,4,HIGH); //Select Pin HIGH 
			
			
			

		W_GP(PA,4,LOW); //Low select pin data loading
		SPI1->DR = 'e'; //load data to send in register
		while(SPI1->SR & 0x80) {} //When the controller is busy then just wait
		W_GP(PA,4,HIGH); //Select Pin HIGH 
			
			
		
		W_GP(PA,4,LOW); //Low select pin data loading
		SPI1->DR = 'W'; //load data to send in register
		while(SPI1->SR & 0x80) {} //When the controller is busy then just wait
		W_GP(PA,4,HIGH); //Select Pin HIGH 
		
	}
}