#ifdef __cplusplus
extern "C" {
#endif

enum timer1_clock_source {
	TIMER1_DISABLED = 0,
	TIMER1_INT = 1,
	TIMER1_INT_8 = 2,
	TIMER1_INT_64 = 3,
	TIMER1_INT_256 = 4,
	TIMER1_INT_1024 = 5,
	TIMER1_EXT_FALLING = 6,
	TIMER1_EXT_RISING = 7
};

void timer1_init(void);
void timer1_source(enum timer1_clock_source cs);

void OC1A_enable(void);
void OC1A_disable(void);
void OC1B_enable(void);
void OC1B_disable(void);
void OC1C_enable(void);
void OC1C_disable(void);

#ifdef __cplusplus
}
#endif
