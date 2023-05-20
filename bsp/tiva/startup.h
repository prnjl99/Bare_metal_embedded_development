#include <stdint.h>

extern uint32_t _etext;
extern uint32_t _sldata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _ebss;
extern uint32_t _sbss;
extern uint32_t _slrelocate_intr;
extern uint32_t _srelocate_intr;
extern uint32_t _erelocate_intr;
extern uint32_t _size_relocate_intr;

int main(void);
void default_handler(void);
