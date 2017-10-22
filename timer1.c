#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer1.h"

void timer1_init(void) {
	// Clear ouput compare registers
	OCR1A = 0;
	OCR1B = 0;
	OCR1C = 0;

	TCCR1A =
		_BV(WGM10) | // Phase correct, 10-bit PWM
		_BV(WGM11) |
		0;

	TCCR1B = 0;
	timer1_source(TIMER1_INT);

	TCCR1C = 0;
}

void timer1_source(enum timer1_clock_source cs) { TCCR1B = (TCCR1B & 0xF8) | cs; };

void OC1A_enable() { TCCR1A |= _BV(COM1A1); }
void OC1A_disable() { TCCR1A &= ~(_BV(COM1A1)); }
void OC1B_enable() { TCCR1A |= _BV(COM1B1); }
void OC1B_disable() { TCCR1A &= ~(_BV(COM1B1)); }
void OC1C_enable() { TCCR1A |= _BV(COM1C1); }
void OC1C_disable() { TCCR1A &= ~(_BV(COM1C1)); }
