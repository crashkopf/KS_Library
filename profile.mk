# Kitchen Sink Setup

## General Flags
export CPU ?= atmega1280
export BOARD ?= kitchensink
export F_CPU ?= 16000000UL

BOARDDIR ?= .
BUILDDIR ?= build

AVR-CC=avr-gcc
AVR-LD=avr-ld
AVR-OBJCOPY=avr-objcopy

## Options common to compile, link and assembly rules
AVR-COMMON = -mmcu=$(CPU)

## Compile options common for all C compilation units.
WARNINGS=-Wall -Wextra -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-align -Wsign-compare \
		-Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wunused \
		-Wfatal-errors

AVR-CFLAGS = $(AVR-COMMON) \
	-Os \
	$(WARNINGS) \
	-D_CPU=$(CPU) \
	-DF_CPU=$(F_CPU) \
	-fdata-sections -ffunction-sections

BOARDOBJS = \
	$(BUILDDIR)/adc.o \
	$(BUILDDIR)/debug.o \
	$(BUILDDIR)/dallas_one_wire.o \
	$(BUILDDIR)/display.o \
	$(BUILDDIR)/fet.o \
	$(BUILDDIR)/graph.o \
	$(BUILDDIR)/hd44780.o \
	$(BUILDDIR)/keypad.o \
	$(BUILDDIR)/kitchensink.o \
	$(BUILDDIR)/timer0.o \
	$(BUILDDIR)/timer1.o \
	$(BUILDDIR)/usart0.o \

board: $(BOARDOBJS)

$(BUILDDIR)/%.o: $(BOARDDIR)/%.c
	@mkdir -p $(@D)
	$(AVR-CC) $(AVR-CFLAGS) -c -o $@ $<

