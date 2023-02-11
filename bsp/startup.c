#include "startup.h"
#include <stdint.h>

#ifdef CI_ENABLED
    uint32_t vector[] __attribute__ ((section (".isr_vector"))) = {
        STACK_START,
        0x0UL,
    };
#else
    uint32_t vector[] __attribute__ ((section (".isr_vector"))) = {
        STACK_START,
        (uint32_t)(&reset_handler),
    };
#endif

void default_handler(void){
    while(1){};
}

void reset_handler(void)
{
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint32_t *pDst = (uint32_t*)&_sdata;
    uint32_t *pSrc = (uint32_t*)&_etext;

    for(uint32_t i =0 ; i<size; i++)
    {
        *pDst++ = *pSrc++;
    }
    
    size = &_ebss - &_sbss;
    pDst = (uint32_t*)&_sbss;

    for(uint32_t i =0 ; i<size; i++)
    {
        *pDst++ = 0;
    }

    main();
}
