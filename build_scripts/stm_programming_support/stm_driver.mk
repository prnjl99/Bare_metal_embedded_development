# Makefile to build target application from <ROOT>/test_applications
ifneq ($(CI),true)
    LD:=arm-none-eabi-gcc
endif

APP?=uart
APPDIR=$(ROOT_FOLDER)/test_applications/build/$(build_dir)/$(APP)
OBJDIR=$(ROOT_FOLDER)/test_applications/build/$(build_dir)/$(APP)/generated_files

CFLAGS+=-Wall -Wextra -Werror -DSTM32L476xx -Wno-unused-parameter
ifneq ($(CI),true)
    CFLAGS+=-mlittle-endian -mthumb -mcpu=cortex-m4
    CFLAGS+=-mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -O0 -ffunction-sections -fdata-sections --specs=nano.specs
    AFLAGS+=-Wall -mlittle-endian -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -g3
endif

LFLAGS=-T $(ROOT_FOLDER)/stm_files/bsp/STM32L476RGTX_FLASH.ld -mcpu=cortex-m4 --specs=nosys.specs -Wl,-Map="$(APPDIR)/$(APP).map"
LFLAGS+=-static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
# Enable this to discard sections using garbage collector
#LFLAGS+=-Wl,--gc-sections

INCLUDES=-I$(ROOT_FOLDER)/stm_files/driver/BSP/STM32L4xx_Nucleo -I$(ROOT_FOLDER)/stm_files/driver/CMSIS/Device/ST/STM32L4xx/Include
INCLUDES+=-I$(ROOT_FOLDER)/stm_files/driver/CMSIS/Include -I$(ROOT_FOLDER)/stm_files/driver/STM32L4xx_HAL_Driver/Inc
INCLUDES+=-I$(ROOT_FOLDER)/stm_files/driver/STM32L4xx_HAL_Driver/Inc/Legacy -I$(ROOT_FOLDER)/stm_files/driver
INCLUDES+=-I$(ROOT_FOLDER)/test_applications/using_stm_drivers/$(APP)

SRCS=$(wildcard $(ROOT_FOLDER)/stm_files/driver/BSP/STM32L4xx_Nucleo/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/stm_files/driver/STM32L4xx_HAL_Driver/Src/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/stm_files/driver/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/test_applications/using_stm_drivers/$(APP)/*.c)

ASSM+=$(wildcard $(ROOT_FOLDER)/stm_files/bsp/*.s)

LDFILES=$(wildcard $(ROOT_FOLDER)/stm_files/bsp/*.ld)

ARCH_FILE=$(wildcard $(ROOT_FOLDER)/stm_files/bsp/*.a)
