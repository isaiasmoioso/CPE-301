/*
 * DA2T2C.c
 *
 * Created: 3/13/2016 10:46:48 PM
 * Author : Isaias Osorio
 * TASK 2 - C
*/

#define	F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	unsigned char i = 0;			//count of rising edge cycles 
    unsigned char j = (1<<PORTC0);	//use to compare
	DDRB = 0xFF;
    
	while (1) 
    {
		_delay_ms(250);				// delay for 250us
		j ^= 1<<PORTC0;				// toggle
		if(j == 1)					// check if its rising edge
			i++;
		PORTB = i;					// output to port b the count i
    }
}

