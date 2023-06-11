#ifndef __MAIN_H
#define __MAIN_H

#include <stdint.h>
#include <stdbool.h>

#define HWREGBITW(x, b)                                                       \
        HWREG(((uint32_t)(x) & 0xF0000000) | 0x02000000 |                     \
              (((uint32_t)(x) & 0x000FFFFF) << 5) | ((b) << 2))

#define HWREG(x)                                                              \
        (*((volatile uint32_t *)(x)))

#define GPIO_PIN_1              0x00000002
#define GPIO_PIN_2              0x00000004  // GPIO pin 2
#define GPIO_PIN_3              0x00000008
#define GPIO_PORTF_BASE         0x40025000
#define GPIO_PIN_TYPE_ANALOG    0x00000000
#define GPIO_STRENGTH_2MA       0x00000001
#define GPIO_PIN_TYPE_STD       0x00000008
#define GPIO_DIR_MODE_OUT       0x00000001
#define GPIO_O_DATA             0x00000000
#define GPIO_O_DR2R             0x00000500
#define GPIO_O_DR4R             0x00000504
#define GPIO_O_DR8R             0x00000508
#define GPIO_O_ODR              0x0000050C
#define GPIO_O_PUR              0x00000510
#define GPIO_O_PDR              0x00000514
#define GPIO_O_SLR              0x00000518
#define GPIO_O_DEN              0x0000051C
#define GPIO_O_AMSEL            0x00000528
#define GPIO_O_DIR              0x00000400
#define GPIO_O_AFSEL            0x00000420

#define SYSCTL_RCGCBASE         0x400fe600
#define SYSCTL_PRBASE           0x400fea00
#define SYSCTL_PERIPH_GPIOF     0xf0000805

static void GPIOPinWrite(uint32_t ui32Port, uint8_t ui8Pins, uint8_t ui8Val)
{
    HWREG(ui32Port + (GPIO_O_DATA + (ui8Pins << 2))) = ui8Val;
}

static void GPIOPadConfigSet(uint32_t ui32Port, uint8_t ui8Pins,
                 uint32_t ui32Strength, uint32_t ui32PinType)
{
    HWREG(ui32Port + GPIO_O_DR2R) = ((ui32Strength & 1) ?
                                     (HWREG(ui32Port + GPIO_O_DR2R) |
                                      ui8Pins) :
                                     (HWREG(ui32Port + GPIO_O_DR2R) &
                                      ~(ui8Pins)));
    HWREG(ui32Port + GPIO_O_DR4R) = ((ui32Strength & 2) ?
                                     (HWREG(ui32Port + GPIO_O_DR4R) |
                                      ui8Pins) :
                                     (HWREG(ui32Port + GPIO_O_DR4R) &
                                      ~(ui8Pins)));
    HWREG(ui32Port + GPIO_O_DR8R) = ((ui32Strength & 4) ?
                                     (HWREG(ui32Port + GPIO_O_DR8R) |
                                      ui8Pins) :
                                     (HWREG(ui32Port + GPIO_O_DR8R) &
                                      ~(ui8Pins)));
    HWREG(ui32Port + GPIO_O_SLR) = ((ui32Strength & 8) ?
                                    (HWREG(ui32Port + GPIO_O_SLR) |
                                     ui8Pins) :
                                    (HWREG(ui32Port + GPIO_O_SLR) &
                                     ~(ui8Pins)));

    HWREG(ui32Port + GPIO_O_ODR) = ((ui32PinType & 1) ?
                                  (HWREG(ui32Port + GPIO_O_ODR) | ui8Pins) :
                                  (HWREG(ui32Port + GPIO_O_ODR) & ~(ui8Pins)));
    HWREG(ui32Port + GPIO_O_PUR) = ((ui32PinType & 2) ?
                                  (HWREG(ui32Port + GPIO_O_PUR) | ui8Pins) :
                                  (HWREG(ui32Port + GPIO_O_PUR) & ~(ui8Pins)));
    HWREG(ui32Port + GPIO_O_PDR) = ((ui32PinType & 4) ?
                                  (HWREG(ui32Port + GPIO_O_PDR) | ui8Pins) :
                                  (HWREG(ui32Port + GPIO_O_PDR) & ~(ui8Pins)));
    HWREG(ui32Port + GPIO_O_DEN) = ((ui32PinType & 8) ?
                                  (HWREG(ui32Port + GPIO_O_DEN) | ui8Pins) :
                                  (HWREG(ui32Port + GPIO_O_DEN) & ~(ui8Pins)));

    HWREG(ui32Port + GPIO_O_AMSEL) =
          ((ui32PinType == GPIO_PIN_TYPE_ANALOG) ?
           (HWREG(ui32Port + GPIO_O_AMSEL) | ui8Pins) :
           (HWREG(ui32Port + GPIO_O_AMSEL) & ~(ui8Pins)));
}

static void GPIODirModeSet(uint32_t ui32Port, uint8_t ui8Pins, uint32_t ui32PinIO)
{
    HWREG(ui32Port + GPIO_O_DIR) = ((ui32PinIO & 1) ?
                                    (HWREG(ui32Port + GPIO_O_DIR) | ui8Pins) :
                                    (HWREG(ui32Port + GPIO_O_DIR) & ~(ui8Pins)));
    HWREG(ui32Port + GPIO_O_AFSEL) = ((ui32PinIO & 2) ?
                                      (HWREG(ui32Port + GPIO_O_AFSEL) |
                                       ui8Pins) :
                                      (HWREG(ui32Port + GPIO_O_AFSEL) &
                                       ~(ui8Pins)));
}

static void GPIOPinTypeGPIOOutput(uint32_t ui32Port, uint8_t ui8Pins)
{
    GPIOPadConfigSet(ui32Port, ui8Pins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);

    GPIODirModeSet(ui32Port, ui8Pins, GPIO_DIR_MODE_OUT);
}

static bool SysCtlPeripheralReady(uint32_t ui32Peripheral)
{
    return(HWREGBITW(SYSCTL_PRBASE + ((ui32Peripheral & 0xff00) >> 8),
                     ui32Peripheral & 0xff));
}

static void SysCtlPeripheralEnable(uint32_t ui32Peripheral)
{
    HWREGBITW(SYSCTL_RCGCBASE + ((ui32Peripheral & 0xff00) >> 8),
              ui32Peripheral & 0xff) = 1;
}

void User_intr_handler(void);

#endif /* __MAIN_H */
