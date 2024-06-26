#include "uart_drive.h"
#include "gp_drive.h"
#include "stm32f10x.h"                  // Device header
#include "SysTick.h"


void USART_init(unsigned short usart, unsigned long BR)
{
	//If you are using USART1 clocl speed 108MHZ, else 54MHz
	// USART3 -> PB10 (Tx) & PB11 (Rx)
	//USART2 -> PA2 (Tx) & PA3 (Rx)
	//USART1 -> PA9 (Tx) & PA10 (Rx)
	
	unsigned long BRR_Calculation;
	BRR_Calculation = USART_BRR(usart, BR);
  //Enabling AFIO of Bus-2
	RCC->APB2ENR |= 1;
	
	if(usart ==1)
	{
		__disable_irq();
		
	RCC->APB2ENR |= 0x4000; //Enabling USART1 from the bus
	init_GP(PA, 9, OUT50, O_GP_PP); //Enabling Output or Tx
	init_GP(PA, 10, IN, IPP); //Enabling Input or Rx
	USART1->BRR |= BRR_Calculation; //Setting the baud rate for 9600
	USART1->CR1 |= 8;	//Setting UART Transmit
	USART1->CR1 |= 4;	//Setting UART Receive
	USART1->CR1 |= 0x2000;	//Enabling UART1 on the CR
		
	USART1->CR1 |= 0x20; //RXNEIE interrupt enable
	NVIC_EnableIRQ(USART1_IRQn);
	__enable_irq();
		
	}
	else if(usart == 2)
	{ 
	__disable_irq();
		
	RCC->APB1ENR |= 0x20000; 	//Enabling USART1 from the bus
	init_GP(PA, 2, OUT50, O_GP_PP); //Output or Tx
	init_GP(PA, 3, IN, IPP); //Input or Rx
	USART2->BRR |= BRR_Calculation; 	//Setting the baud rate for 9600
	USART2->CR1 |= 8;	//Setting UART Transmit
	USART2->CR1 |= 4;	//Setting UART Receive
	USART2->CR1 |= 0x2000;	//Enabling UART on the CR
		
	USART2->CR1 |= 0x20; //RXNEIE interrupt enable
	NVIC_EnableIRQ(USART2_IRQn);
	__enable_irq();
	}else if(usart == 3)
	{
	__disable_irq();
		
	RCC->APB1ENR |= 0x40000; //Enabling USART3 from the bus
	init_GP(PB, 10, OUT50, O_GP_PP); //Enabling Output or Tx
	init_GP(PB, 1, IN, IPP); //Enabling Input or Rx
	USART3->BRR |= BRR_Calculation; //Setting the baud rate for 9600
	USART3->CR1 |= 8;	//Setting UART Transmit
	USART3->CR1 |= 4;	//Setting UART Receive
	USART3->CR1 |= 0x2000;	//Enabling UART
		
	USART3->CR1 |= 0x20; //RXNEIE interrupt enable
	NVIC_EnableIRQ(USART3_IRQn);
	__enable_irq();
		
	}
}

unsigned long USART_BRR(unsigned short usart, unsigned long BR)
{
	unsigned long div = 54000000; //Store the integer number division by the clock 
	//our clock is 108MHz so we used 54MHz if clock=72MHz -> it will be 36MHz
	unsigned long dec;
	double frac = 54000000.00; //for storing the fractional part
	double frac2;
	unsigned long final;
	
	if(usart == 1)
	{
	div = 108000000; //Store the integer number division by the clock 
	frac = 108000000.00; //for storing the fractional part
	}
	div = div/(BR*16); //From the baud rate calculation formula //Division Result Calculation
	frac = 16 * (frac/(BR*16)-div);//From the baud rate calculation formula //Fractional Calculation
	dec = frac;
	frac2 = 100 * (dec-frac);
	if(frac2>50)
	 {
		dec++;
		if(dec==16)
	{
		frac =0;
		div++;
	}
	 }

	
	final = (div<<4);
	final += dec;
	
	return final;
}

char USART_RX(unsigned short usart)
{
	char c;
	if(usart == 1)
	  {
		while((USART1->SR & 0x20) == 0) // If RXNE bit is LOW then we are not recevings
		{}
		c = USART1->DR; //If RXNE bit is HIGH then we can see received data in the chat variable
	  }
	else if(usart == 2)
	  {
		while((USART2->SR & 0x20) == 0) // If RXNE bit is LOW then we are not recevings
		{}
		c = USART2->DR; //If RXNE bit is HIGH then we can see received data in the chat variable
	  }
	else if(usart == 3)
		{
		while((USART3->SR & 0x20) == 0) // If RXNE bit is LOW then we are not recevings
		{}
		c = USART3->DR; //If RXNE bit is HIGH then we can see received data in the chat variable
		}
	return c;
}

void USART_TX(unsigned short usart, char c)
{

	if(usart == 1)
	  {
		while((USART1->SR & (1<<6)) == 0x00) // If TXE bit is 0 then we do not send any data
		{}
		USART1->DR = c;	// if the TXE is 0 then send the chat character
	  }
	else if(usart == 2)
	  {
		while((USART2->SR & (1<<6)) == 0x00) // If TXE bit is 0 then we do not send any data
		{}
		USART2->DR = c;	// if the TXE is 0 then send the chat character
	  }
	else if(usart == 3)
		{
		while((USART3->SR & (1<<6)) == 0x00) // If TXE bit is 0 then we do not send any data
		{}
		USART3->DR = c;	// if the TXE is 0 then send the chat character
		}

}

void USART_ISR(unsigned short uart, unsigned short bridge, unsigned short * signal, unsigned short * counter, char str[])
{
	if(bridge == 0) // If bridge is not HIGH means it is process
	{
		str[*counter] = USART_RX(uart); //First receive the message
		if(str[*counter] == '\n') //If the counter pointer reaches to new line charcter 
		{
			* counter = 0; //reset counter to 0
			* signal = 1; //Set the signal to HIGH
		}else
		{
			* counter = *counter + 1; //else increment the counter
		}
	}else
	{
		USART_TX(uart, USART_RX(uart)); // if bridge == 1 that means user need to perform only bridgr operation
	}
}

void UART_SEND(unsigned short uart, char str[])
{
	int i = 0;
	while(str[i] != '\0') //while the str[i] is not new-line character
	{
		USART_TX(uart, str[i]); //send the string character
		i++;
		
	}
}

void str_empty(char str[])
{
	int i = 0;
	while(str[i] != '\0') //while the str[i] is not new-line character
	{
		str[i] = '\0';
		i++;
	}
}