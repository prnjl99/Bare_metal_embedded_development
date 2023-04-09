#include "startup.h"
#include "common.h"
#include "gpio.h"

const uint32_t pra_const = 1UL;

int main(void)
{
    toggle_LED();
	(void)pra_const;
}

void User_intr_handler(void)
{
    while(1){};
}

