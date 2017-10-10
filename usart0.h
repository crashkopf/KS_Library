
#include <avr/io.h>
#include <stdio.h>

void usart0_init(unsigned long baud, unsigned char framedef);
int usart0_putc(char c, FILE * f);
int usart0_getc(FILE * f);
void usart0_send(char *, unsigned long, void (*)(char *));
