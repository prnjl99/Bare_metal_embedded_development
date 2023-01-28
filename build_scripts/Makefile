# Makefile to build target application from <ROOT>/test_applications

ifeq ($(CI),true)
    CC:=gcc
else
    CC:=arm-none-eabi-gcc
    CFLAGS=--specs=nosys.specs
endif


APP?=first_app
OBJDIR=$(ROOT_FOLDER)/test_applications/build/$(APP)

CFLAGS+=-Wall -Wextra -Werror
LFLAGS=

INCLUDES=-I$(ROOT_FOLDER)/driver/headers -I$(ROOT_FOLDER)/bsp
SRCS=$(wildcard $(ROOT_FOLDER)/bsp/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/driver/sources/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/test_applications/$(APP)/*.c)
LDFILES=$(wildcard $(ROOT_FOLDER)/bsp/*.ld)
OBJS= $(SRCS:.c=.o)

MAIN=$(APP)

OBJFUNC:
	mkdir -p $(OBJDIR)

.PHONY: depend clean

all:	MAINFUNC
		$(info ######################################################)
		$(info $(APP) build successfully)
		$(info ######################################################)

MAINFUNC:	$(OBJS) OBJFUNC
		$(CC) $(CFLAGS) $(INCLUDES) -o $(OBJDIR)/$(MAIN) $(OBJS) $(LFLAGS)

.c.o:
		$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

depend: $(SRCS)
		makedepend $(INCLUDES) $^
clean:
		$(RM)-r $(OBJS) $(OBJDIR)
