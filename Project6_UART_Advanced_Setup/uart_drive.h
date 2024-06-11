unsigned long USART_BRR(unsigned short usart, unsigned long BR);
void USART_init(unsigned short usart, unsigned long BR);
char USART_RX(unsigned short usart);
void USART_TX(unsigned short usart, char c);
void USART_ISR(unsigned short uart, unsigned short uart_mgr[], char str[]);
void UART_SEND(unsigned short uart, char str[]); //Function Prototype
void str_empty(char str[]);