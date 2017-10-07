#ifdef __cplusplus
extern "C" {
#endif

void keypad_init(void);
unsigned short keypad_scan(void);
void keypad_update(void);
unsigned short get_keys(void);

#ifdef __cplusplus
}
#endif
