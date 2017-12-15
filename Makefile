BUILD_DIR  ?= build/
TARGET     ?= STM32L0X2
VERSION    ?= 1

STM_DIR     = lib/stm/
BLOCKS_DIR  = lib/blocks/

include $(STM_DIR)init.mk
include $(BLOCKS_DIR)init.mk

CFILES += main.c
INCLUDE_PATHS += .

include $(STM_DIR)stm.mk
include $(BLOCKS_DIR)blocks.mk
