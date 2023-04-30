/*
 * Lab3.c
 *
 * Created: 30.04.2023 12:27:36
 * Author:	Daniil Grammatikopulo 
 * Student code: st79101
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>


int main(void)
{	
	// Enable DDRB to output mode and turn off LEDs
    DDRB = 0xFF; 
    PORTB = 0xFF;

	// Set up Timer 1 with a prescaler of 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);
	// Enable Timer 1 overflow interrupt
    TIMSK1|= (1 << TOIE1);
	
	// Set initial value of Timer 1 counter to 57723 
	// TCNT1 = 65535 - F_CPU / 1024
    TCNT1 = 57723;
	
	// Enable global interrupt
	sei();
	
    while (1)  {}
}

// Interrupt service routine for Timer 1 overflow
ISR(TIMER1_OVF_vect) {
	// If PORTB shows 12 in binary code, turn off LEDs
	if (PORTB == 0xF3) 
		PORTB = 0xFF;	
	// Increase number by 1 for each occurrence of timer overflow
	else 
		PORTB = ~(~PORTB + 1);
	// Set initial value of Timer 1 counter to 57723
	TCNT1 = 57723;
}
