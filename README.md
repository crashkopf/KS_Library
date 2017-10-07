ADC - Analog to digital conversion, channel multiplexing.
Debug
Display - High-level display interface
FET
HD44780 - Low-level commands to the display driver
Keypad - Scan 4x4 keypad.  Key debouncing and event queue.
Pressure - Conversion from ADC value to pressure.
Temperature - Conversion from ADC value to temperature.  Cold-point compensation.
Timer0 - System clock
Timer1 - Servo0, Servo1, Servo2
USART0 - USB Serial (57600, N-8-1)
USART1
USART2
USART3

Example:

#include "kitchensink.h"

void main() {
	// Initialize Kitchen Sink hardware
	KS_init();

	// Main program loop...
}
