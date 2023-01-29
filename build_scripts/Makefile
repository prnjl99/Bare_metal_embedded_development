# Makefile to build target application from <ROOT>/test_applications

ifeq ($(CI),true)
    CC:=gcc
else
    CC:=arm-none-eabi-gcc
    LD:=arm-none-eabi-ld
    OBJCOPY:=arm-none-eabi-objcopy
    CFLAGS=--specs=nosys.specs
endif

MAIN=$(APP)

#UTILITY VARIABLES
RM      = rm -rf
MKDIR   = @mkdir -p $(@D) #creates folders if not present

INCLUDES=-I$(ROOT_FOLDER)/driver/headers -I$(ROOT_FOLDER)/bsp

SRCS=$(wildcard $(ROOT_FOLDER)bsp/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/driver/sources/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/test_applications/$(APP)/*.c)

LDFILES=$(wildcard $(ROOT_FOLDER)/bsp/*.ld)

OBJDIR=$(ROOT_FOLDER)/test_applications/build/$(APP)/obj_files
OBJS=$(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

LDFLAGS=-T $(LDFILES) -e Reset_Handler

CFLAGS+=-Wall -Wextra -Werror
CFLAGS+=-mfloat-abi=softfp -Os -MD -std=c99 -c    
CFLAGS+=-ggdb -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 

# Rules to build bin
OBJFUNC:
	mkdir -p $(OBJDIR)

#all: OBJFUNC $(ROOT_FOLDER)\test_applications\build\$(APP)\$(APP).bin

#$(OBJDIR)/%.o: $(SRCS)/%.c
#	$(CC) -o $@ $^ $(INC) $(CFLAGS)

#$(ROOT_FOLDER)\test_applications\build\$(APP)\$(APP).elf:$(OBJS)
#	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCS) -o $(OBJS)
#	$(CC) -o $(OBJS) $(SRCS) $(INC) $(CFLAGS)
#	$(LD) -o $@ $^ $(LDFLAGS)

#$(ROOT_FOLDER)\test_applications\build\$(APP)\$(APP).bin: $(ROOT_FOLDER)\test_applications\build\$(APP)\$(APP).elf
#	$(OBJCOPY) -O binary $< $@

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

#remove object and bin files
clean:
	-$(RM) $(OBJDIR)

.PHONY: all clean