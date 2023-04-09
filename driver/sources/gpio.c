#include "gpio.h"

void toggle_LED(void)
{
    // Enable the clock to GPIO port A
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    // Initialize pin A_5
    GPIOA->MODER &= ~(3U << (5 * 2));
    GPIOA->MODER |= (1 & 3) << (5 * 2);

    static int pra_pin_state = 0;

    while(1)
    {
        pra_pin_state = (~pra_pin_state);
        if(pra_pin_state != 0UL)
        {
            GPIOA->BSRR = GPIO_BSRR_BS5;
        }
        else
        {
            GPIOA->BRR = GPIO_BRR_BR5;
        }
        for(uint32_t test_pra=0UL;test_pra<50000UL;test_pra++){};
    }
}

void invert_LED(void)
{
    // Enable the clock to GPIO port A
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    // Initialize pin A_5
    GPIOA->MODER &= ~(3U << (5 * 2));
    GPIOA->MODER |= (1 & 3) << (5 * 2);
    static int pra_pin_state = 0;

    pra_pin_state = (~pra_pin_state);
    if(pra_pin_state != 0UL)
    {
        GPIOA->BSRR = GPIO_BSRR_BS5;
    }
    else
    {
        GPIOA->BRR = GPIO_BRR_BR5;
    }
}
