#include "adc.h"

// degrees C
#define COLDTEMP (25)

// uV / deg C
#define SENSITIVITY (41ul)

// voltage gain of differential amp stage
#define GAIN (100ul)

#define COMPENSATE(x) ((((x) * (ADC_REF_V / (GAIN * SENSITIVITY))) / ADC_MAXCOUNT) + COLDTEMP)
