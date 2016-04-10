/* TASK 1 - C
 * DA2T1C.c
 *
 * Created: 3/13/2016 10:14:17 PM
 * Author : Isaias Osorio
 */ 
#define	F_CPU 8000000L	//8MHz clock
#include <avr/io.h>
#include <util/delay.h> //for the use of delays


int main(void)
{
    DDRC = (1<<PORTC0);
    
	while (1) 
    {
		_delay_ms(250);
		PORTC ^= 1<<PORTC0;
    }
}

