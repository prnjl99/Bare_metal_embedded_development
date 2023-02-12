# Makefile to build target application from <ROOT>/test_applications

ifeq ($(CI),true)
    CC:=gcc
	CFLAGS=-Wno-pointer-to-int-cast -DCI_ENABLED
else
    CC:=arm-none-eabi-gcc
    LD:=arm-none-eabi-ld
    OBJCOPY:=arm-none-eabi-objcopy
    GDB:=arm-none-eabi-gdb
    CFLAGS=--specs=nosys.specs
endif

APP?=first_app
APPDIR=$(ROOT_FOLDER)/test_applications/build/$(APP)
OBJDIR=$(ROOT_FOLDER)/test_applications/build/$(APP)/generated_files

CFLAGS+=-Wall -Wextra -Werror
ifneq ($(CI),true)
	CFLAGS+=-g -mlittle-endian -mthumb -mcpu=cortex-m4
	CFLAGS+=-mfloat-abi=hard -mfpu=fpv4-sp-d16
endif
LFLAGS=-T $(ROOT_FOLDER)/bsp/linker.ld -Map=$(OBJDIR)/$(APP).map

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
		$(info $(APP) built successfully)
		$(info ######################################################)

flash:	all
		openocd -f stm.cfg -c "init; reset halt; stm32l4x mass_erase 0; exit"
		openocd -f stm.cfg -c "program $(APPDIR)/$(APP).bin reset exit 0x08000000"

# For debugging with GDB:
# 		openocd -f stm.cfg -c "init; reset init"
#  		Then start GDB in other shell and execute following commands:
#		target remote :3333
#		monitor reset init
#		file <PATH TO .elf FILE>
#		load
# Can be programmed via st-flash:
#	 st-flash --reset write $(APPDIR)/$(APP).bin 0x8000000

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

disass: all
		$(GDB) $(APPDIR)/$(APP).elf -batch -ex 'disass /r $(FUNC)'

clean:
		rm -rf $(OBJS) $(APPDIR)
