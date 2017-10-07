#include <avr/interrupt.h>

#include <stdio.h>

#include "kitchensink.h"

FILE display = FDEV_SETUP_STREAM(display_putchar, NULL, _FDEV_SETUP_WRITE);

void KS_init() {
	// Initialize system timer
	timer0_init();

	// Initialize PWM timer
	timer1_init();

	// Set up PWM pins outputs
	DDRB |= _BV(DDB5) | _BV(DDB6) | _BV(DDB7);

	// Initialize ADC
	adc_init();

	display_init();
	keypad_init();
	fet_init();

	// Enable LED output
	DDRJ |= _BV(DDJ7);

	// Enable interrupts
	sei();
}
