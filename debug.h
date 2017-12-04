#include <stdio.h>
#include <avr/pgmspace.h>

#ifndef KSLIB_NODEBUG

#define debug(string, ...) fprintf_P(&debug, PSTR(string), ##__VA_ARGS__)

extern FILE debug;

#endif /* KSLIB_NODEBUG */
