# ==============================================================================
# Initialization
# ==============================================================================

-include .env.mk

export FXCGSDK

ifeq ($(strip $(FXCGSDK)),)
$(error FXCGSDK is not set in your environment. \
	Run `export FXCGSDK=<PATH_TO_SDK>` or add `FXCGSDK=<PATH_TO_SDK>` to '.env.mk')
endif

# Clear implicit built-in rules
.SUFFIXES:

# SDK rules
include $(FXCGSDK)/toolchain/prizm_rules

# ==============================================================================
# Build configuration
# ==============================================================================

OUTPUT_NAME	:= libcalctype
BUILD_DIR	:= build
SOURCE_DIRS	:= src src/$(PLATFORM)
DATA_DIRS	:= data
INCLUDE_DIRS	:= include

# ==============================================================================
# Flags
# ==============================================================================

# -flto in CFLAGS and LDFLAGS enables link-time optimization (LTO). This usually
# allows the compiler to generate smaller and/or faster code, however may expose
# bugs in the source code that wouldn't cause any trouble without LTO enabled.
CFLAGS		= -std=c17 -Os -Wall $(MACHDEP) $(INCLUDE) -ffunction-sections \
			-fdata-sections -funroll-loops -fno-trapping-math \
			-fno-trapv -Wno-switch -flto

LDFLAGS		= $(MACHDEP) -T$(FXCGSDK)/toolchain/prizm.x -Wl,-static \
			-Wl,-gc-sections -flto

# Libraries
LIBS		:= -lc -lfxcg -lgcc
LIB_DIRS	:=

# ==============================================================================
# Output
# ==============================================================================

## If --------------------------------------------------------------------------
ifneq ($(BUILD_DIR),$(notdir $(CURDIR)))
## -----------------------------------------------------------------------------

export OUTPUT	:= $(CURDIR)/$(OUTPUT_NAME)

export VPATH	:= $(foreach dir,$(SOURCE_DIRS),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA_DIRS),$(CURDIR)/$(dir))

export DEPSDIR	:= $(CURDIR)/$(BUILD_DIR)

# Source files
CFILES		:= $(foreach dir,$(SOURCE_DIRS),\
			$(notdir $(wildcard $(dir)/*.c)))
CXXFILES	:= $(foreach dir,$(SOURCE_DIRS),\
			$(notdir $(wildcard $(dir)/*.cc)))
sFILES		:= $(foreach dir,$(SOURCE_DIRS),\
			$(notdir $(wildcard $(dir)/*.s)))
SFILES		:= $(foreach dir,$(SOURCE_DIRS),\
			$(notdir $(wildcard $(dir)/*.S)))
BINFILES	:= $(foreach dir,$(DATA_DIRS),$(notdir $(wildcard $(dir)/*.*)))

# Linker
ifeq ($(strip $(CXXFILES)),)
export LD	:= $(CC)
else
export LD	:= $(CXX)
endif

# Objects
export OFILES	:= $(addsuffix .o,$(BINFILES)) $(CFILES:.c=.o) \
			$(CXXFILES:.cc=.o) $(sFILES:.s=.o) $(SFILES:.S=.o)

# Include path flags
export INCLUDE	:= $(foreach dir,$(INCLUDE_DIRS),-iquote $(CURDIR)/$(dir)) \
			$(foreach dir,$(LIB_DIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD_DIR) -I$(LIBFXCG_INC)

# Library path flags
export LIBPATHS	:= $(foreach dir,$(LIB_DIRS),-L$(dir)/lib) \
			-L$(LIBFXCG_LIB)

### ============================================================================
### Targets
### ============================================================================

.PHONY: all install uninstall clean

all: $(BUILD_DIR)
	@make --no-print-directory -C $(BUILD_DIR) -f $(CURDIR)/Makefile

$(BUILD_DIR):
	@mkdir $@

install:
ifeq ($(strip $(INSTALL_PREFIX)),)
$(error INSTALL_PREFIX is not set in your environment. \
	Run `export INSTALL_PREFIX=<PATH>` or add `INSTALL_PREFIX=<PATH>` to '.env.mk')
endif
	install -m 644 "$(OUTPUT).a" "$(INSTALL_PREFIX)/lib"
	cp -R -T include "$(INSTALL_PREFIX)/include/calctype"

uninstall:
ifeq ($(strip $(INSTALL_PREFIX)),)
$(error INSTALL_PREFIX is not set in your environment. \
	Run `export INSTALL_PREFIX=<PATH>` or add `INSTALL_PREFIX=<PATH>` to '.env.mk')
endif
	$(call rmdir,$(INSTALL_PREFIX)/include/calctype)
	$(call rm,$(INSTALL_PREFIX)/lib/$(OUTPUT_NAME).a)


clean:
	$(call rmdir,$(BUILD_DIR))
	$(call rm,$(OUTPUT).a)

## Else ------------------------------------------------------------------------
else
## -----------------------------------------------------------------------------

DEPENDS := $(OFILES:.o=.d)

$(OUTPUT).a: $(OFILES)

-include $(DEPENDS)

## End if ----------------------------------------------------------------------
endif
## -----------------------------------------------------------------------------
