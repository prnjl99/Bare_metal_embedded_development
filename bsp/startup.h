#include <stdint.h>
#include "systick.h"

#define STACK_START 0x20018000U

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _ebss;
extern uint32_t _sbss;

int main(void);
void reset_handler(void); 
void default_handler(void);
