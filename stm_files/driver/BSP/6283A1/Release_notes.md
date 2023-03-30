---
pagetitle: Release Notes for X-NUCLEO-6283A1 BSP 
lang: en
header-includes: <link rel="icon" type="image/x-icon" href="_htmresc/favicon.png" />
---

::: {.row}
::: {.col-sm-12 .col-lg-4}

<center>
# Release Notes for <mark>X-NUCLEO-6283A1</mark> BSP
Copyright &copy; 2021 STMicroelectronics\
    
[![ST logo](_htmresc/st_logo_2020.png)](https://www.st.com){.logo}
</center>

# License

This software component is licensed by ST under BSD 3-Clause, the "License"; You may not use this component except in compliance with the License. You may obtain a copy of the License at:

[BSD 3-Clause](https://opensource.org/licenses/BSD-3-Clause)

# Purpose

The **6283A1 BSP** is a software component intenteded to be used within the **STM32Cube** ecosystem. This software implements the BSP v2.0 specifications for the X-NUCLEO-6283A1 Expansion Board on STM32. It is built on top of STM32Cube software technology that ease portability across different STM32 micro-controllers.

Here is the list of references:

- [X-NUCLEO-6283A1: 6-channel ambient light sensor, with flicker extraction expansion board based on VD6283 for STM32 Nucleo](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/imaging-evaluation-boards/x-nucleo-6283a1.html)
- [VD6283TX: Hybrid filter multispectral sensor with light flicker engine](https://www.st.com/content/st_com/en/products/imaging-and-photonics-solutions/ambient-light-sensors/vd6283tx.html)

:::

::: {.col-sm-12 .col-lg-8}
# Update History

::: {.collapse}
<input type="checkbox" id="collapse-section2" checked aria-hidden="true">
<label for="collapse-section2" aria-hidden="true">__v1.0.1 / July 12th 2021__</label>
<div>			

## Main Changes

### Maintenance release

- Ignore i2c_recover return value during initialization
- Remove I2C1 hard-coded statements to ensure code portability

## Contents
<small>The components flagged by "[]{.icon-st-update}" have changed since the
previous release. "[]{.icon-st-add}" are new.</small>

Components

  Name                                                        Version                                           License                                                                                                       Release note
  ----------------------------------------------------------- ------------------------------------------------- ------------------------------------------------------------------------------------------------------------- ------------------------------------------------------------------------------------------------------------------------------------------------
  **X-NUCLEO-6283A1 BSP Driver**                                                     V1.0.1[]{.icon-st-add}                                            [BSD 3-Clause](https://opensource.org/licenses/BSD-3-Clause)                                                [release note](.\Release_Notes.html)

Note: in the table above, components **highlighted** have changed since previous release.

## Known Limitations


  Headline
  ----------------------------------------------------------
    The current implementation of this driver doesn't allow the simultaneous usage of ALS and flicker since the functions VD6283A1_Start() and VD6283A1_StartFlicker() are mutually exclusive.

## Development Toolchains and Compilers

- IAR System Workbench V8.50.9
- ARM Keil V5.32
- STM32CubeIDE v1.6.1

## Supported Devices and Boards

- X-NUCLEO-6283A1

## Backward Compatibility

N/A

## Dependencies

This software release is compatible with:

- VD6283TX Component Driver v1.0.1

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section1" checked aria-hidden="true">
<label for="collapse-section1" aria-hidden="true">__v1.0.0 / June 11th 2021__</label>
<div>			

## Main Changes

### First release

This is the first release of the **6283A1 BSP** Driver.

## Contents
<small>The components flagged by "[]{.icon-st-update}" have changed since the
previous release. "[]{.icon-st-add}" are new.</small>

Components

  Name                                                        Version                                           License                                                                                                       Release note
  ----------------------------------------------------------- ------------------------------------------------- ------------------------------------------------------------------------------------------------------------- ------------------------------------------------------------------------------------------------------------------------------------------------
  **X-NUCLEO-6283A1 BSP Driver**                                                     V1.0.0[]{.icon-st-add}                                            [BSD 3-Clause](https://opensource.org/licenses/BSD-3-Clause)                                                [release note](.\Release_Notes.html)

Note: in the table above, components **highlighted** have changed since previous release.

## Known Limitations


  Headline
  ----------------------------------------------------------
    The current implementation of this driver doesn't allow the simultaneous usage of ALS and flicker since the functions VD6283A1_Start() and VD6283A1_StartFlicker() are mutually exclusive.

## Development Toolchains and Compilers

- IAR System Workbench V8.50.9
- ARM Keil V5.31
- STM32CubeIDE v1.6.0

## Supported Devices and Boards

- X-NUCLEO-6283A1

## Backward Compatibility

N/A

## Dependencies

This software release is compatible with:

- VD6283TX Component Driver v1.0.0

</div>
:::

:::
:::

<footer class="sticky">
::: {.columns}
::: {.column width="95%"}
For complete documentation on **STM32Cube Expansion Packages** ,
visit: [STM32Cube Expansion Packages](https://www.st.com/en/embedded-software/stm32cube-expansion-packages.html)
:::
::: {.column width="5%"}
<abbr title="Based on template cx566953 version 2.0">Info</abbr>
:::
:::
</footer>
