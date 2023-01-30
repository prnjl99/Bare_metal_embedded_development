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
LFLAGS=

INCLUDES=-I$(ROOT_FOLDER)/driver/headers -I$(ROOT_FOLDER)/bsp
SRCS=$(wildcard $(ROOT_FOLDER)/bsp/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/driver/sources/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/test_applications/$(APP)/*.c)
LDFILES=$(wildcard $(ROOT_FOLDER)/bsp/*.ld)
OBJS=$(SRCS:.c=.o)

CREATE_DIRS:
	mkdir -p $(OBJDIR)
	mkdir -p $(APPDIR)

MV_FILES_BUILD:
	mv $(OBJS) $(OBJDIR)

.PHONY: depend clean all

all:	MAINFUNC GENBIN MV_FILES_BUILD
		$(info ######################################################)
		$(info $(APP) build successfully)
		$(info ######################################################)

MAINFUNC:$(OBJS) CREATE_DIRS

%.o:%.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

GENELF:
	$(LD) -o $(APPDIR)/$(APP).elf $(OBJS) $(LFLAGS)

GENBIN:GENELF
	$(OBJCOPY) -O binary $(APPDIR)/$(APP).elf $(APPDIR)/$(APP).bin

depend: $(SRCS)
		makedepend $(INCLUDES) $^

clean:
		$(RM)-r $(OBJS) $(APPDIR)
