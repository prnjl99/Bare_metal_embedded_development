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

ifeq ($(scratch),1)
	include stm_programming_support/scratch.mk
else
	include stm_programming_support/stm_driver.mk
endif

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

flash:	all
		openocd -f stm.cfg -c "init; reset halt; stm32l4x mass_erase 0; exit"
		openocd -f stm.cfg -c "program $(APPDIR)/$(APP).bin reset exit 0x08000000"

debug:	all
		openocd -f stm.cfg -c "init; reset init"

erase:
		openocd -f stm.cfg -c "init; reset halt; stm32l4x mass_erase 0; exit"

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
