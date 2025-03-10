# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  RX72N Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	test

DEVICE		=	R5F572NN

FATFS_VER	=	ff14/source

BUILD		=	release
# BUILD		=	debug

VPATH		=	../

ASOURCES	=	common/start.s

CSOURCES	=	common/init.c \
				common/vect.c \
				common/syscalls.c \
				tinyusb/src/tusb.c \
				tinyusb/src/common/tusb_fifo.c \
				tinyusb/src/device/usbd.c \
				tinyusb/src/device/usbd_control.c \
				tinyusb/src/class/audio/audio_device.c \
				tinyusb/src/class/cdc/cdc_device.c \
				tinyusb/src/class/dfu/dfu_device.c \
				tinyusb/src/class/dfu/dfu_rt_device.c \
				tinyusb/src/class/hid/hid_device.c \
				tinyusb/src/class/midi/midi_device.c \
				tinyusb/src/class/msc/msc_device.c \
				tinyusb/src/class/net/ecm_rndis_device.c \
				tinyusb/src/class/net/ncm_device.c \
				tinyusb/src/class/usbtmc/usbtmc_device.c \
				tinyusb/src/class/video/video_device.c \
				tinyusb/src/class/vendor/vendor_device.c \
				hid_app.c \
				tinyusb/src/class/cdc/cdc_host.c \
				tinyusb/src/class/hid/hid_host.c \
				tinyusb/src/class/msc/msc_host.c \
				tinyusb/src/host/hub.c \
				tinyusb/src/host/usbh.c \
				tinyusb/src/host/usbh_control.c \
				tinyusb/src/portable/ohci/ohci.c

PSOURCES	=	main.cpp \
 				dcd_usb.cpp \
 				hcd_usb.cpp

USER_LIBS	=	supc++

LDSCRIPT	=	../RX72N/$(DEVICE).ld

# USER_DEFS	=	SIG_RX72N CFG_TUSB_MCU=OPT_MCU_RX72N
USER_DEFS	=	SIG_RX72N CFG_TUSB_MCU=OPT_MCU_RX72N

# Renesas GNU-RX gcc compiler version check
TARGET_ISA_TEXT := $(shell rx-elf-gcc --target-help | grep ISA)

# AS_DEFS		=	--defsym NOT_USER=1
ifeq ($(TARGET_ISA_TEXT), )
# gcc-7.5.0 current gcc source build
AS_DEFS		=	-mcpu=rx600
CC_DEFS		=	-mcpu=rx600 -Wa,-mcpu=rxv2
CP_DEFS		=	-mcpu=rx600
else # Renesas GNU-RX gcc
AS_DEFS		=	-misa=v3
CC_DEFS		=	-misa=v3
# CP_DEFS		=	-misa=v3 -mdfpu -mtfu=intrinsic,mathlib
CP_DEFS		=	-misa=v3 -mtfu=intrinsic,mathlib
# CP_DEFS		=	-misa=v3 -mdfpu
endif

# Include path for each environment
ifeq ($(OS),Windows_NT)
SYSTEM := WIN
LOCAL_PATH  =   /mingw64
else
  UNAME := $(shell uname -s)
  ifeq ($(UNAME),Linux)
    SYSTEM := LINUX
    LOCAL_PATH = /usr/local
  endif
  ifeq ($(UNAME),Darwin)
    SYSTEM := OSX
    OSX_VER := $(shell sw_vers -productVersion | sed 's/^\([0-9]*.[0-9]*\).[0-9]*/\1/')
    LOCAL_PATH = /opt/local
  endif
endif

INC_SYS     =   $(LOCAL_PATH)/include

INC_APP		=	. ../ \
				../RX600/drw2d/inc/tes \
				../tinyusb/src

LIB_ROOT	=	../RX600/drw2d ../libmad ../zlib ../libpng

AS_OPT		=

CP_OPT		=	-Wall -Werror \
				-Wno-unused-variable \
				-Wno-unused-function \
				-Wno-stringop-truncation \
				-fno-exceptions

CC_OPT		=	-Wall -Werror \
                -Wno-unused-variable \
                -Wno-unused-function \
                -Wno-maybe-uninitialized \
                -Wno-unused-but-set-variable \
                -fno-exceptions

#				-fdata-sections \
				-ffunction-sections \
				-fsingle-precision-constant \
				-fno-strict-aliasing

ifeq ($(BUILD),debug)
    CC_OPT += -g -DDEBUG
    CP_OPT += -g -DDEBUG
	OPTIMIZE = -O0
endif

ifeq ($(BUILD),release)
    CC_OPT += -DNDEBUG
    CP_OPT += -DNDEBUG
	OPTIMIZE = -O3
endif

