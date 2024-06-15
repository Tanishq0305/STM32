#include "stm32f10x.h"                  // Device header
#include "SysTick.h"
#include "gp_drive.h"
#include "i2c_drive.h"

void i2c_init(char i2c, unsigned short speed_mode)
{
	RCC->APB2ENR |= 1; //AFIO pin enable
	
	if(i2c ==1)
	{
		RCC->APB2ENR |= 0x0200000; //I2C1 enable
		
		//Pin Enable
		init_GP(PB, 6, OUT50, O_AF_OD);
		init_GP(PB, 7, OUT50, O_AF_OD);
		
		//Peripheral
		I2C1->CR1 |= 0x8000; //Reset I2C1
		I2C1->CR1 &= ~0x8000; //Remove reset
		I2C1->CR2 = 0x8; //Freqeuncy of I2C
		I2C1->CCR = speed_mode; //Select speed mode for I2C1
		I2C1->TRISE |= 0x9; //T rise of the I2C
		I2C1->CR1 |= 1; //Enable I2C1
		
	}else if(i2c == 2)
	{
		RCC->APB2ENR |= 0x0400000; //I2C2 enable
		//Pin Enable
		init_GP(PB, 10, OUT50, O_AF_OD);
		init_GP(PB, 11, OUT50, O_AF_OD);
		//Peripheral
		I2C2->CR1 |= 0x8000; 
		I2C2->CR1 &= ~0x8000; 
		I2C2->CR2 = 0x8; 
		I2C2->CCR = speed_mode; 
		I2C2->TRISE |= 0x9; 
		I2C2->CR1 |= 1;
	}
}

void I2c_start(char i2c)
{
	if(i2c == 1)
	{
		I2C1->CR1 |= 0x100; //Start bit set
		while(!(I2C1-> SR1 & 1)) {} //Wait until SR1 1st bit is cleared
		
	}else if(i2c == 2)
	{
		I2C2->CR1 |= 0x100; //Start bit set
		while(!(I2C2-> SR1 & 1)) {} //Wait until SR1 1st bit is cleared
	}
}

void I2C_write(char i2c, char address, char data[])
{
	int i=0;
	I2c_start(i2c);
	I2C_add(i2c,address, 0);
	while(data[i])
	{
		I2C_data(i2c, data[i]);
		i++;
	}
	I2C_stop(i2c);

}

void I2C_add(char i2c, char address, char RW)
{
	volatile int tmp;
	if(i2c == 1)
	{
		I2C1->DR = (address|RW); //load address in the DR
		while((I2C1->SR1 & 2) == 0){} //Wait till the ACK is received
				while(I2C1->SR1 & 2) //When ACK is received loop to read SR1 & SR2s till address is cleared
				{
					tmp = I2C1->SR1;
					tmp = I2C1->SR2;
						if((I2C1->SR1 & 2) == 0) //When the address cleared then break the loop
						{break;}
				} 
	}else if(i2c == 2)
	{
			I2C2->DR = (address|RW);
			while((I2C2->SR1 & 2) == 0){} 
				while(I2C2->SR1 & 2) 
				{
					tmp = I2C2->SR1;
					tmp = I2C2->SR2;
						if((I2C2->SR1 & 2) == 0) 
						{break;}
				} 
	}
}

void I2C_data(char i2c, char data)
{
	if(i2c == 1)
	{
		while((I2C1->SR1 & 0x80)== 0) {} //Wait till the Txe becomes 0
			I2C1->DR = data; //load data in DR
		while((I2C1->SR1 & 0x80)== 0) {} //Wait till the Txe again becomes 0
	}else if(i2c == 2)
	{
		while((I2C2->SR1 & 0x80)== 0) {} //Wait till the Txe becomes 0
			I2C2->DR = data; //load data in DR
		while((I2C2->SR1 & 0x80)== 0) {} //Wait till the Txe again becomes 0
	}
}

void I2C_stop(char i2c)
{
	volatile int tmp;
	if(i2c == 1)
	{
		tmp = I2C1->SR1;
		tmp = I2C1->SR2;
		I2C1 -> CR1 |= 0x200;
		
	}else if(i2c == 2)
	{
		tmp = I2C2->SR1;
		tmp = I2C2->SR2;
		I2C2 -> CR1 |= 0x200;
	}
}
