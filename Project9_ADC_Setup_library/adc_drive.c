#include "adc_drive.h"

//------------------ ADC Initialization-------------------//
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
						ADC1->CR2 = 0; 				 //RESET the CR2
						ADC1->SQR3 = channel;   //Select the channel in the SQR3 register to scan
						
						ADC1->CR2 |= 1;				//Wake up ADC
						Systick_DelayMs(100); //Delay to till wake it up
						ADC1->CR2 |= 1; 			//Start the conversion
						
						ADC1->CR2 |= 2; 		//Continuous conversion setup
					
					}else if(adc==adc2)
					{
						RCC->APB2ENR |= 0x401; //Enabling the AFIO of GPIOs and Enabling ADC2
						ADC2->CR2 = 0; 				 //RESET the CR2
						ADC2->SQR3 = channel;   //Select the channel in the SQR3 register to scan
						
						ADC2->CR2 |= 1;				//Wake up ADC
						Systick_DelayMs(100); //Delay to till wake it up
						ADC2->CR2 |= 1; 			//Start the conversion
						
						ADC2->CR2 |= 2; 		//Continuous conversion setup
					}
		}
		return result;
}

//------------------ Flag Check for conversion -------------------//
char adc_check(char adc, short port, short pin)
{
	char check = 0;
	if(adc==adc1)
	{
			if(ADC1->SR & 2) // checking the EOC bit is 1 or not
			{	
				check =1;			//If it is 1 then we will set check to 1
			}
	}else if(adc==adc2)
	{
			if(ADC2->SR & 2) 
			{	
				check =1;			
			}
	}
	
	return check;
}

//------------------ Rx of ADC -------------------//
int adc_rx(char adc, short port, short pin)
{
	int result = 0;
	int data = 0;
	
	if(adc == adc1)
	{
		data = ADC1->DR;
	}else if(adc == adc2)
	{
		data = ADC2->DR;
	}
	
	result = (data*1000)/0xfff;
	return result;
}