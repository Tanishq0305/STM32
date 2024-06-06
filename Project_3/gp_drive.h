#define RCC_APB2ENR (*((volatile unsigned long * )0x40021018)) //Allocated Value to variable of RCC register
	
#define GPIO_A 			(*((volatile unsigned long * )0x40010800)) //Allocated Registers of corresponding GPIO to variables
#define GPIO_B 			(*((volatile unsigned long * )0x40010C00))
#define GPIO_C 			(*((volatile unsigned long * )0x40011000))

//Ports
#define PA 1 // Options for port as port A,B,C
#define PB 2
#define PC 3

//Directions
#define IN 0	 // Options for dir as Input, Output with 10MHz/ 2MHz/ 5MHz
#define OUT10 1
#define OUT2  2
#define OUT50  3

//Direction Options for input
#define I_AN 0
#define IF   1
#define IPP  2

//Direction Options for input
#define O_GP_PP 0 //Push-pull
#define O_GP_OD 1 //OPen-Drain
#define O_AF_PP 2 //Aleternative function Pushpull
#define O_AF_OD 3 //Aletrnative function Open Drain

//State
#define LOW 0
#define HIGH 1

void init_GP(unsigned short port, unsigned short pin, unsigned short dir, unsigned short opt);

int R_GP(unsigned short port, unsigned short pin);
void W_GP(unsigned short port, unsigned short pin, unsigned short state);

void toggle_GP(unsigned short port, unsigned short pin);