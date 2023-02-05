#include "startup.h"

extern int main(void);
extern void _initialStackPoniter(void);

__attribute__((naked, noreturn)) void _resetHandler(void)
{
	extern long _startbss, _endbss, _startdata, _enddata, _absaddrdata;
	for(long *src = &_startbss; src < &_endbss; src++)
	{
		*src = 0;
	}
    for(long *src = &_startdata, *dst = &_absaddrdata; src < &_enddata;)
	{
		*src++ = *dst++;
	}
	main();
	while(1){};
}

__attribute__((section(".vtors"))) void (*vectorTable[STANDARD_INTR_COUNT + USER_INTR_COUNT])(void)=
{
    _initialStackPoniter,
	_resetHandler
};