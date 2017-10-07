#include <avr/io.h>

#include "fet.h"

void fet_init() {
	PORTE &= ~0x38;
	DDRE |= 0x38;   // fet0, fet1, fet2

	PORTH &= ~0x38; // fet3, fet4, fet5
	DDRH |= 0x38;

	PORTL &= ~0x18; // fet6, fet7
	DDRL |= 0x18;
}
