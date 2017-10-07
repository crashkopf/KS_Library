#ifndef _ADC_H
#define _ADC_H
/*
	Notes:
	ADC channels 8..13 are banked.  This means the devices being read changes with the bank setting.

	Floating point calcs are used in macros to preserve precision, but these should end up as integer math if
	optimization is turned on (see "constant folding")
*/

// 10 bits
#define ADC_MAXCOUNT (1023u)

// in millivolts - use floating point to preserve precision at compile time
#define ADC_REF_V (5000.0)

#define ADC_TO_MILLIVOLTS(x) ( x * (ADC_REF_V / ADC_MAXCOUNT))
#define MILLIVOLTS_TO_ADC(x) ( x * (ADC_MAXCOUNT / ADC_REF_V))

//
enum adc_channel {
	ANA0 = 0,
	ANA1 = 1,
	ANA2 = 2,
	ANA3 = 3,
	ANA4 = 4,
	ANA5 = 5,
	ANA6 = 6,
	ANA7 = 7,
	AT0 = 8,
	AT1 = 9,
	AT2 = 10,
	AT3 = 11,
	AP0 = 12,
	AP1 = 13
};

// This is for the external mux, not the internal one
// These are left-shifted by 4 so they can be ANDed with the internal ADC channel
enum adc_bank {
	ADCBANK0 = (0 << 4),
	ADCBANK1 = (1 << 4),
	ADCBANK2 = (2 << 4),
	ADCBANK3 = (3 << 4)
};

#ifdef __cplusplus
extern "C" {
#endif

void adc_init(void);

// chan bits 0..3 are ADC channel, 4..5 are mux bank
// [..mmcccc]
// Use enums declared here and in temperature.h, pressure.h to specify channel
unsigned adc_read (unsigned chan);

#ifdef __cplusplus
}
#endif
#endif //_ADC_H
