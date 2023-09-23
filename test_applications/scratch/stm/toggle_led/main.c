#include "startup.h"
#include "common.h"
#include "gpio.h"
#include <stdio.h>

const uint32_t pra_const = 1UL;
char *pra_arr="Hello";
char pra_arr_1[]="Hello";

int main(void)
{
    volatile float test_f = 1.035;
    toggle_LED();
	printf("%f",test_f);
	(void)test_f;
	(void)pra_const;
	(void)pra_arr;
	(void)pra_arr_1;
}

void User_intr_handler(void)
{
    while(1){};
}

