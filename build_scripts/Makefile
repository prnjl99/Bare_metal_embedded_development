# Makefile to build target application from <ROOT>/test_applications

ifeq ($(CI),true)
    CC:=gcc
	CFLAGS=-Wno-pointer-to-int-cast -DCI_ENABLED
else
    CC:=arm-none-eabi-gcc
    LD:=arm-none-eabi-ld
    AS:=arm-none-eabi-as
    AR:=arm-none-eabi-ar
    OBJCOPY:=arm-none-eabi-objcopy
    GDB:=arm-none-eabi-gdb
endif

APP?=first_app
APPDIR=$(ROOT_FOLDER)/test_applications/build/$(APP)
OBJDIR=$(ROOT_FOLDER)/test_applications/build/$(APP)/generated_files

CFLAGS+=-Wall -Wextra -Werror -DSTM32L476xx -Wno-unused-parameter
ifneq ($(CI),true)
    CFLAGS+=-mlittle-endian -mthumb -mcpu=cortex-m4
    CFLAGS+=-mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -O0 -ffunction-sections -fdata-sections --specs=nano.specs
    AFLAGS+=-Wall -mlittle-endian -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -g3
endif
LFLAGS=-T $(ROOT_FOLDER)/bsp/STM32L476RGTX_FLASH.ld -mcpu=cortex-m4 --specs=nosys.specs -Wl,-Map="6283A1_ALSValues.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
INCLUDES=-I$(ROOT_FOLDER)/driver/BSP/STM32L4xx_Nucleo -I$(ROOT_FOLDER)/driver/CMSIS/Device/ST/STM32L4xx/Include -I$(ROOT_FOLDER)/driver/CMSIS/Include
INCLUDES+=-I$(ROOT_FOLDER)/driver/STM32L4xx_HAL_Driver/Inc -I$(ROOT_FOLDER)/driver/STM32L4xx_HAL_Driver/Inc/Legacy -I$(ROOT_FOLDER)/driver
SRCS=$(wildcard $(ROOT_FOLDER)/driver/BSP/STM32L4xx_Nucleo/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/driver/STM32L4xx_HAL_Driver/Src/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/driver/*.c)
SRCS+=$(wildcard $(ROOT_FOLDER)/test_applications/$(APP)/*.c)
ASSM+=$(wildcard $(ROOT_FOLDER)/bsp/*.s)
LDFILES=$(wildcard $(ROOT_FOLDER)/bsp/*.ld)
ARCH_FILE=$(wildcard $(ROOT_FOLDER)/bsp/*.a)
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
		$(AS) $(AFLAGS) $(INCLUDES) -c $< -o $@

GENELF:
		$(info ######################################################)
		$(info linking object files)
		$(info ######################################################)
		$(CC) $(LFLAGS) $(OBJS) -o $(APPDIR)/$(APP).elf

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
