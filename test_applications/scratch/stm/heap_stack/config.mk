$(info Note- This build is using config.mk from application directory)

LFLAGS=-T $(ROOT_FOLDER)/bsp/stm/linker.ld
ifneq ($(CI),true)
    LD:=arm-none-eabi-gcc
    LFLAGS+=-mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb --specs=nano.specs --specs=nosys.specs
    LFLAGS+=-static -Wl,--start-group -lc -lm -Wl,--end-group -Wl,-Map=$(APPDIR)/$(APP).map 
    # Enable this to discard sections using garbage collector
    #LFLAGS+=--gc-sections
endif
