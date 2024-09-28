#include<LPC214x.h>
void Uart0Init()
{
	PINSEL0=0x01;
	U0LCR=0x83;
	U0DLM=0x00;
	U0DLL=97;
	U0LCR=0x03;
}
unsigned char UART0_PutChar(unsigned char Ch)
{
	while(!(U0LSR & 0x20));
	U0THR=Ch;
	return Ch;
}
void UART0_PutS(unsigned char *Ch)
{
	while(*Ch)
	UART0_PutChar(*Ch++);
}
void delay(int time)
{
	unsigned int i,j;
	for (i=0;i<time;i++)
	for (j=0;j<5000; j++);
}
void call()
{
	Uart0Init();
	UART0_PutS("ATE0\r\n"); //Echo disable
	UART0_PutS("ATD4762620555;\r\n");
	UART0_PutS("ATH0\r");
	UART0_PutS("AT+CMGF=1\r\n");
	UART0_PutS("AT+CMGS=\"4762620555\"\r\n");
	UART0_PutS("ALERT !!!!There is a lpg leakage in this specified address\r");
	UART0_PutChar(0x1A);
}

