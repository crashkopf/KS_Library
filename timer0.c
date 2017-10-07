#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer0.h"

volatile unsigned long _systime;

unsigned long systime() {
	unsigned long t;
	cli();
	t = _systime;
	sei();
	return t;
}

void timer0_init() {
	// Set output compare registers
	OCR0A = 250;
	OCR0B = 0;

	// Turn on the compare match interrupt
	TIMSK0 = _BV(OCIE0A);

	TCCR0A =
		_BV(WGM01) |
		0; // Clear on OCR match

	TCCR0B =
		_BV(CS00) |
		_BV(CS01) |
//		_BV(CS02) |
		0; // Divide by 64
}

ISR(TIMER0_COMPA_vect) {
	_systime++;
}
