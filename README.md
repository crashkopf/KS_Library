KS_Library - Everything but the Kitchen Sink!
=============================================

  * ADC - Analog to digital conversion, channel multiplexing.
  * Debug - Messages to USB serial
  * Display - High-level display interface
  * FET - FET sink outputs
  * Graphs - Graph tiny data with the HD44780
  * HD44780 - Low-level commands to the display driver
  * Keypad - Scan 4x4 keypad.  Key debouncing and event queue.
  * Pressure - Conversion from ADC value to pressure.
  * Temperature - Conversion from ADC value to temperature.  Cold-point compensation.
  * Timer0 - System clock
  * Timer1 - Servo0, Servo1, Servo2
  * USART0 - USB Serial (57600, N-8-1)
  * USART1
  * USART2
  * USART3

Code Example
-------------
	#include "kitchensink.h"

	void main() {
		// Initialize Kitchen Sink hardware
		KS_init();

		// Main program loop...
		display("Peace among worlds!\n");
	}

Makefile Example
----------------
	###############################################################################
	# Makefile for the project AVR
	###############################################################################

	PROJECT=mayhem

	all: $(PROJECT).hex

	BOARDDIR = path/to/KS_Library
	include $(BOARDDIR)/profile.mk

	OBJECTS = \
		$(BOARDOBJS) \
		build/Main.o \

	## Main build section
	.PHONY: clean upload documentation

	board: $(BOARDOBJS)

	build/%.o: src/%.c
		@mkdir -p $(@D)
		$(AVR-CC) $(AVR-CFLAGS) $(addprefix -I,  $(BOARDDIR) src tmp) -c -o $@ $<

	$(PROJECT).elf: $(OBJECTS)
		$(AVR-CC) $(AVR-COMMON) -o $@ $^ $(AVR-LDFLAGS)

	%.hex: %.elf
		avr-objcopy -O ihex $< $@

	upload: $(PROJECT).hex
		avrdude -p m1280 -P /dev/ttyUSB0 -c arduino -b 57600 -F -u -U flash:w:$<

	documentation:
		doxygen documentation/Doxyfile

	## Clean target
	clean:
		-rm -rf build tmp
		-rm -f *.elf *.hex
