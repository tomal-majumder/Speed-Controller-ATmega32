/*
 * GccApplication3.c
 *
 * Created: 12/4/2017 12:42:11 AM
 *  Author: Asus
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif


#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"
volatile int count=0;    //Main revolution counter

volatile int rpm=0;   //Revolution per minute

volatile int rps=0;   //Revolution per second
char str[100];

ISR(INT0_vect)//STEP2
{
	//PORTB = ~PORTB;
	count++;
}

ISR(INT1_vect)//STEP2
{
	//PORTB = ~PORTB;
	OCR0-=60;
}

ISR(TIMER1_COMPA_vect) { // this function is called every time the timer reaches the threshold we set

	//PORTB=~PORTB; // toggle the LED
	rps=count;
	rpm=rps*60;
	count=0;
}

int main(void)
{
	int i,steps,a,b,intres;
	
	float result;
	
	DDRD=0xF0;
	DDRC=0xFF;
	DDRB=0xFF;
	Lcd4_Init();
	
	ADMUX=0b01000000;
	ADCSRA=0b10001010;
	
	PORTB = 0b00000000;
	PORTC=0b00000010;
	TCCR1B|=((1<<WGM12)|(1<<CS12)|(1<<CS10));
	TCCR0=0b01110010;

	TIMSK |= (1 << OCIE1A); // enable the CTC interrupt

	OCR1A   = 961; // set the CTC compare value
    OCR0= 230;
	//GICR = (1<<INT0); //STEP3
	GICR = (1<<INT1) | (1<<INT0);
	MCUCR = 0b11111110;//STEP4
	sei();
    while(1)
    {
        //TODO:: Please write your application code 
		int ll;
		ADMUX=0b01000000;
		ADCSRA=0b10000010;
		
		ADCSRA |= (1<<ADSC);
		
		while (ADCSRA & (1<<ADSC));

		ll =ADCL;
		steps=(ADCH & 3)<<8 | ll ;
		ADCH = 0;
		ADCL = 0;
		
		result=((float)steps*500)/1024;
		
		intres = (int) result;
		
		for(i=3;i>=0;i--){
			if(i==1){
				str[i]='.';
				continue;
			}
			str[i]=(intres%10)+48;
			//Lcd4_Write_Char('a');
			intres=intres/10;
		}
		
		
		//Lcd4_Clear();
		if(rpm>0) PORTB=0b00000001;
		else PORTB=0b00000010;
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String(str);
		char str2[100];
		sprintf(str2,"%d", rpm);
		Lcd4_Set_Cursor(2,1);
		Lcd4_Write_String(str2);
		//polling();
		//_delay_ms(500);
		if(rpm>380) OCR0=230;
    }
}