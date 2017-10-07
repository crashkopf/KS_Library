#include <stdio.h>
#include <avr/pgmspace.h>

#define debug(fmt, ...) _debug(PSTR(fmt), ##__VA_ARGS__)

void _debug(const char *, ...);
