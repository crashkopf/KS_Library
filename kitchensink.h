#include <avr/io.h>

#include "adc.h"
#include "fet.h"
#include "display.h"
#include "keypad.h"
#include "pressure.h"
#include "temperature.h"
#include "timer0.h"
#include "timer1.h"



void KS_init(void);

static inline void LED_ON(void) {PORTJ |= _BV(PJ7);}
static inline void LED_OFF(void) {PORTJ &= ~_BV(PJ7);}
static inline void LED_TOGGLE(void) {PORTJ ^= _BV(PJ7);}
