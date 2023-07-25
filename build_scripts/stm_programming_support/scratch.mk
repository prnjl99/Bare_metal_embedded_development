# Makefile to build target application from <ROOT>/test_applications
ifneq ($(CI),true)
    LD:=arm-none-eabi-ld
endif

APP?=first_app
APPDIR=$(ROOT_FOLDER)/test_applications/build/$(build_dir)/$(APP)
OBJDIR=$(ROOT_FOLDER)/test_applications/build/$(build_dir)/$(APP)/generated_files

CFLAGS+=-Wall -Wextra -Werror

ifneq ($(CI),true)
    CFLAGS+=-g3 -O0 -mlittle-endian -mthumb -mcpu=cortex-m4 --specs=nosys.specs
    CFLAGS+=-mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nano.specs -std=gnu11
    # Generate separate sections for each data functions
    CFLAGS+=-fdata-sections -ffunction-sections
endif

LFLAGS=-T $(ROOT_FOLDER)/bsp/stm/linker.ld -Map=$(APPDIR)/$(APP).map
# Enable this to discard sections using garbage collector
#LFLAGS+=--gc-sections

-include $(ROOT_FOLDER)/test_applications/scratch/stm/$(APP)/config.mk

INCLUDES=-I$(ROOT_FOLDER)/driver/headers -I$(ROOT_FOLDER)/bsp/stm -I$(ROOT_FOLDER)/test_applications/scratch/stm/$(APP)

SRCS=$(wildcard $(ROOT_FOLDER)/bsp/stm/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/driver/sources/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/test_applications/scratch/stm/$(APP)/*.c)

LDFILES=$(wildcard $(ROOT_FOLDER)/bsp/stm/*.ld)
