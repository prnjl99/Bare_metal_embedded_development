#include <stdint.h>
#include "main.h"


#ifndef COMMON_H
#define COMMON_H

#define PERIPH_BASE           (0x40000000UL) /*!< Peripheral base address */

#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000UL)
#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x08000000UL)

#define RCC_BASE              (AHB1PERIPH_BASE + 0x1000UL)
#define RCC                   ((RCC_TypeDef *) RCC_BASE)
#define RCC_AHB2ENR_GPIOAEN   1UL

#define     __I     volatile const
#define     __O     volatile
#define     __IO    volatile
#define     __OM     volatile
#define     __IM     volatile const
#define     __IOM    volatile

#define BIT_POS(x) (1UL << (x))

typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t ICSCR;
  __IO uint32_t CFGR;
  __IO uint32_t PLLCFGR;
  __IO uint32_t PLLSAI1CFGR;
  __IO uint32_t PLLSAI2CFGR;
  __IO uint32_t CIER;
  __IO uint32_t CIFR;
  __IO uint32_t CICR;
  uint32_t      RESERVED0;
  __IO uint32_t AHB1RSTR;
  __IO uint32_t AHB2RSTR;
  __IO uint32_t AHB3RSTR;
  uint32_t      RESERVED1;
  __IO uint32_t APB1RSTR1;
  __IO uint32_t APB1RSTR2;
  __IO uint32_t APB2RSTR;
  uint32_t      RESERVED2;
  __IO uint32_t AHB1ENR;
  __IO uint32_t AHB2ENR;
  __IO uint32_t AHB3ENR;
  uint32_t      RESERVED3;
  __IO uint32_t APB1ENR1;
  __IO uint32_t APB1ENR2;
  __IO uint32_t APB2ENR;
  uint32_t      RESERVED4;
  __IO uint32_t AHB1SMENR;
  __IO uint32_t AHB2SMENR;
  __IO uint32_t AHB3SMENR;
  uint32_t      RESERVED5;
  __IO uint32_t APB1SMENR1;
  __IO uint32_t APB1SMENR2;
  __IO uint32_t APB2SMENR;
  uint32_t      RESERVED6;
  __IO uint32_t CCIPR;
  uint32_t      RESERVED7;
  __IO uint32_t BDCR;
  __IO uint32_t CSR;
} RCC_TypeDef;

void _close(void);
void _lseek(void); 
void _read(void);
void _write(void);

#endif /* COMMON_H */
