#
#             LUFA Library
#     Copyright (C) Dean Camera, 2021.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

# Run "make help" for target help.

MCU          = atmega32u4
ARCH         = AVR8
BOARD        = NONE
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = DanceMicro
SRC          = $(TARGET).c Descriptors.c ADCSensors.c
SRC 		 += $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS)
LUFA_PATH    = ../lufa/LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig/ 
LD_FLAGS     =



# ------- PANEL SENSITIVIES ------- #
PRESS_THRESHOLD_A0 ?= 300
RELEASE_THRESHOLD_A0 ?= 250
PRESS_THRESHOLD_A1 ?= 300
RELEASE_THRESHOLD_A1 ?= 250
PRESS_THRESHOLD_A2 ?= 300
RELEASE_THRESHOLD_A2 ?= 250
PRESS_THRESHOLD_A3 ?= 300
RELEASE_THRESHOLD_A3 ?= 250
# --------------------------------- #



CC_FLAGS += -DPRESS_THRESHOLD_A0=$(PRESS_THRESHOLD_A0) -DRELEASE_THRESHOLD_A0=$(RELEASE_THRESHOLD_A0)
CC_FLAGS += -DPRESS_THRESHOLD_A1=$(PRESS_THRESHOLD_A1) -DRELEASE_THRESHOLD_A1=$(RELEASE_THRESHOLD_A1)
CC_FLAGS += -DPRESS_THRESHOLD_A2=$(PRESS_THRESHOLD_A2) -DRELEASE_THRESHOLD_A2=$(RELEASE_THRESHOLD_A2)
CC_FLAGS += -DPRESS_THRESHOLD_A3=$(PRESS_THRESHOLD_A3) -DRELEASE_THRESHOLD_A3=$(RELEASE_THRESHOLD_A3)

# Default target
all:

# Include LUFA-specific DMBS extension modules
DMBS_LUFA_PATH ?= $(LUFA_PATH)/Build/LUFA
include $(DMBS_LUFA_PATH)/lufa-sources.mk
include $(DMBS_LUFA_PATH)/lufa-gcc.mk

# Include common DMBS build system modules
DMBS_PATH      ?= $(LUFA_PATH)/Build/DMBS/DMBS
include $(DMBS_PATH)/core.mk
include $(DMBS_PATH)/cppcheck.mk
include $(DMBS_PATH)/doxygen.mk
include $(DMBS_PATH)/dfu.mk
include $(DMBS_PATH)/gcc.mk
include $(DMBS_PATH)/hid.mk
include $(DMBS_PATH)/avrdude.mk
include $(DMBS_PATH)/atprogram.mk
