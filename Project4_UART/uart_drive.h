unsigned long USART_BRR(unsigned short usart, unsigned long BR);
void USART_init(unsigned short usart, unsigned long BR);
char USART_RX(unsigned short usart);
void USART_TX(unsigned short usart, char c);