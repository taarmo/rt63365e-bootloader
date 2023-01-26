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
LINKER_SCRIPT = ./stub.ld

CC = $(GCC_PATH)mips-linux-gnu-gcc

MIPS_FLAGS = -march=mips32r2
CFLAGS = -O3 -EB $(MIPS_FLAGS) -std=c99 -fno-builtin -Wall -pedantic -mno-abicalls -fno-pic -fno-stack-protector -fomit-frame-pointer 
LD_FLAGS = -nostartfiles -nostdlib -static -Wl,-z,max-page-size=0x1000



#-fno-pic -mno-abicalls importantes

SRC      = src
OBJ      = obj
MKDIR	 = mkdir -p

#ifdef DEBUG
CFLAGS += -g
#else
#	CFLAGS += -O3
#endif

MKDIR = mkdir -p
SOURCESC = $(SRC)/main.c $(SRC)/utils.c $(SRC)/uart.c $(SRC)/vsprintf.c
SOURCESS = $(SRC)/start.S $(SRC)/utils_asm.S


ALLOBJS    = obj/start.o obj/main.o obj/utils.o obj/utils_asm.o obj/uart.o obj/vsprintf.o
SUBDIRS    = $(shell find $(SRC) -type d)
OBJSUBDIRS = $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))
PROJECT_INC_PATHS = -I$(SRC) 


.PHONY: info

all: $(RES)

$(RES): $(OBJSUBDIRS) $(ALLOBJS) 
	$(CC) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(ALLOBJS) -o $(RES) 

$(foreach F,$(SOURCESS),$(eval $(call COMPILE,$(CC),$(call S2O,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS))))
$(foreach F,$(SOURCESC),$(eval $(call COMPILE,$(CC),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS) $(PROJECT_INC_PATHS))))

$(OBJSUBDIRS):
	$(MKDIR) $(OBJSUBDIRS)

clean:
	rm $(ALLOBJS)

cleanall:
	rm main*
	rm $(ALLOBJS)

rung:
	qemu-mips -L /usr/mips-linux-gnu/ -g 1234 ./main.out
rune:
	qemu-mips-static -L /usr/mips-linux-gnu/ ./main.out


#DEBUG
info:
	$(info $(SOURCESS))
	$(info $(SOURCESCPP))
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLOBJS))