SYSINCS		=	$(addprefix -I, $(INC_SYS))
APPINCS		=	$(addprefix -I, $(INC_APP))
AINCS		=	$(SYSINCS) $(APPINCS)
CINCS		=	$(SYSINCS) $(APPINCS)
PINCS		=	$(SYSINCS) $(APPINCS)
LIBINCS		=	$(addprefix -L, $(LIB_ROOT))
DEFS		=	$(addprefix -D, $(USER_DEFS))
LIBS		=	$(addprefix -l, $(USER_LIBS))

# You should not have to change anything below here.
AS			=	rx-elf-as
CC			=	rx-elf-gcc
CP			=	rx-elf-g++
AR			=	rx-elf-ar
LD			=	rx-elf-ld
OBJCOPY		=	rx-elf-objcopy
OBJDUMP		=	rx-elf-objdump
SIZE		=	rx-elf-size

AFLAGS		=	$(AS_OPT) $(AS_DEFS)
CFLAGS		=	-std=gnu99 $(CC_OPT) $(OPTIMIZE) $(CC_DEFS) $(DEFS)
PFLAGS		=	-std=c++17 $(CP_OPT) $(OPTIMIZE) $(CP_DEFS) $(DEFS)

override LDFLAGS = $(MCU_TARGET) -nostartfiles -Wl,-Map,$(TARGET).map -T $(LDSCRIPT)

OBJCOPY_OPT	=	--srec-forceS3 --srec-len 32

OBJECTS	=	$(addprefix $(BUILD)/,$(patsubst %.s,%.o,$(ASOURCES))) \
			$(addprefix $(BUILD)/,$(patsubst %.c,%.o,$(CSOURCES))) \
			$(addprefix $(BUILD)/,$(patsubst %.cpp,%.o,$(PSOURCES)))

DOBJECTS =	$(addprefix $(BUILD)/,$(patsubst %.c,%.o,$(CSOURCES))) \
			$(addprefix $(BUILD)/,$(patsubst %.cpp,%.o,$(PSOURCES)))

DEPENDS =   $(patsubst %.o,%.d, $(DOBJECTS))

.PHONY: all clean
.SUFFIXES :
.SUFFIXES : .rc .hpp .s .h .c .cpp .d .o

all: $(BUILD) $(TARGET).elf text

$(TARGET).elf: $(OBJECTS) $(LDSCRIPT) Makefile
	$(CC) $(LDFLAGS) $(LIBINCS) -o $@ $(OBJECTS) $(LIBS)
	$(SIZE) $@

$(BUILD)/%.o: %.s
	mkdir -p $(dir $@); \
	$(AS) -c $(AOPT) $(AFLAGS) $(AINCS) -o $@ $<

$(BUILD)/%.o : %.c
	mkdir -p $(dir $@); \
	$(CC) -c $(COPT) $(CFLAGS) $(CINCS) $(CCWARN) -o $@ $<

$(BUILD)/%.o : %.cpp
	mkdir -p $(dir $@); \
	$(CP) -c $(POPT) $(PFLAGS) $(PINCS) $(CPWARN) -o $@ $<

$(BUILD)/%.d: %.c
	mkdir -p $(dir $@); \
	$(CC) -MM -DDEPEND_ESCAPE $(COPT) $(CFLAGS) $(APPINCS) $< \
	| sed 's/$(notdir $*)\.o:/$(subst /,\/,$(patsubst %.d,%.o,$@) $@):/' > $@ ; \
	[ -s $@ ] || rm -f $@

$(BUILD)/%.d: %.cpp
	mkdir -p $(dir $@); \
	$(CP) -MM -DDEPEND_ESCAPE $(POPT) $(PFLAGS) $(APPINCS) $< \
	| sed 's/$(notdir $*)\.o:/$(subst /,\/,$(patsubst %.d,%.o,$@) $@):/' > $@ ; \
	[ -s $@ ] || rm -f $@

clean:
	rm -rf $(BUILD) $(TARGET).elf $(TARGET).mot $(TARGET).lst $(TARGET).map

clean_depend:
	rm -f $(DEPENDS)

lst:  $(TARGET).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images

text: mot lst

bin: $(TARGET).bin
mot: $(TARGET).mot
lst: $(TARGET).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

%.mot: %.elf
	$(OBJCOPY) $(OBJCOPY_OPT) -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@
#	$(OBJCOPY) -j .vects -j .text -j .data -O binary $< $@

tarball:
	tar cfvz $(subst .elf,,$(TARGET))_$(shell date +%Y%m%d%H).tgz \
	*.[hc]pp Makefile ../common/*/*.[hc]pp ../common/*/*.[hc]

bin_zip:
	$(LK) $(LFLAGS) $(LIBS) $(OBJECTS) $(ICON_OBJ) $(LIBN) -mwindows -o $(TARGET) 
	rm -f $(subst .exe,,$(TARGET))_$(shell date +%Y%m%d%H)_bin.zip
	zip $(subst .exe,,$(TARGET))_$(shell date +%Y%m%d%H)_bin.zip *.exe *.dll res/*.*

run:
	rx_prog -d RX72N --progress --erase --write --verify $(TARGET).mot

-include $(DEPENDS)
