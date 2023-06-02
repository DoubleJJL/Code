#ifndef PRINTSCANF_H
#define PRINTSCANF_H
/****************************************************************************
	Include Files
****************************************************************************/
#include <avr/io.h>
#include <stdio.h>
/****************************************************************************
	Function definitions
****************************************************************************/
int getch(void);
int putch_uart0(char message, FILE *stream);
int getch_uart0(FILE *stream);
int putch_uart1(char message, FILE *stream);
int getch_uart1(FILE *stream);
void setUBRR(int num, long int baudrate);
void initUART(int num, long int baudrate);

#endif