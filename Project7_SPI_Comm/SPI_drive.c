/*
#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"
#include "SPI_drive.h"

void spi_init(unsigned short spi)
{
	RCC->APB2ENR |= 0x01; //Enable AFIO for GPIOs
	if(spi == 1)
	{
	RCC->APB2ENR |= 0x1000; //Enable SPI1 bit
	//--------------------Pin Setup---------------------------//
	init_GP(PA, 4, OUT50, O_GP_PP); //PA4 - SS - General OUT
	init_GP(PA, 5, OUT50, O_AF_PP); //PA5 - CLK - Alternate OUT
	init_GP(PA, 6, IN, IPP);				//PA6 - MISO - Alternat In
	init_GP(PA, 7, OUT50, O_AF_PP); //PA6 - MOSI - Alternate OUT 
	//-------------SPI Peripheral Setup------------------------//
	SPI1->CR1 |= 0x4; //Master mode
	SPI1->CR1 |= 0x31; //Clock Speed/ 256
	SPI1->CR2 |= 0x4; //SSOE
	SPI1->CR1 |= 0x40; // SPE i.e. enable SPI peri
	W_GP(PA,4,HIGH); //select line HIGH
		
	}else if(spi == 2)
	{
	RCC->APB1ENR |= 0x4000; //Enable SPI2 bit
	//--------------------Pin Setup---------------------------//
	init_GP(PA, 12, OUT50, O_GP_PP); 
	init_GP(PA, 13, OUT50, O_AF_PP); 
	init_GP(PA, 14, IN, IPP);				
	init_GP(PA, 15, OUT50, O_AF_PP); 
	//-------------SPI Peripheral Setup------------------------//
	SPI2->CR1 |= 0x4; 
	SPI2->CR1 |= 0x31; 
	SPI2->CR2 |= 0x4; 
	SPI2->CR1 |= 0x40; 
	W_GP(PA,12,HIGH); 
		
	}
}

void spi_Tx(unsigned short spi, char tx_char)
{
	if(spi == 1)
	{
		W_GP(PA,4,LOW); //Low select pin data loading
		SPI1->DR = tx_char; //load data to send in register
		while(SPI1->SR & 0x80) {} //When the controller is busy then just wait
		W_GP(PA,4,HIGH);
	}else if(spi == 2)
	{
		W_GP(PB,12,LOW); 
		SPI1->DR = tx_char; 
		while(SPI2->SR & 0x80) {} 
		W_GP(PB,12,HIGH);
	}
}

void spi_msg(unsigned short spi, char str[])
{
	int i = 0;
	if(spi ==1)
	{
				W_GP(PA,4,LOW); 
				while(str[i]) //While string is there sends
				{
					SPI1->DR = str[i]; 
					while(SPI1->SR & 0x80) {}
					i++;
				}
				W_GP(PA,4,HIGH);
				
	}else if(spi == 2)
	{
				W_GP(PB,12,LOW); 
				while(str[i]) //While string is there sends
				{
					SPI2->DR = str[i]; 
					while(SPI2->SR & 0x80) {}
					i++;
				}
				W_GP(PB,12,HIGH);
	}
}
*/

#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"
#include "SPI_drive.h"

void spi_init(unsigned short spi)
{
    RCC->APB2ENR |= 0x01; // Enable AFIO for GPIOs
    if(spi == 1)
    {
        RCC->APB2ENR |= 0x1000; // Enable SPI1 bit
        //--------------------Pin Setup---------------------------//
        init_GP(PA, 4, OUT50, O_GP_PP); // PA4 - SS - General OUT
        init_GP(PA, 5, OUT50, O_AF_PP); // PA5 - CLK - Alternate OUT
        init_GP(PA, 6, IN, IPP);        // PA6 - MISO - Alternat In
        init_GP(PA, 7, OUT50, O_AF_PP); // PA7 - MOSI - Alternate OUT 
        //-------------SPI Peripheral Setup------------------------//
        SPI1->CR1 |= 0x4; // Master mode
        SPI1->CR1 |= 0x31; // Clock Speed/256
        SPI1->CR2 |= 0x4; // SSOE
        SPI1->CR1 |= 0x40; // SPE i.e. enable SPI peri
        W_GP(PA,4,HIGH); // Select line HIGH
        
    } else if(spi == 2)
    {
        RCC->APB1ENR |= 0x4000; // Enable SPI2 bit
        //--------------------Pin Setup---------------------------//
        init_GP(PA, 12, OUT50, O_GP_PP); 
        init_GP(PA, 13, OUT50, O_AF_PP); 
        init_GP(PA, 14, IN, IPP);                
        init_GP(PA, 15, OUT50, O_AF_PP); 
        //-------------SPI Peripheral Setup------------------------//
        SPI2->CR1 |= 0x4; 
        SPI2->CR1 |= 0x31; 
        SPI2->CR2 |= 0x4; 
        SPI2->CR1 |= 0x40; 
        W_GP(PA,12,HIGH); 
        
    }
}

void spi_Tx(unsigned short spi, char tx_char)
{
    if(spi == 1)
    {
        W_GP(PA,4,LOW); // Low select pin data loading
        SPI1->DR = tx_char; // Load data to send in register
        while(SPI1->SR & 0x80) {} // When the controller is busy then just wait
        W_GP(PA,4,HIGH);
    } else if(spi == 2)
    {
        W_GP(PB,12,LOW); 
        SPI1->DR = tx_char; 
        while(SPI2->SR & 0x80) {} 
        W_GP(PB,12,HIGH);
    }
}

void spi_msg(unsigned short spi, char str[])
{
    int i = 0;
    if(spi ==1)
    {
        W_GP(PA,4,LOW); 
        while(str[i]) // While string is there sends
        {
            SPI1->DR = str[i]; 
            while(SPI1->SR & 0x80) {}
            i++;
        }
        W_GP(PA,4,HIGH);
                
    } else if(spi == 2)
    {
        W_GP(PB,12,LOW); 
        while(str[i]) // While string is there sends
        {
            SPI2->DR = str[i]; 
            while(SPI2->SR & 0x80) {}
            i++;
        }
        W_GP(PB,12,HIGH);
    }
}

char spi_Rx(unsigned short spi)
{
    char rx_char;
    if(spi == 1)
    {
        while(!(SPI1->SR & 0x01)) {} // Wait until Receive buffer is not empty
        rx_char = SPI1->DR; // Read the received data
    } else if(spi == 2)
    {
        while(!(SPI2->SR & 0x01)) {} // Wait until Receive buffer is not empty
        rx_char = SPI2->DR; // Read the received data
    }
    return rx_char;
}
