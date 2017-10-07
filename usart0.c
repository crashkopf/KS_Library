/*
  serio.c
*/
#include <avr/io.h>
#include <avr/interrupt.h>

#include "usart0.h"

#ifndef F_CPU
#define F_CPU 16000000
#endif

#ifndef BAUD_TOL
#define BAUD_TOL 2
#endif

void usart0_init(unsigned long, unsigned char);
void _setbaud(unsigned long);
static inline void _txstart(void);
static inline void _txstop(void);
static inline void _rxstart(void);
static inline void _rxstop(void);

void (*_txcomplete)(char *);

char * buffer;
unsigned char length;
unsigned char position;

void usart0_init(unsigned long baud, unsigned char framedef) {
	(void) framedef;

	_setbaud(baud);

	UCSR0B = 0;
	// Set framing, 8N1
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);

	// Enable RX/TX pins
	UCSR0B |= _BV(TXEN0) | _BV(RXEN0);

	// enable interrupts
	_rxstart();
}

void usart0_send(char * b, unsigned long l, void (*cb)(char *)) {
	buffer = b;
	length = l;
	_txcomplete = cb;
	position = 0;
	_txstart();
}

void _setbaud(unsigned long baud) {
	int use2x;
	unsigned long div;

	div = (((F_CPU) + 8UL * (baud)) / (16UL * (baud)) - 1UL);

	if (100 * (F_CPU) > (16 * ((div) + 1)) * (100 * (baud) + (baud) * (BAUD_TOL)))
		use2x=1;
	else if (100 * (F_CPU) < (16 * ((div) + 1)) * (100 * (baud) - (baud) * (BAUD_TOL)))
		use2x = 1;
	else
		use2x=0;

	if (use2x) {
		UCSR0A = _BV(U2X2);             /* improve baud rate error by using 2x clk */
		UBRR0 = (F_CPU / (8UL * baud)) - 1;
	}
	else
		UBRR0 = (F_CPU / (16UL * baud)) - 1;
}

static inline void _txstart() {
	UCSR0B |= _BV(UDRIE0);		// Turn on UDR empty interrupt
}
static inline void _txstop() {
	UCSR0B &= ~(_BV(UDRIE0));	// Turn off UDR empty interrupt
}
static inline void _rxstart() {
	UCSR0B |= _BV(RXCIE0);		// Turn on RX complete interrupt
}
static inline void _rxstop() {
	UCSR0B &= ~(_BV(RXCIE0));	// Turn off RX complete interrupt
}

// USART2 interrupt handlers
ISR(USART0_RX_vect) {
	char c = UDR0; // Always read from UDR, otherwise the interrupt will keep firing
	(void) c;
//	writeb(&_rdbuf, &c, 1);
}

ISR(USART0_TX_vect) {

}

ISR(USART0_UDRE_vect) {
	if (buffer && (position < length)) {
		UDR0 = buffer[position];
		position++;
	}
	else {
		_txstop();
		if (_txcomplete) _txcomplete(buffer);
	}
}
