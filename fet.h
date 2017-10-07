#define SET_FET0() do { PORTE |= 0x08; } while (0)
#define SET_FET1() do { PORTE |= 0x10; } while (0)
#define SET_FET2() do { PORTE |= 0x20; } while (0)
#define SET_FET3() do { PORTH |= 0x08; } while (0)
#define SET_FET4() do { PORTH |= 0x10; } while (0)
#define SET_FET5() do { PORTH |= 0x20; } while (0)
#define SET_FET6() do { PORTL |= 0x08; } while (0)
#define SET_FET7() do { PORTL |= 0x10; } while (0)

#define CLR_FET0() do { PORTE &= ~0x08; } while (0)
#define CLR_FET1() do { PORTE &= ~0x10; } while (0)
#define CLR_FET2() do { PORTE &= ~0x20; } while (0)
#define CLR_FET3() do { PORTH &= ~0x08; } while (0)
#define CLR_FET4() do { PORTH &= ~0x10; } while (0)
#define CLR_FET5() do { PORTH &= ~0x20; } while (0)
#define CLR_FET6() do { PORTL &= ~0x08; } while (0)
#define CLR_FET7() do { PORTL &= ~0x10; } while (0)

#ifdef __cplusplus
extern "C" {
#endif

void fet_init(void);

#ifdef __cplusplus
}
#endif
