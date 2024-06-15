#include "adc_drive.h"

char adc_init(char adc, short port, short pin)
{
	char channel;
	char result = 0;
		if(port == PA) //Checking if user selected portA
		{
			if(pin<8) //setting the channel from the pin -> adc_drive.h
			{
				result = 1;
				channel = pin;
			}
	  }else if(port == PB)//Checking if user selected portB
		{
			if(pin<2)
			{
				result = 1;
				channel = 8 + pin;
			}
		}else if(port == PC)//Checking if user selected portC
		{
			if(pin<6)
			{
				result =1 ;
				channel = 10 + pin;
				
			}
		}
		//--------------- After configuring the channel and setting result to 1 --------------------//
		if(result == 1)
		{
			init_GP(port,pin,IN,I_AN); //selecting Pin as analog input
			if(adc == adc1)
			{
				RCC->APB2ENR |= 0x201; //Enabling the AFIO of GPIOs and Enabling ADC1
			}
		}

	
}