#include <avr/io.h>
#include <stdint.h>

#include "adc.h"

// set MUXA / MUXB pins to correct bank
#define ADC_SETBANK(n) {PORTL = (PORTL & ~0xc0) | ((n) << 6);}


void adc_init() {
	DDRL |= 0xc0;    // MUXA and MUXB are outputs
	PORTL = (PORTL & ~0xc0) | (0 << 6);  // bank number for external MUX

	ADMUX = 0x40;    // AVCC is AREF
	ADCSRA |= 0x80;  // enable ADC
	ADCSRA |= 0x07;  // prescale by 128

	DIDR0 = 0x0f;    // disable digital inputs, ADC0 - ADC3
	DIDR2 = 0xff;    // disable digital inputs, ADC8 - ADC15
}

unsigned adc_read(unsigned chan) {

	if (chan >= 8) {
		ADCSRB |= 0x08;  // MUX high channels (8 - 15)
	} else {
		ADCSRB &= ~0x08; // MUX low channels (0 - 7)
	}

	ADMUX = (ADMUX & ~0x1f) | (chan & 0x07);  // MUX channel number

	ADCSRA |= 0x40;  // start conversion
	while (ADCSRA & 0x40) ;   // wait for conversion to complete

	return ADC;
}
