# ARM Cortex-M4 based driver development using STM32L476RG and ek-tm4c123gxl
Currently developing bare metal driver, startup-code, linker-script, build infrastructure etc. for STM32L476RG ( STMicroelectronics ) and ek-tm4c123gxl ( Texas Instruments ) boards without using any IDE/development environment.

Commands:
- **Clean project**:`<ARGUMENTS> <PATH OF PROJECT'S ROOT FOLDER>`/build_scripts/build.sh clean
- **Build project**:`<ARGUMENTS> <PATH OF PROJECT'S ROOT FOLDER>`/build_scripts/build.sh build `APP`
- **Flash project**:`<ARGUMENTS> <PATH OF PROJECT'S ROOT FOLDER>`/build_scripts/build.sh flash `APP`
- **Erase project from STM32L476RG**:`<ARGUMENTS> <PATH OF PROJECT'S ROOT FOLDER>`/build_scripts/build.sh erase
- **Debug project using GDB**:`<ARGUMENTS> <PATH OF PROJECT'S ROOT FOLDER>`/build_scripts/build.sh debug `APP`
- **Dissassemble** :`<ARGUMENTS> <PATH OF PROJECT'S ROOT FOLDER>`/build_scripts/build.sh disass `APP` `FUNCTION`

Arguments to command:
- **Target selection**:prepend `tiva=1` or `stm=1` in command to select STM32L476RG and ek-tm4c123gxl as target device
- **Driver selection**: This repo supports building using driver library provided by kit vendor or driver/BSPs developed from scratch by me. To use driver/BSPs developed by me from scratch, prepend `scratch=1` in command. By default if this argument is not provided, it will use driver library provided by kit vendor.
e.g. `stm=1 scratch=1 <PATH OF PROJECT'S ROOT FOLDER>/build_scripts/build.sh build toggle_led` command builds toggle_led application for STM32L476RG using driver/BSPs developed from scratch by me.

_Note:_
- _`APP` can be selected from test_applications directory. e.g. `toggle_led`_
- _`FUNCTION` can be any function in the project. e.g. `main`_

Documents related to STM32L476RG:

- https://www.st.com/resource/en/datasheet/stm32l476je.pdf
- https://www.st.com/resource/en/reference_manual/rm0351-stm32l47xxx-stm32l48xxx-stm32l49xxx-and-stm32l4axxx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
- https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf

Documents related to ek-tm4c123gxl:

- https://www.ti.com/lit/ds/spms376e/spms376e.pdf