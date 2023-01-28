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

RES = minlzlib.a

GCC_PATH = /usr/bin/
LINKER_SCRIPT     = ./hg532s_bootloader.ld

CCPP = $(GCC_PATH)mips-linux-gnu-g++
CC = $(GCC_PATH)mips-linux-gnu-gcc
AR       = mips-linux-gnu-ar
OBJCOPY = mips-linux-gnu-objcopy

MIPS_FLAGS = -march=mips32r2

#CFLAGS = -EB $(MIPS_FLAGS) -std=c11 -fno-builtin -Wall -pedantic -nostdlib -mno-abicalls -fno-common -fno-PIE -fno-stack-protector -fomit-frame-pointer -ffunction-sections -fdata-sections -nostdinc -ffreestanding -isystem sysinc -isystem $(shell $(CC) --print-file-name=include) 

CFLAGS = -EB $(MIPS_FLAGS) -std=c11 -fno-builtin -Wall -pedantic -nostdlib -mno-abicalls -fno-common -fno-PIE -fno-stack-protector -fomit-frame-pointer -nostdinc -ffreestanding -isystem sysinc -isystem $(shell $(CC) --print-file-name=include) -Wno-multichar 
#CPPFLAGS = -Wall -pedantic

SRC      = src
OBJ      = obj
MKDIR	 = mkdir -p

#ifdef DEBUG
CFLAGS += -g
#else
#	CFLAGS += -O3
#endif

ARFLAGS  = -cr 

MKDIR = mkdir -p
#SOURCESCPP = $(shell find $(SRC)/ -type f -iname *.cpp)
SOURCESC = $(shell find $(SRC)/ -type f -iname *.c)
#SOURCESC = src/main_ram.c src/config_uart.c src/print.c src/write_uart.c
SOURCESS = $(shell find $(SRC)/ -type f -iname *.S)

ALLOBJS    = obj/dictbuf.o obj/inputbuf.o obj/lzma2dec.o obj/lzmadec.o obj/rangedec.o obj/xzcrc.o obj/xzstream.o 

#ALLOBJS    = $(foreach F,$(SOURCESS) ,$(call S2O,$(F)))
#ALLOBJS    += $(foreach F,$(SOURCESC) $(SOURCESCPP),$(call C2O,$(F)))
SUBDIRS    = $(shell find $(SRC) -type d)
OBJSUBDIRS = $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))
PROJECT_INC_PATHS = -I$(SRC) 


.PHONY: info

all: $(RES)

$(RES): $(OBJSUBDIRS) $(ALLOBJS) 
	$(AR) $(ARFLAGS) $(RES) $(ALLOBJS) 

#$(foreach F,$(SOURCESCPP),$(eval $(call COMPILE,$(CCPP),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CPPFLAGS) $(PROJECT_INC_PATHS))))
$(foreach F,$(SOURCESS),$(eval $(call COMPILE,$(CC),$(call S2O,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS))))
$(foreach F,$(SOURCESC),$(eval $(call COMPILE,$(CC),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS) $(PROJECT_INC_PATHS))))

$(OBJSUBDIRS):
	$(MKDIR) $(OBJSUBDIRS)

clean:
	rm $(ALLOBJS)

cleanall:
	rm minlzlib.a
	rm $(ALLOBJS)


#DEBUG
info:
	$(info $(SOURCESC))
	#$(info $(SOURCESCPP))
	#$(info $(SUBDIRS))
	#$(info $(OBJSUBDIRS))
	#$(info $(ALLOBJS))


