// /*
//  * pan_tilt.c
//  *
//  * Created: 2023-05-26 오후 12:44:51
//  * Author : user
//  */ 
// 
// #include <avr/io.h>
// #include <util/delay.h>
// #include <string.h>
// #include "printscanf.h"
// 
// int check_digit(void);
// void reset_str(void);
// 
// char str[10];
// 
// int main(void)
// {
//     initUART(0, 115200);
// 	/*printf("ffffffaaaaaa\r\n");*/
// 	DDRB |= (1 << PB5);
// 	DDRB |= (1 << PB6);
// 	TCCR1A = 0xa2;
// 	TCCR1B |= 0x1b;	
// 	ICR1 = 5000-1;
// 	OCR1A = 200;
// 	OCR1B = 375;
// /*	int i = 0;*/
// 
// 	char *ptr1_str;
// 	char *ptr2_str;
// 	int digits;
// 	int pos_pan=400;
// 	int pos_tilt=200;
// 	
// 	
// 	
//     while (1) 
//     {
// 		scanf("%s" , str);
// 		//printf("%s\r\n", str);
// 		
// // 		i=0;
// // 		
// // 		while(str[i] != '\0'){
// // 			i++;
// // 		}
// 
// 					
// 		ptr1_str = strstr(str, "pan");
// 		ptr2_str = strstr(str, "tilt");
// 		 
// 		if(ptr1_str!= NULL)
// 		{
// 			//printf("pan include\r\n");
// 			
// 			digits = check_digit();
// 			//printf("digit : %d\r\n", digits);
// 			if(digits ==3)
// 			{
// 				pos_pan = (str[3]-'0')*100 +(str[4]-'0')*10 + (str[5]-'0');
// 			}
// 			else if(digits == 2)
// 			{
// 				pos_pan = (str[3]-'0')*10 +(str[4]-'0');
// 			}
// 			else if(digits == 1)
// 			{
// 				pos_pan = (str[3]-'0');
// 			}
// 			
// 			//printf("pos_pan : %d\r\n", pos_pan);
// 			reset_str();
// 			
// 		}
// 		else;
// 		
// 		if(ptr2_str != NULL)
// 		{
// 			//printf("title include\r\n");
// 			
// 			digits = check_digit();
// 			//printf("digit : %d\r\n", digits);
// 			
// 			if(digits ==3)
// 			{
// 				pos_tilt = (str[4]-'0')*100 +(str[5]-'0')*10 + (str[6]-'0');
// 			}
// 			else if(digits ==2)
// 			{
// 				pos_tilt = (str[4]-'0')*10 +(str[5]-'0');
// 			}
// 			else if(digits ==1)
// 			{
// 				pos_tilt = (str[4]-'0');
// 			}
// 			
// 			//printf("pos_tilt : %d\r\n", pos_tilt);
// 			reset_str();
// 		}
// 		else;
// 			OCR1A = pos_tilt;
// 			_delay_ms(10);
// 			OCR1B = pos_pan;
// 			_delay_ms(10);
//     }
// 	
// 
// }
// 
// int check_digit()
// {
// 	int i, cnt;
// 	cnt = 0;
// 	for(i=0; i<sizeof(str); i++)
// 	{
// 		if(str[i]>='0' && str[i]<='9')
// 		{
// 			cnt++;
// 		}
// 	}
// 	return cnt;
// }
// 
// void reset_str(void)
// {
// 	
// 	for(int i=0; i<sizeof(str); i++)
// 	{
// 		str[i] = '\0';
// 	}
// 	
// }
// 
// 

/*
 * pantilit2.c
 *
 * Created: 2023-05-30 오전 11:24:21
 * Author : user
 */ 

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include "printscanf.h"

int check_digit(void);
void reset_str(void);

char str[10];

