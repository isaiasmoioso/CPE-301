/*
 * DA-4.c
 *
 * Created: 4/10/2016 3:11:05 PM
 * Author : Isaias Osorio
 */ 
#define F_CPU 8000000UL // frequency for delay functions

#include <util/delay.h> // library for _delay_ms() function
#include <avr/io.h> // library for I/O

void delay (); // function declaration for delay

int main(void)
{
	unsigned char i = 230, j=230, k=230;// initialize to 230 for 10% value of 255
	unsigned char counter2 = 0, counter3 = 0; 
	// two variables to update 2nd and 3rd PWMs counters
	
	DDRD = 0x40;		// OC0A	
	DDRB = 0x0A;		// OC1A and OC2A

	OCR0A = 230;		// 230 is 10% value of 255 when decrementing
	TCCR0A = 0xC1;		// Phase Correct PWM, inverted
	TCCR0B = 0x03;		// N = 64
	OCR1A = 230;		// 230 is 10% value of 255 when decrementing
	TCCR1A = 0xC1;		// Phase Correct PWM, inverted
	TCCR1B = 0x03;		// N = 64
	OCR2A = 230;		// 230 is 10% value of 255 when decrementing
	TCCR2A = 0xC1;		// Phase Correct PWM, inverted
	TCCR2B = 0x04;		// N = 64
	
    while (1) // loop forever
    {
		
		OCR0A = i;		// update 3 PWM values at beginning of each loop
		OCR1A = j;		// from delay of 40ms
		OCR2A = k;
		
		counter2++;		// increment counter for 2nd PWM every time 1st is updated
		i -= 5;		// increase duty cycle of PWM1 by 10%
		if(i < 30)		// if duty cycle is more than 90% (inverted)
			i = 230;	// reset duty cycle back to 10%
		if(counter2 >= 9) 
		{				// if PWM1 reset duty cycle
			counter2 = 0; // clear counter for PWM2
			counter3++; // increment counter for PWM3
			j -= 25;	// increase duty cycle of PWM2 by 10%
			if(j < 30)	// if duty cycle is more than 90% (inverted)
				j = 230; // reset duty cycle back to 10%
		}
		if(counter3 >= 9) 
		{				// if PWM2 reset duty cycle
			counter3 = 0;// clear counter for PWM3
			k-=5;		// increase duty cycle of PWM3 by 10%
			if(k < 30)	// if duty cycle is more than 90% (inverted)
				k = 230;// reset duty cycle back to 10%
		}
		_delay_ms(40);	// delay for 40ms
	}
	return 0;
}
