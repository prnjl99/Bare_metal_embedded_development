#include "main.h"

int main(void)
{
	/* Move to unpriviledged mode */
	__asm("MOV R0, #01");
	__asm("MSR CONTROL, R0");
	/* Try to move to unpriviledged mode, but it will not be allowed */
	__asm("MOV R0, #0x00");
	__asm("MSR CONTROL, R0");

	while(1){};
}
