#include "stm32f10x.h"                  // Device header
#include "SysTick.h"
#include "gp_drive.h"
#include "i2c_drive.h"

char data[2] = {0x01, 0x02};
int main()
{
	SysTick_init();
	i2c_init(2, I2C_FM);
	
	while(1)
	{
		I2C_write(2, 0x78, data);
		Systick_DelayMs(10);
	}
		
}
