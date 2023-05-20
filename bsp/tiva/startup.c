#include <stdint.h>
#include "startup.h"

#ifdef CI_ENABLED
    void (*vector[])(void) __attribute__ ((section (".isr_vector"))) = {
        (void (*)(void))STACK_START,
        (void (*)(void))0x0UL,
    };
#else
    static uint32_t pui32Stack[128];

    void reset_handler(void) __attribute__ ((weak, alias("default_reset_handler")));
    void SysTick_Handler(void) __attribute__ ((weak, alias("default_SysTick_Handler")));
    void (*vector[])(void) __attribute__ ((section (".isr_vector"))) = {
        (void (*)(void))((uint32_t)pui32Stack + sizeof(pui32Stack)),
        (void (*)(void))(&reset_handler),
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		(void (*)(void))(&SysTick_Handler)
    };
#endif

volatile uint32_t s_ticks;

void default_handler(void){
    while(1){};
}

void default_reset_handler(void)
{
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint32_t *pDst = (uint32_t*)&_sdata;
    uint32_t *pSrc = (uint32_t*)&_sldata;

    for(uint32_t i =0 ; i<size; i++)
    {
        *pDst++ = *pSrc++;
    }
    
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDst = (uint32_t*)&_sbss;

    for(uint32_t i =0 ; i<size; i++)
    {
        *pDst++ = 0;
    }

    main();
}

void default_SysTick_Handler(void)
{
    s_ticks++;
}
