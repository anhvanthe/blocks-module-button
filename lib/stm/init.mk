STM_DIR ?= $(shell pwd)

PREFIX  ?= arm-none-eabi-
CC       = $(PREFIX)gcc
LD       = $(PREFIX)ld

C_FLAGS += \
    -mabi=aapcs -mthumb -mlittle-endian -mno-unaligned-access \
    -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-builtin \
    -w -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wpointer-arith \
    -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g3 -ggdb -std=gnu11 -pedantic

LD_FLAGS += \
    -Os -nostartfiles -nodefaultlibs -nostdlib -Xlinker \
    --gc-sections -Wl,-Map,"$(BUILD_DIR)/$(TARGET).map" --specs=nano.specs
