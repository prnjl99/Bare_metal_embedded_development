# Makefile to build target application from <ROOT>/test_applications
ifneq ($(CI),true)
    LD:=arm-none-eabi-gcc
endif

APP?=first_app
APPDIR=$(ROOT_FOLDER)/test_applications/build/$(APP)
OBJDIR=$(ROOT_FOLDER)/test_applications/build/$(APP)/generated_files

CFLAGS+=-Wall -Wextra -Werror

ifneq ($(CI),true)
    CFLAGS+=-g3 -O0 -mlittle-endian -mthumb -mcpu=cortex-m4 --specs=nosys.specs
    CFLAGS+=-mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nano.specs -std=gnu11
    # Generate separate sections for each data functions
    CFLAGS+=-fdata-sections -ffunction-sections
endif

LFLAGS=-T $(ROOT_FOLDER)/bsp/linker.ld
ifneq ($(CI),true)
    LFLAGS+=-mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb --specs=nano.specs --specs=nosys.specs
    LFLAGS+=-static -Wl,--start-group -lc -lm -Wl,--end-group -Wl,-Map=$(APPDIR)/$(APP).map 
    # Enable this to discard sections using garbage collector
    #LFLAGS+=--gc-sections
endif

INCLUDES=-I$(ROOT_FOLDER)/driver/headers -I$(ROOT_FOLDER)/bsp -I$(ROOT_FOLDER)/test_applications/scratch/$(APP)

SRCS=$(wildcard $(ROOT_FOLDER)/bsp/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/driver/sources/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/test_applications/scratch/$(APP)/*.c)

LDFILES=$(wildcard $(ROOT_FOLDER)/bsp/*.ld)
