#include <stdint.h>

#define PERIPH_BASE           (0x40000000UL) /*!< Peripheral base address */

#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000UL)
#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x08000000UL)

#define RCC_BASE              (AHB1PERIPH_BASE + 0x1000UL)
#define RCC                   ((RCC_TypeDef *) RCC_BASE)
#define RCC_AHB2ENR_GPIOAEN   1UL

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
