#include "hd44780.h"
#include "graph.h"

#define NROWS (16)
#define NCOLS (20)
#define CWIDTH (5)
#define CHEIGHT (8)

void graph (unsigned char * data, unsigned char options) {
	unsigned char row = 0;
	unsigned char col = 0;
	unsigned char bits = 0;
	unsigned char k = 0;

	// Draw data to CGRAM
	hd44780_wait_ready(0);
	hd44780_outcmd(HD44780_CGADDR(0));
	for (col = 0; col < NCOLS; col += CWIDTH) {
		for (row=0; row < NROWS; row++) {
			// Render a line from data
			bits = 0;
			for (k = 0; k < CWIDTH; k++) {
				if (options & GRAPH_FILL) {
					if (data[col + k] >= (NROWS - row)) {
						bits |= 1 << ((CWIDTH - 1) - k);
					}
				} else {
					if (data[col + k] == (NROWS - row)) {
						bits |= 1 << ((CWIDTH - 1) - k);
					}
				}
				if (options & GRAPH_SMOOTH) {
					// Left neighbor smoothing
					if ((col + k) > 0) {
						// Lower
						if ((data[col + k - 1] > (NROWS - row)) && ((NROWS - row) > data[col + k])) {
							bits |= 1 << ((CWIDTH - 1) - k);
						}
						// Higher
						if ((data[col + k - 1] < (NROWS - row)) && ((NROWS - row) < data[col + k])) {
							bits |= 1 << ((CWIDTH - 1) - k);
						}
					}
					// Right neighbor smoothing
					if ((col + k) < NCOLS - 1) {
						// Lower
						if ((data[col + k + 1] > (NROWS - row)) && ((NROWS - row) > data[col + k])) {
							bits |= 1 << ((CWIDTH - 1) - k);
						}
						// Higher
						if ((data[col + k + 1] < (NROWS - row)) && ((NROWS - row) < data[col + k])) {
							bits |= 1 << ((CWIDTH - 1) - k);
						}
					}
				}
			}
			hd44780_wait_ready(0);
			hd44780_outdata(bits);
		}
	}
}


void graph_draw_canvas (void) {
	int j;
	hd44780_wait_ready(0);
	hd44780_outcmd(HD44780_DDADDR(0));
	//~ // Line 0
	hd44780_wait_ready(0);
	hd44780_outcmd(HD44780_DDADDR(0));
	for (j=0; j < 4; j++) {hd44780_wait_ready(0); hd44780_outdata(j * 2);}
	// Line 1
	hd44780_wait_ready(0);
	hd44780_outcmd(HD44780_DDADDR(64));
	for (j=0; j < 4; j++) {hd44780_wait_ready(0); hd44780_outdata((j * 2) + 1);}
}
