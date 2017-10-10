#include <stdio.h>
#include <avr/pgmspace.h>

#define display(string, ...) fprintf_P(&display, PSTR(string), ##__VA_ARGS__)

extern FILE display;

void display_init(void);

int display_putchar(char c, FILE *stream);

void display_RC(unsigned char r, unsigned char c);