int main(void)
{
    initUART(0, 115200);
	reset_str();
	printf("control pan tilt\r\n");

	char *ptr1_str;
	char *ptr2_str;
	int digits=0;
	int pos_pan = 350;
	int pos_tilt=200;
	_delay_ms(1);
	DDRB |= 1<<PB6;	// 1000 0000 PWM 출력: OC1A --- PB5 OC1B = PB4
	DDRB |= 1<<PB5;
	TCCR1A=0xa2; // COM1A[1:0]="10", OC1A핀사용, OC1B핀 사용  WGM1(1:0)="10"
	//				+--------+--------+--------+--------+--------+--------+--------+--------+
	//				| COM1A1 | COM1A0 | COM1B1 | COM1B0 | COM1C1 | COM1C0 | WGM1 1 | WGM1 0 |
	//				+--------+--------+--------+--------+--------+--------+--------+--------+
	//				|    1   |    0   |   1    |    0   |    0   |    0   |    1   |    0   |
	//				+--------+--------+--------+--------+--------+--------+--------+--------+
	TCCR1B |= 0x1b; // WGM3(3:2)="11", CS3(2:0)="011" 64분주 사용
	//				+--------+--------+--------+--------+--------+--------+--------+--------+
	//				| ICNC1  | ICES1  |    -   | WGM1 3 | WGM1 2 |  CS1 2 |  CS1 1 |  CS1 0 |
	//				+--------+--------+--------+--------+--------+--------+--------+--------+
	//				|    0   |    0   |    -   |    1   |    1   |    0   |    1   |    1   |
	//				+--------+--------+--------+--------+--------+--------+--------+--------+
	TCCR1C  = 0x00;  // WGM3(3:0)="1110", Fast PWM, 모드 14
	//				+--------+--------+--------+--------+--------+--------+--------+--------+
	//				| ICNC1  | ICES1  |    -   | WGM1 3 | WGM1 2 |  CS1 2 |  CS1 1 |  CS1 0 |
	//				+--------+--------+--------+--------+--------+--------+--------+--------+
	//				|    0   |    0   |    -   |    1   |    1   |    0   |    0   |    1   |
	//				+--------+--------+--------+--------+--------+--------+--------+--------+
	TCNT1   = 0x0000; // 타이머1 카운터 초기화
	ICR1=4999;
	OCR1A=350;
	OCR1B=200;
    while (1) 
    {
		//scanf("%s" , str);					// 입력
		fgets(str, sizeof(str),stdin);				//입력받은 문자열 출력 

		ptr1_str = strstr(str, "pan");			// 검사하는 역할 strstr str문자열 안에 pan이 있는지 검사 
		ptr2_str = strstr(str, "tilt");			// tilt를 포함했는지 파악 
		 
		if(ptr1_str!= NULL)						// pan을 포함하고 있냐? str이 null 이 아니라는것은 str has pan  
		{
			printf("pan include\r\n");
			
			digits = check_digit();				// 몇자리 숫자가 들어왔는지 
			printf("digit : %d\r\n", digits);
			if(digits ==3)
			{
				pos_pan = (str[3]-'0')*100 +(str[4]-'0')*10 + (str[5]-'0');		// str[3]-'0' 숫자에서 0에 해당하는 아스키를 빼서 진짜 숫자로 만듦 그래서 *100을 곱함 
			}
			else if(digits == 2)
			{
				pos_pan = (str[3]-'0')*10 +(str[4]-'0');
			}
			else if(digits == 1)
			{
				pos_pan = (str[3]-'0');
			}
			else;
			printf("pos_pan : %d\r\n", pos_pan);
			reset_str();
		
		}
		else;
		
		if(ptr2_str != NULL)
		{
			printf("title include\r\n");
			
			digits = check_digit();
			printf("digit : %d\r\n", digits);
			
			if(digits ==3)
			{
				pos_tilt = (str[4]-'0')*100 +(str[5]-'0')*10 + (str[6]-'0');
			}
			else if(digits ==2)
			{
				pos_tilt = (str[4]-'0')*10 +(str[5]-'0');
			}
			else if(digits ==1)
			{
				pos_tilt = (str[4]-'0');
			}
			else;
			printf("pos_tilt : %d\r\n", pos_tilt);
			reset_str();
			
		}
		else;
						OCR1A = pos_pan;
					/*	_delay_ms(1);*/
						OCR1B = pos_tilt;
					/*	_delay_ms(1);	*/
    }

}

int check_digit()
{
	int i, cnt;
	cnt = 0;
	for(i=0; i<sizeof(str); i++)
	{
		if(str[i]>='0' && str[i]<='9')
		{
			cnt++;
		}
	}
	return cnt;
}

void reset_str(void)
{
	
	for(int i=0; i<sizeof(str); i++)
	{
		str[i] = '\0';
	}
	
}


