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
	TCCR1A|=(1<<COM1A1)|(1<<WGM11);        //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)
	ICR1=2499;  //fPWM=50Hz...fpwm=50=8MHz/N(Top+1) --> Top=8MHz/(50Hz*64) -1=2,499

	DDRB |=(1<<PORTB1);	   //PWM Pins as Output

	//int value=300;//MAX 180

	while(1)
	{
		// OCR1A=value; //
		//_delay_ms(600);
		//value=value-25; //1.38 ms per degree
		OCR1A=50;   //0 degree 50 is min, with 300 when decrementing 25
		Wait();
		OCR1A=174;  //90 degree - neutral is 1.5ms 15000/8=187.5
		Wait();
		//35 to 125
		OCR1A=98;   //35 degree 581/8=72.6
		Wait();
		OCR1A=223;  //125 degrees. 73-49=24, thus 24+188=212
		Wait();
		//180 to 0
		OCR1A=300;  //180 degree 2,140/8=268
		Wait();
		OCR1A=50;   //0 degree 388/8=49
		Wait();//0 degree*/
	}
}