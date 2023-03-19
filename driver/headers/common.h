#include <stdint.h>

#ifndef COMMON_H
#define COMMON_H

#define PERIPH_BASE           (0x40000000UL) /*!< Peripheral base address */

#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000UL)
#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x08000000UL)

#define RCC_BASE              (AHB1PERIPH_BASE + 0x1000UL)
#define RCC                   ((RCC_TypeDef *) RCC_BASE)
#define RCC_AHB2ENR_GPIOAEN   1UL

#define     __IM     volatile const
#define     __IOM    volatile

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t ICSCR;
  volatile uint32_t CFGR;
  volatile uint32_t PLLCFGR;
  volatile uint32_t PLLSAI1CFGR;
  volatile uint32_t PLLSAI2CFGR;
  volatile uint32_t CIER;
  volatile uint32_t CIFR;
  volatile uint32_t CICR;
  uint32_t          RESERVED0;
  volatile uint32_t AHB1RSTR;
  volatile uint32_t AHB2RSTR;
  volatile uint32_t AHB3RSTR;
  uint32_t          RESERVED1;
  volatile uint32_t APB1RSTR1;
  volatile uint32_t APB1RSTR2;
  volatile uint32_t APB2RSTR;
  uint32_t          RESERVED2;
  volatile uint32_t AHB1ENR;
  volatile uint32_t AHB2ENR;
} RCC_TypeDef;

void blink_LED(void);
void _close(void);
void _lseek(void); 
void _read(void);
void _write(void);

#endif /* COMMON_H */
