// BAUD = CLK_sys / 16*(UBRR + 1)
// 16 x (UBRR + 1) = CLK_sys / BAUD
// UBRR = ( ( CLK_sys / BAUD ) - 16)16

#include "printscanf.h"

int getch(void)
{
	while((UCSR0A & 0x80) == 0x00);		//	while(!(UCSR0A & (1<<RXC0)));	Xxxx xxxx & 1000 0000 == 0
	return UDR0;											//	if( RXC0=0 ) wait.
}

int putch_uart0(char message, FILE *stream)	// For using printf()
{
	if (message == '\n')
		putch_uart0('\r', stream);		
	while((UCSR0A & 0x20) == 0x00);		
	UDR0 = message;						
	return 0;
}

int getch_uart0(FILE *stream)					// For using scanf()
{	
	while((UCSR0A & 0x80) == 0x00);
	return UDR0;
}

int putch_uart1(char message, FILE *stream)	// For using printf()
{
	if (message == '\n')
	putch_uart1('\r', stream);
	while((UCSR1A & 0x20) == 0x00);
	UDR1 = message;
	return 0;
}

int getch_uart1(FILE *stream)					// For using scanf()
{
	while((UCSR1A & 0x80) == 0x00);
	return UDR1;
}

void setUBRR(int num, long int baudrate)
{
	int UBRR;
	UBRR = F_CPU / (16 * baudrate);
	
	if(num == 0)
	{
		UBRR0H  = ( UBRR & 0xff00 ) >> 8;		// & 1111 1111 0000 0000 = xxxx xxxx 0000 0000
		UBRR0L  = UBRR & 0x00ff;				// & 0000 0000 1111 1111 = 0000 0000 xxxx xxxx
	}
	else if(num == 1)
	{
		UBRR1H  = ( UBRR & 0xff00 ) >> 8;		// & 1111 1111 0000 0000 = xxxx xxxx 0000 0000
		UBRR1L  = UBRR & 0x00ff;				// & 0000 0000 1111 1111 = 0000 0000 xxxx xxxx
	}
	else;
}

void initUART(int num, long int baudrate)
{
	if(num == 0)
	{
		UCSR0A = 0x00;		// UCSR0A = 0;							 0  0  0  0    0  0  0  0
		UCSR0B = 0x18;		// UCSR0B |= (1<<RXEN0) |(1<<TXEN0);  0  0  0  1       1  0  0  0
		UCSR0C = 0x06;		// UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);0  0  0  0        0  1  1  0
		setUBRR(num, baudrate);
		fdevopen(putch_uart0,getch_uart0);
	}
	else if(num == 1)
	{
		UCSR1A = 0x00;		// UCSR1A = 0;							 0  0  0  0    0  0  0  0
		UCSR1B = 0x18;		// UCSR1B |= (1<<RXEN1)|(1<<TXEN1);		 0  0  0  1    1  0  0  0
		UCSR1C = 0x06;		// UCSR1C |= (1<<UCSZ11)|(1<<UCSZ10);	 0  0  0  0    0  1  1  0
		setUBRR(num, baudrate);
		fdevopen(putch_uart1,getch_uart1);
	}
	else;
}