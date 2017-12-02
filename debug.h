#include <stdio.h>
#include <avr/pgmspace.h>

#define debug(string, ...) fprintf_P(&debug, PSTR(string), ##__VA_ARGS__)

#ifndef NODEBUG

extern FILE debug;

#endif /* NODEBUG */
