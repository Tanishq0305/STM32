#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"
void delay(int time);
void systick_init(void);
void Delaymills(void);
void DelayMs(unsigned long t);
int signal =0;
int main(void)
{
	void systick_init(); //Systick initialization before loop
	/*
	RCC_APB2ENR |= 4; // Enables PORT A in the binary 0000 0000 0000 0100
	RCC_APB2ENR |= 0x10; // Enables PORT C in the binary 0000 0000 0001 0000
	GPIOA->CRL &= 0xFFFFFFF0; //Reset the Port A PIN 0 i.e turn off PIN0 bits
	GPIOA->CRL |= 0x8; //Set the pin0 of Port A as input push-pull

	GPIOC ->CRH |= 0xFF0FFFFF; // Reset PORT C pin 13
	GPIOC->CRH &= 0x00300000; //Set pin13 to output push-pull mode
	*/
	init_GP(PA, 0 ,IN, IPP);
	init_GP(PC, 12, OUT50, O_GP_PP);
	init_GP(PA, 0, OUT50, O_GP_PP);
	
	__disable_irq();
	AFIO->EXTICR[0] = 0x00;
  EXTI->IMR |= 1; //Interrupt request from MRx is not masked
	EXTI->RTSR |= 1; //Set it to rising trigger
	NVIC_EnableIRQ(EXTI0_IRQn);
	__enable_irq();
	
	while(1)
	{
	//	if( R_GP(PA, 0) == 1) //checking PortA Pin0 is High or not
		/*
		W_GP(PA,12,signal);
		if(signal)
		{
		//delay(10);
	  DelayMs(100000);
		toggle_GP(PC, 13); // make pin 13 HIGH when the button is pressed
			// ^= toggels the value
		//delay(10);
		DelayMs(100000);
		}
		else
			{
			W_GP(PC, 13, 0);
			}
			*/
		toggle_GP(PA, 0);
		
	}
	
	
}

void delay(int time)
{
	int t;
	for(;time>0;time--)
	{
		for(t=0;t<100000;t++)
		{	}
	}
}

void EXTI0_IRQHandler()
{
	EXTI->PR |= 1;  // 1 bcz we are managing only pin0 of portA //Enabled the interrupt
	if(signal == 1) //check if signal is 1 or not
	{
		signal = 0;
	}else
	{
		signal = 1;
	}
	
}

//Initialization function of Systick
void systick_init()
{
	SysTick->CTRL = 0; //first put everything to 0 or reset
	SysTick->LOAD = 0x00FFFFFF; //Put load value to maximum
	SysTick->VAL = 0; //Current value of counter set to 0
	SysTick->CTRL = 5; //Force putting 5
}

//Function to create 1ms delay
void Delaymills()
{
	SysTick->LOAD = 108000-1; //Put load to AHB; how many cycles in 1ms
	SysTick->VAL = 0; //Put current counter value to 0
	while((SysTick->CTRL & 0x00010000) ==0) //Until the count flag is set to 1 and that happens automatically in hardware when it reaches 0
	{
		//this loop will run for 1ms
	}	
}

//function to ask user how many ms delay he wants
	void DelayMs(unsigned long t)
	{
		for(;t>0;t--)
		{
			Delaymills();
		}
	}
