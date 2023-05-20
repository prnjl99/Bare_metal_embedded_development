#include "startup.h"

#include <stdint.h>
#include <stdbool.h>
#include "main.h"

int main(void)
{
    static int pra_pin_state = 0x0;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){};

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

    while(1)
    {
        pra_pin_state = ((pra_pin_state == 0x8) ? 0x0 : 0x8);

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, pra_pin_state);

        for(uint32_t test_pra=0UL;test_pra<50000UL;test_pra++){};
    }
}

void User_intr_handler(void)
{
    while(1){};
}

