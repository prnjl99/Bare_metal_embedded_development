#include <stdint.h>
#include "common.h"

#ifndef GPIO_H
#define GPIO_H

#define GPIOA_BASE            (AHB2PERIPH_BASE + 0x0000UL)
#define GPIOA                 ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIO_BSRR_BS5         (0x1UL << 5U)
#define GPIO_BRR_BR5          (0x1UL << 5U)

typedef struct
{
  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t LCKR;
  volatile uint32_t AFR[2];
  volatile uint32_t BRR;
} GPIO_TypeDef;

void toggle_LED(void);
void invert_LED(void);

#endif /* GPIO_H */
