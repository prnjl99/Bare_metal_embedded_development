#include "startup.h"
#include "common.h"
#include "gpio.h"

int main(void)
{
    toggle_LED();
}

void User_intr_handler(void)
{
    while(1){};
}

