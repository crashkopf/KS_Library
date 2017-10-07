
#include <avr/io.h>


void usart0_init(unsigned long baud, unsigned char framedef);
int usart0_putc(char *);
int usart0_getc(char *);
void usart0_send(char *, unsigned long, void (*)(char *));
