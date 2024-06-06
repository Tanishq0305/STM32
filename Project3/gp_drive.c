#include "gp_drive.h"

//Pin Enable or Configuration Function
void init_GP(unsigned short port, unsigned short pin, unsigned short dir, unsigned short opt)
{
	volatile unsigned long * CR; //This is the register we will update wrt input parameters
	unsigned short tPIN = pin;
	unsigned short offset = 0x00; //Offset to get to know we're at CRL or CRH 
	//For CRL offset = 0x00 and for CRH offset = 0x01
	
	if(pin > 7)
	{
		tPIN -= 8;
		offset = 0x01;
	}
	
	if(port == 1)
	{
		RCC_APB2ENR |= 4; // Enabling port A by general method
		CR = (volatile unsigned long *) ( &GPIO_A + offset); //setting address of GPIOA in CR and moving to next register by addin offset
		
	}	else if(port == 2)
	{
		RCC_APB2ENR |= 8; // Enabling port B by general method
		CR = (volatile unsigned long *) ( &GPIO_B + offset); //setting address of GPIOA in CR and moving to next register by addin offset
		
	}else if(port == 3)
	{
		RCC_APB2ENR |= 0x10; // Enabling port B by general method
		CR = (volatile unsigned long *) ( &GPIO_C + offset); //setting address of GPIOA in CRand moving to next register by addin offset
		
	}
	*CR &= ~(0xF<<(tPIN)*4); //Reset target Pin // Just reseting the Mode and CNF value // see explanation in word
  *CR |= ((dir<<(tPIN*4)) | (opt<<(tPIN*4+2))); //set direction and option for the pin
}

//Pin Read Function
int R_GP(unsigned short port, unsigned short pin)
{
	volatile unsigned long * IDR;
	unsigned long offset = 0x02;
	int state;
	
	if(port == 1)
	{
		IDR = (volatile unsigned long *) (&GPIO_A + offset); //Set the value of GPIO_A in IDR with offset
	}else if(port == 2)
	{
		IDR = (volatile unsigned long *) (&GPIO_B + offset); //Set the value of GPIO_B in IDR with offset
	}else if(port == 3)
	{
		IDR = (volatile unsigned long *) (&GPIO_C + offset); //Set the value of GPIO_C in IDR with offset
	}
	state = ((*IDR | (1<<pin))>>pin);  //Checking the status of Pin by using IDR 
	return state;
}

//Pin Write Function
void W_GP(unsigned short port, unsigned short pin, unsigned short state)
{
	volatile unsigned long * ODR;
	unsigned long offset = 0x03;

	
	if(port == 1)
	{
		ODR = (volatile unsigned long *) (&GPIO_A + offset); //Set the value of GPIO_A in ODR with offset
	}else if(port == 2)
	{
		ODR = (volatile unsigned long *) (&GPIO_B + offset); //Set the value of GPIO_B in ODR with offset
	}else if(port == 3)
	{
		ODR = (volatile unsigned long *) (&GPIO_C + offset); //Set the value of GPIO_C in ODR with offset
	}
	state ? (*ODR |= (state<<pin)) : (*ODR &= ~(1<<pin)); //If the ODR is 1 then put 1 at pin or else reverse
}

//Toggle Function
void toggle_GP(unsigned short port, unsigned short pin)
{
	if (R_GP(port,pin)) //If the state is 1
	{
		W_GP(port, pin, 0); //Then make it 0
	}
	else
	{
			W_GP(port, pin, 1);// or if state is 0 then make it 1
	}
}