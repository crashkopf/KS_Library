/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <joerg@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Joerg Wunsch
 * ----------------------------------------------------------------------------
 *
 * Stdio demo, upper layer of LCD driver.
 *
 * $Id: lcd.c 2265 2011-12-28 21:28:29Z joerg_wunsch $
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>

#include <util/delay.h>

#include "hd44780.h"
#include "display.h"

unsigned char row, col;

void display_init(void) {
	hd44780_init();

	// Clear the display.
	hd44780_outcmd(HD44780_CLR);
	hd44780_wait_ready(true);

	// auto-increment address counter, no display shift
	hd44780_outcmd(HD44780_ENTMODE(1, 0));
	hd44780_wait_ready(false);

	// Enable display, blinking cursor.
	hd44780_outcmd(HD44780_DISPCTL(1, 0, 0));
	hd44780_wait_ready(false);

	row = 0;
	col = 0;
}


int display_putchar(char c, FILE *unused) {
	(void) unused;
	switch (c) {
		case (0x09):	// Tab
			break;
		case (0x0A):	// Line feed
			display_RC(++row, 0);
			break;
		case (0x0C):	// Form feed
			hd44780_wait_ready(false);
			hd44780_outcmd(HD44780_CLR);
			display_RC(0,0);
			//hd44780_wait_ready(false);
			//hd44780_outcmd(HD44780_HOME);
			//hd44780_wait_ready(true);
			//hd44780_outcmd(HD44780_DDADDR(0));
			break;
		case (0x0D):	// Carriage return
			display_RC(row, 0);
			break;
		default:
			col++;
			if (col > 20) display_RC(++row, 0);
			hd44780_wait_ready(false);
			hd44780_outdata(c);
			break;
	}
	return 0;
}

void display_RC(unsigned char r, unsigned char c) {
	unsigned char addr = 0;
	if (c > 19) c = 0;
	if (r > 3) r = 3;
	if (r & 0x01) addr += 64;
	if (r & 0x02) addr += 20;
	addr += c;
	hd44780_wait_ready(false);
	hd44780_outcmd(HD44780_DDADDR(addr));
	row = r;
	col = c;
}
