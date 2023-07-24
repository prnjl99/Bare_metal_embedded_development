ifeq ($(CI),true)
    CC:=gcc
    CFLAGS=-Wno-pointer-to-int-cast -DCI_ENABLED
else
    CC:=arm-none-eabi-gcc
    AS:=arm-none-eabi-as
    AR:=arm-none-eabi-ar
    DISASS:=arm-none-eabi-objdump
    OBJCOPY:=arm-none-eabi-objcopy
    GDB:=arm-none-eabi-gdb
    READELF:=arm-none-eabi-readelf
	# nm also can be used to analyze object files and final executable file ( because both are in ELF format )
	# Linux uses ELF format, whereas Windows uses COFF format
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

all:	MAINFUNC GENDISASS GENDISASS_M MV_FILES_BUILD
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

GENIM:GENELF
		$(info ######################################################)
		$(info generating bin and hex images)
		$(info ######################################################)
		$(OBJCOPY) -O binary $(APPDIR)/$(APP).elf $(APPDIR)/$(APP).bin
		$(OBJCOPY) -O ihex $(APPDIR)/$(APP).elf $(APPDIR)/$(APP).hex

GENDISASS:GENIM
		$(info ######################################################)
		$(info generating disassembly file)
		$(info ######################################################)
		$(DISASS) -D $(APPDIR)/$(APP).elf > $(APPDIR)/$(APP).s

GENDISASS_M:
		$(info ######################################################)
		$(info generating disassembly of main.c file)
		$(info ######################################################)
		$(CC) -S $(CFLAGS) $(INCLUDES) $(ROOT_FOLDER)/test_applications/scratch/stm/$(APP)/main.c -o $(APPDIR)/main.s

depend: $(SRCS)
		makedepend $(INCLUDES) $^

disass: all
		$(GDB) $(APPDIR)/$(APP).elf -batch -ex 'disass /r $(FUNC)'

clean:
		rm -rf $(OBJS) $(APPDIR)
