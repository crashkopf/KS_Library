
#include <stdio.h>
#include <avr/pgmspace.h>

#include "debug.h"

#ifndef NODEBUG

#include "usart0.h"

FILE debug = FDEV_SETUP_STREAM(usart0_putc, usart0_getc, _FDEV_SETUP_RW);

#endif /* NODEBUG */
