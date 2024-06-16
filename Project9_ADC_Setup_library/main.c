#include "stm32f10x.h"                  // Device header
#include "SysTick.h"
#include "gp_drive.h"
#include "adc_drive.h"
#include "uart_drive.h"
#include "help_func.h"

char num[10]; //char array
int analog_rx =0;

int main()
{
	SysTick_init();
	USART_init(2,115200); //USART Setup
	
	adc_init(adc1, PA, 0); 
	while(1)
	{
		if(adc_check(adc1, PA,0))
		{
			analog_rx = adc_rx(adc1, PA,0) *330; //stroing the readings into analog_rx
			analog_rx = analog_rx/100;
			int2char(analog_rx, num); //using help function to convert the input to array
			UART_SEND(2,num); //Send string on  USARt
			USART_TX(2, '\n');
			str_empty(num);
		}
		
	}
		
}
