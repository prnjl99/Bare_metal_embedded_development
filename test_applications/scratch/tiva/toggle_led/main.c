#include "startup.h"

#include <stdint.h>
#include <stdbool.h>
#include "main.h"

int main(void)
{
    static int pra_pin_state_1 = 0x0;
    static int pra_pin_state_2 = 0x0;
    static int pra_pin_state_3 = 0x0;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){};

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

    while(1)
    {
        pra_pin_state_1 = ((pra_pin_state_1 == GPIO_PIN_3) ? 0x0 : GPIO_PIN_1);
        pra_pin_state_2 = ((pra_pin_state_2 == GPIO_PIN_3) ? 0x0 : GPIO_PIN_2);
        pra_pin_state_3 = ((pra_pin_state_3 == GPIO_PIN_3) ? 0x0 : GPIO_PIN_3);

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, pra_pin_state_1);
        for(uint32_t test_pra=0UL;test_pra<700000UL;test_pra++){};

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, pra_pin_state_2);
        for(uint32_t test_pra=0UL;test_pra<700000UL;test_pra++){};

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, pra_pin_state_3);
        for(uint32_t test_pra=0UL;test_pra<700000UL;test_pra++){};

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0);

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        for(uint32_t test_pra=0UL;test_pra<700000UL;test_pra++){};
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
        for(uint32_t test_pra=0UL;test_pra<700000UL;test_pra++){};
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
        for(uint32_t test_pra=0UL;test_pra<700000UL;test_pra++){};
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0);
    }
}

void User_intr_handler(void)
{
    while(1){};
}

