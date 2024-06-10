#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"
#include "SysTick.h"
#include "uart_drive.h"

char USART_1_msg[250]; // string message
unsigned short USART_1_cnt = 0; //counter for string
unsigned short USART_1_signal = 0; //signal to indicate that string is ready
unsigned short USART_1_bdg = 0; //bridge

char USART_2_msg[250]; // string message
unsigned short USART_2_cnt = 0; //counter for string
unsigned short USART_2_signal = 0; //signal to indicate that string is ready
unsigned short USART_2_bdg = 0; //bridge

char USART_3_msg[250]; // string message
unsigned short USART_3_cnt = 0; //counter for string
unsigned short USART_3_signal = 0; //signal to indicate that string is ready
unsigned short USART_3_bdg = 0; //bridge

char chat = 'c';
char msg[30] = "Welcome to the World";


int main(void)
{
	//Delay Function
	SysTick_init();
  USART_init(2, 115200);
	USART_init(3, 9600);
	
  Systick_DelayMs(100);
	
	UART_SEND(2,msg);
	UART_SEND(3,msg);
	
	while (1)
	{
		if(USART_2_signal == 1)
		{
			UART_SEND(3, USART_2_msg);
			USART_2_signal = 0;
			str_empty(USART_2_msg);
		}
		
		if(USART_3_signal == 1)
		{
			UART_SEND(2, USART_3_msg);
			USART_3_signal = 0;
			str_empty(USART_3_msg);
		}
		
	}
}

void USART2_IRQHandler()
{
 USART_ISR(2, 3, &USART_2_signal, &USART_2_cnt, USART_2_msg);
}

void USART3_IRQHandler()
{
 USART_ISR(3,2, &USART_3_signal, &USART_3_cnt, USART_3_msg);
}

