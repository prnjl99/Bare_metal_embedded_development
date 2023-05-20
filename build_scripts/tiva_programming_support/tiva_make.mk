ifeq ($(CI),true)
    CC:=gcc
    CFLAGS=-Wno-pointer-to-int-cast -DCI_ENABLED
else
    CC:=arm-none-eabi-gcc
    AS:=arm-none-eabi-as
    AR:=arm-none-eabi-ar
    OBJCOPY:=arm-none-eabi-objcopy
    GDB:=arm-none-eabi-gdb
    READELF:=arm-none-eabi-readelf
endif

include tiva_programming_support/scratch.mk

OBJS=$(SRCS:.c=.o) $(ASSM:.s=.o)

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

%.o:%.s
		$(CC) $(AFLAGS) $(INCLUDES) -c $< -o $@

GENELF:
		$(info ######################################################)
		$(info linking object files)
		$(info ######################################################)
		$(info $(LFLAGS))
		$(LD) $(LFLAGS) $(OBJS) -o $(APPDIR)/$(APP).elf
		$(READELF) -Sl $(APPDIR)/$(APP).elf > $(APPDIR)/$(APP).readelf

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
