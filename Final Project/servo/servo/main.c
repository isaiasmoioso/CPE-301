// #define F_CPU 8000000UL					//XTAL = 8MHZ
// #include <avr/io.h>
// #include <util/delay.h>
// void Wait()
// {
// 	int i;
// 	for(i=0;i<50;i++)
// 	{
// 		_delay_loop_2(0);
// 		_delay_loop_2(0);
// 		_delay_loop_2(0);
// 	}
// }
// int main()
// {
// 	//FOR TIMER1
// 	TCCR1A|=(1<<COM1A1)|(1<<WGM11)|(1<<COM1B1);        //NON Inverted PWM
// 	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)
// 	ICR1=2499;  //fPWM=50Hz...fpwm=50=8MHz/N(Top+1) --> Top=8MHz/(50Hz*64) -1=2,499
// 
// 	DDRB |=(1<<PORTB1);	   //PWM Pins as Output
// 	DDRB |=(1<<PORTB2);
// 
// 
// 	while(1)
// 	{
// 	
// 		OCR1B=67;   //0 degree 50 is min, with 300 when decrementing 25
// 		Wait();
// 		OCR1B=270;   //0 degree 50 is min, with 300 when decrementing 25
// 		//Wait();
// 		OCR1A=174;  //90 degree - neutral is 1.5ms 15000/8=187.5
// 		Wait();
// 		//35 to 125
// 		OCR1A=98;   //35 degree 581/8=72.6
// 		Wait();
// 
// 	}
// }
#define F_CPU 8000000UL					//XTAL = 8MHZ
#include <avr/io.h>
#include <util/delay.h>
void Wait()
{
	int i;
	for(i=0;i<50;i++)
	{
		_delay_loop_2(0);
		_delay_loop_2(0);
		_delay_loop_2(0);
	}
}
int main()
{
	//FOR TIMER1
	TCCR0A|=(1<<COM0A1)|(1<<WGM01)|(1<<WGM00)|(1<<COM0B1) |(1<<COM0A1);        //NON Inverted PWM
	TCCR0B|=(1<<CS01)|(1<<CS00); //PRESCALER=64 MODE 14(FAST PWM)
	//ICR1=2499;  //fPWM=50Hz...fpwm=50=8MHz/N(Top+1) --> Top=8MHz/(50Hz*64) -1=2,499

	DDRD |=(1<<PORTD6);	   //PWM Pins as Output
	DDRD |=(1<<PORTD5);


	while(1)
	{
		
// 		OCR0B=67;   //0 degree 50 is min, with 300 when decrementing 25
// 		Wait();
// 		OCR0B=65;   //0 degree 50 is min, with 300 when decrementing 25
// 		Wait();
		OCR0B=120;   //0 degree 50 is min, with 300 when decrementing 25
		Wait();
		OCR0B=170;   //0 degree 50 is min, with 300 when decrementing 25
		Wait();
		OCR0B=228;   //0 degree 50 is min, with 300 when decrementing 25
		Wait();
		
		OCR0A=110;   //0 degree 50 is min, with 300 when decrementing 25
		Wait();
		OCR0A=150;   //0 degree 50 is min, with 300 when decrementing 25
		Wait();
		OCR0A=200;   //0 degree 50 is min, with 300 when decrementing 25
		Wait();

		//OCR0B=75;   //0 degree 50 is min, with 300 when decrementing 25
		//Wait();
// 		OCR0A=174;  //90 degree - neutral is 1.5ms 15000/8=187.5
// 		Wait();
		//35 to 125
// 		OCR0A=98;   //35 degree 581/8=72.6
// 		Wait();

	}
}
