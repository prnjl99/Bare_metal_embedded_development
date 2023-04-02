# Makefile to build target application from <ROOT>/test_applications
ifneq ($(CI),true)
    LD:=arm-none-eabi-ld
endif

APP?=first_app
APPDIR=$(ROOT_FOLDER)/test_applications/build/$(APP)
OBJDIR=$(ROOT_FOLDER)/test_applications/build/$(APP)/generated_files

CFLAGS+=-Wall -Wextra -Werror

ifneq ($(CI),true)
    CFLAGS+=-g -mlittle-endian -mthumb -mcpu=cortex-m4
    CFLAGS+=-mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nosys.specs
endif

LFLAGS=-T $(ROOT_FOLDER)/bsp/linker.ld -Map=$(OBJDIR)/$(APP).map

INCLUDES=-I$(ROOT_FOLDER)/driver/headers -I$(ROOT_FOLDER)/bsp -I$(ROOT_FOLDER)/test_applications/scratch/$(APP)

SRCS=$(wildcard $(ROOT_FOLDER)/bsp/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/driver/sources/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/test_applications/scratch/$(APP)/*.c)

LDFILES=$(wildcard $(ROOT_FOLDER)/bsp/*.ld)
