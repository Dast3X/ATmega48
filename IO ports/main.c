#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define UPPER_BOUND 7000 // Setting max value for delay
#define LOWER_BOUND 200	 // Setting min value for delay
#define LED PORTB
#define ISPRESSED(n) (~PIND & ( 1 << n ))	// Macro for checking whether button is pressed
// Macro for decreasing/increasing delay
#define CHANGE_TIME	if (ISPRESSED(5)) {decrease_ms(&ms); continue;} if (ISPRESSED(1)) {increase_ms(&ms); continue;}

// Function to delay for a given number of ms
void delay(uint16_t ms){
	while(ms--)	_delay_ms(1); // Delay for 1ms at a time
}

// Function to increase the delay time by 1000ms
void increase_ms(uint16_t* ms) {
	while (ISPRESSED(1));	// Wait for SW1 to be released
	if (*ms + 1000 >= UPPER_BOUND)	// If the new delay time would be above the upper bound, set it to the upper bound
		*ms = UPPER_BOUND;	// Assign to 7000ms
	else
		*ms += 1000;	// Otherwise, increase the delay by 1000ms
}

// Function to decrease the delay time by 300ms
void decrease_ms(uint16_t* ms) {
	while (ISPRESSED(5));	// Wait for switch 5 to be released
	if (*ms <= LOWER_BOUND+300) // if to avoid the overflow problem of uint16_t type, in case of negative 'ms'
		*ms = LOWER_BOUND;	// Assign to 200ms
	else if (*ms - 300 <= LOWER_BOUND)	// If decreasing the delay time would be below the lower bound, set it to the lower bound
		*ms = LOWER_BOUND;	// Assign to 200ms
	else
		*ms -= 300; // Otherwise, decrease the delay by 300ms
}

int main(void)
{
	CLKPR = (1 << CLKPCE); // Set the clock prescaler to divide by 1
	CLKPR = 0;
	
	DDRB = 0xFF;	// Set 6th LED as output
	DDRD = 0x00;	// Set PORTD as input
	PORTD = 0x22;	// enable pull-up resistors for SW1 & SW5
	uint16_t ms = 500;	// Set initial delay to 500ms
	LED = 0xFF;
	while (1)	// Infinite loop
	{
		CHANGE_TIME	// Check for button presses during delay time
		LED = 0xBF;	// Turn on the 6th LED
		CHANGE_TIME	// Check for button presses during delay time
		delay(ms);	// Delay for the specified amount of time
		CHANGE_TIME	// Check for button presses during delay time
		LED = 0xFF;	// Turn off the 6th LED
		CHANGE_TIME	// Check for button presses during delay time
		delay(ms);	// Delay for the specified amount of time
		CHANGE_TIME	// Check for button presses during delay time
	}
}