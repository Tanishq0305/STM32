#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"
#include "SysTick.h"
#include "uart_drive.h"

char chat = 'c';

int main(void)
{
	//Delay Function
	SysTick_init();
  USART_init(3, 115200);

	while (1)
	{
		//Receive Data
		while((USART3->SR & 0x20) == 0) // If RXNE bit is LOW then we are not recevings
		{}
		chat = USART3->DR; //If RXNE bit is HIGH then we can see received data in the chat variable
			
		//Transmit data
		while((USART3->SR & (1<<6)) == 0x80) // If TXE bit is 1 then we do not send any data
		{}
		Systick_DelayMs(100);  //I have not declared it in this project yet
		USART3->DR = chat;	// if the TXE is 0 then send the chat character
	 
	}
}
