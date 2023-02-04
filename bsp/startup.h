#define STANDARD_INTR_COUNT 16UL
#define USER_INTR_COUNT     82UL

extern __attribute__((section(".vtors"))) void (*vectorTable[STANDARD_INTR_COUNT + USER_INTR_COUNT])(void);
