
#include <avr/io.h>

#include <stdio.h>
#include <string.h>

#include "debug.h"

#define BUFSIZE (96)

void _debug(const char * fmt, ...) {
	(void) fmt;
	return;
}
