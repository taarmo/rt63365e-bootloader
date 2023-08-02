#########################MACROS#############################################

define C2O
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

define S2O
$(patsubst %.S,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1)))
endef

define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1)))
endef

define COMPILE
$(2) : $(3) $(4)
	$(1) -c -o $(2) $(3) $(5)
endef

#########################MACROS#############################################

RES = main.out

GCC_PATH = /usr/bin/
LINKER_SCRIPT = ./rt63365e.ld 

CC = $(GCC_PATH)mips-linux-gnu-gcc
OBJCOPY = mips-linux-gnu-objcopy

MIPS_FLAGS = -march=mips32r2

CFLAGS = -O2 -EB $(MIPS_FLAGS) -std=c11 -fno-builtin -Wall -pedantic -mno-abicalls -fno-PIC -fno-PIE -fno-stack-protector -fno-omit-frame-pointer -ffreestanding -nostdinc -isystem sysinc -isystem $(shell $(CC) --print-file-name=include) -Wno-multichar 


LD_FLAGS = -nostdlib -static

SRC      = src
LIB      = lib
OBJ      = obj
MKDIR	 = mkdir -p

ifdef DEBUG
	CFLAGS += -g -DDEBUG
else
	CFLAGS += -DNODEBUG
endif

ifdef RAM64
	CFLAGS += -DRAM64
else
	CFLAGS += -DRAM32
endif

MKDIR = mkdir -p
SOURCESC = $(shell find $(SRC)/ -type f -iname *.c)
#SOURCESC = src/main_ram.c src/config_uart.c src/print.c src/write_uart.c
SOURCESS = $(shell find $(SRC)/ -type f -iname *.S)


LIBS = $(LIB)/minlzlib/minlzlib.a $(LIB)/dlmalloc/malloc.a 
ALLOBJS = obj/start.o obj/config_dmc.o obj/init_cache.o obj/init_main.o obj/main.o obj/uart.o obj/vsprintf.o obj/uart_debug.o obj/cache.o obj/spi.o obj/flash.o obj/utils.o obj/exceptions.o obj/exceptions_asm.o obj/timer.o obj/elf_loader.o obj/gpio.o obj/lcd.o 


ifdef DOOM
	LIBS += $(LIB)/doom/doom.a 
else
endif

ifdef GDBSTUB
	LIBS += $(LIB)/gdbstub/gdbstub.a 
else
endif


#ALLOBJS    = $(foreach F,$(SOURCESS) ,$(call S2O,$(F)))
#ALLOBJS    += $(foreach F,$(SOURCESC) $(SOURCESCPP),$(call C2O,$(F)))
SUBDIRS    = $(shell find $(SRC) -type d)
OBJSUBDIRS = $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))
PROJECT_INC_PATHS = -I$(SRC) -I$(LIB)/minlzlib -I$(LIB)/minlzlib/src -I$(LIB)/doom/src -I$(LIB)/gdbstub/src -I$(LIB)/dlmalloc/src 


.PHONY: info

all: $(RES).bin

$(RES): $(OBJSUBDIRS) $(ALLOBJS) 
	$(MAKE) -C lib 
	$(CC) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(ALLOBJS) $(LIBS) -o $(RES) 

$(foreach F,$(SOURCESS),$(eval $(call COMPILE,$(CC),$(call S2O,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS))))
$(foreach F,$(SOURCESC),$(eval $(call COMPILE,$(CC),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS) $(PROJECT_INC_PATHS))))

$(OBJSUBDIRS):
	$(MKDIR) $(OBJSUBDIRS)

clean:
	$(MAKE) -C lib clean
	rm $(ALLOBJS)

cleanall:
	$(MAKE) -C lib cleanall
	rm main*
	rm $(ALLOBJS)


$(RES).bin: $(RES)
	$(OBJCOPY) -O binary $< $@
	truncate --size=8M $@

flash:
	sudo flashrom -p ft2232_spi:type=2232H,port=A -c W25Q64JV-.Q -w main.out.bin
rung:
	qemu-mips -L /usr/mips-linux-gnu/ -g 1234 ./main.out
rune:
	qemu-mips-static -L /usr/mips-linux-gnu/ ./main.out


#DEBUG
info:
	$(info $(SOURCESC))
	#$(info $(SOURCESCPP))
	#$(info $(SUBDIRS))
	#$(info $(OBJSUBDIRS))
	#$(info $(ALLOBJS))




