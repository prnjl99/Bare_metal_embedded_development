#include "startup.h"
#include "common.h"
#include "gpio.h"

int main(void)
{
    while(1){};
}

void User_intr_handler(void)
{
    toggle_LED();
}