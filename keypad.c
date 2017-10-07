#include <avr/io.h>
#include "keypad.h"

#define PBIT(n) (1 << (n))  // Set a single bit
#define NBIT(n) (0x0f ^ PBIT(n))  // Clear a single bit, but keep the rest set (low nibble)
#define SCAN(n) {PORTA |= NBIT(n); PORTA &= ~PBIT(n); DDRA &= ~NBIT(n); DDRA |= PBIT(n); }
#define NOSCAN { PORTA |= 0x0f; DDRA &= ~0x0f; }  // Set all bits in lower nibble; clear all bit in lower nibble of DDR

#define NKEYS (16)
#define NSAMPLES (3)
/*
PA0 - SCAN0
PA1 - SCAN1
PA2 - SCAN2
PA3 - SCAN3
PA4 - KEY0
PA5 - KEY1
PA6 - KEY2
PA7 - KEY3
*/

void keypad_reset(void);

unsigned short _state;	// The debounced state of all keys, as a bit-map.
unsigned short _changes;	// A bit mask denoting transitions since the last read
unsigned short _samples[NSAMPLES];

void keypad_init(void) {
	keypad_reset();
}

void keypad_reset(void) {
	PORTA = 0xf0;	// Makse sure all key pins are set for input
	DDRA = 0x0f;	// key0 - key3 are inputs with pullup
}

unsigned short keypad_scan(void) {
	unsigned char i;
	unsigned short keys = 0;
	keypad_reset();  // This fixes a bug where keys aren't read after the display is cleared.
	for (i=0; i<4; i++) {
		SCAN(i);
		// Read a nybble and store it
		keys += ((PINA & 0xf0) >> 4) << (4 * i);
	}
	NOSCAN;
	return ~keys; // Invert keys before returning.
}

void keypad_update(void) {
	int j;
	unsigned short keys_on;
	unsigned short keys_off;
	unsigned short new_state;

	// Shift samples down by 1
	if (NSAMPLES > 1) {
		for (j=(NSAMPLES - 1); j > 0; j--) {
			_samples[j] = _samples[j-1];
		}
	}

	// Store the latest sample at the head
	_samples[0] = keypad_scan();

	// Iterate through the sample array ANDing each sample
	// Only bits with a steady state will be 1
	keys_on = ~0;
	keys_off = ~0;
	for (j=0; j < NSAMPLES; j++) {
		keys_on &= _samples[j];
		keys_off &= ~_samples[j];
	}

	// We now have two variables:
	//  * key_on where every bit that is 1 in all samples is 1
	//  * keys_off where every bit that is 0 in all samples is 1
	// We can then use these two as bitmasks to set and clear bits in the key state map
	new_state = (_state | keys_on) & ~keys_off;

	// XOR the new state with the previous to get any transitions.
	// OR with the change mask so previous changes aren't lost.
	_changes |= _state ^ new_state;

	_state = new_state;
}

unsigned short get_keys(void) {
	unsigned short k = _state & _changes;
	_changes = 0;
	return k;
}
