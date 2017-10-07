#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer1.h"

void timer1_init() {
	// Clear ouput compare registers
	OCR1A = 0;
	OCR1B = 0;
	OCR1C = 0;

	// Turn on the overflow interrupt
	//TIMSK1 = _BV(TOIE1);

	TCCR1A =
		_BV(WGM10) | // Phase correct, 10-bit PWM
		_BV(WGM11) |
		0;

	TCCR1B =
		_BV(CS10) |
		//_BV(CS11) |
		//_BV(CS12) |
		0; // Divide by 1

	TCCR1C = 0;
}

void OC1A_enable() { TCCR1A |= _BV(COM1A1); }
void OC1A_disable() { TCCR1A &= ~(_BV(COM1A1)); }
void OC1B_enable() { TCCR1A |= _BV(COM1B1); }
void OC1B_disable() { TCCR1A &= ~(_BV(COM1B1)); }
void OC1C_enable() { TCCR1A |= _BV(COM1C1); }
void OC1C_disable() { TCCR1A &= ~(_BV(COM1C1)); }

ISR(TIMER1_OVF_vect, ISR_NAKED) {
	// Don't do anything...
	asm volatile (
		"reti\n\t"
		::
	);
}
