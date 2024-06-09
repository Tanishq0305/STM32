#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"
#include "SysTick.h"
#include "uart_drive.h"

char chat = 'c';

int main(void)
{
	//Delay Function
	SysTick_init();
  USART_init(2, 115200);

	while (1)
	{
		//Receive Data
		chat = USART_RX(2);
			
		//Transmit data
    USART_TX(2,chat);
	 
	}
}
