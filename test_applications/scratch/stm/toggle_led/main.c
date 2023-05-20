#include "startup.h"
#include "common.h"
#include "gpio.h"

const uint32_t pra_const = 1UL;
char *pra_arr="Hello";
char pra_arr_1[]="Hello";

int main(void)
{
    toggle_LED();
	(void)pra_const;
	(void)pra_arr;
	(void)pra_arr_1;
}

void User_intr_handler(void)
{
    while(1){};
}

