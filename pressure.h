#include "adc.h"

#define MPXV7007_TO_DECI_INH2O(x) ((x * 200910) / 292578)
#define MPXV7025_TO_DECI_INH2O(x) ((x * 200910) / 92070)
#define MPXV7007_TO_PA(x) (((long long) x * 5000000) / 292578)
#define MPXV7025_TO_PA(x) (((long long) x * 5000000) / 92070)
#define MPXV7007_TO_HPA(x) ((x * 50000) / 292578)
#define MPXV7025_TO_HPA(x) ((x * 50000) / 92070)

enum pressure_channel {
	P0 = (AP0 & ADCBANK0),
	P1 = (AP1 & ADCBANK0),
	P2 = (AP0 & ADCBANK1),
	P3 = (AP1 & ADCBANK1),
	P4 = (AP0 & ADCBANK2),
	P5 = (AP1 & ADCBANK2)
};
