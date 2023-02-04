# Makefile to build target application from <ROOT>/test_applications

ifeq ($(CI),true)
    CC:=gcc
else
    CC:=arm-none-eabi-gcc
    LD:=arm-none-eabi-ld
    OBJCOPY:=arm-none-eabi-objcopy
    CFLAGS=--specs=nosys.specs
endif

APP?=first_app
APPDIR=$(ROOT_FOLDER)/test_applications/build/$(APP)
OBJDIR=$(ROOT_FOLDER)/test_applications/build/$(APP)/generated_files

CFLAGS+=-Wall -Wextra -Werror
LFLAGS=-T $(ROOT_FOLDER)/bsp/linker.ld -nostdlib

INCLUDES=-I$(ROOT_FOLDER)/driver/headers -I$(ROOT_FOLDER)/bsp
SRCS=$(wildcard $(ROOT_FOLDER)/bsp/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/driver/sources/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/test_applications/$(APP)/*.c)
LDFILES=$(wildcard $(ROOT_FOLDER)/bsp/*.ld)
OBJS=$(SRCS:.c=.o)
$(info ######################################################)
$(info compiling sources)
$(info ######################################################)

CREATE_DIRS:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(APPDIR)

MV_FILES_BUILD:
	@mv $(OBJS) $(OBJDIR)

.PHONY: depend clean all

all:	MAINFUNC GENBIN MV_FILES_BUILD
		$(info ######################################################)
		$(info $(APP) build successfully)
		$(info ######################################################)

MAINFUNC:$(OBJS) CREATE_DIRS

%.o:%.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

GENELF:
		$(info ######################################################)
		$(info linking object files)
		$(info ######################################################)
		$(LD) $(LFLAGS) $(OBJS) -o $(APPDIR)/$(APP).elf

GENBIN:GENELF
		$(info ######################################################)
		$(info generating bin file)
		$(info ######################################################)
		$(OBJCOPY) -O binary $(APPDIR)/$(APP).elf $(APPDIR)/$(APP).bin

depend: $(SRCS)
		makedepend $(INCLUDES) $^

clean:
		rm -rf $(OBJS) $(APPDIR)
