#define F_CPU 8000000UL 
#include <avr/interrupt.h>

// Define the macro to check if a button is pressed
#define ISPRESSED(n) (~PIND & ( 1 << n ))

// Declare global variables
volatile uint16_t pressed_buttons = 0xFF;	// Initialize to all buttons not pressed
volatile uint16_t press_count = 0;	// Keep track of button presses

// The main function
int main(void) {
	
	// Set Port D as input and enable internal pull-up resistors
	DDRD = 0x00;
	PORTD = 0xFF;

	// Set Port B as output and initialize all pins to high (LEDs off)
	DDRB = 0xFF;
	PORTB = 0xFF;
	
	// Enable Pin Change Interrupt for Port D (PCINT16 to PCINT23)
	PCICR |= (1 << PCIE2);
	PCMSK2 = 0xFF; // Enable interrupt on all pins of Port D
	sei();	// Enable global interrupts

	while (1) {}	// Infinite Loop
}

// Interrupt Service Routine for Pin Change Interrupt on Port D
ISR(PCINT2_vect)
{
	// Check if PD0 (button 1) is pressed
	if(ISPRESSED(PD0)) {
		press_count++;	// Increment button press counter
		
		// If the button has been pressed an even number of times, turn on the LEDs according to the previous button state
		if (press_count % 2 == 0) 
			PORTB = pressed_buttons;
		else {
			pressed_buttons = 0xFF; // Forget all pressed buttons
			PORTB = 0xFF;	// Turn off all LEDs
		}
	}
	// Check if any other button is pressed (PD1 to PD7)
	if ((PIND & 0xFE) != 0xFE)
		pressed_buttons &= PIND;	// Update the button state
}
