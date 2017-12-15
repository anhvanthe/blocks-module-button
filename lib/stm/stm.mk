PWD=$(STM_DIR)

ifeq ($(TARGET),STM32L0X2)
  include $(PWD)/STM32L0X2_HAL.mk
endif

ifeq ($(TARGET),STM32L4X6)
  include $(PWD)STM32L4X6_HAL.mk
endif

LD_FLAGS += -T "$(LD_LINKER_FILE)"

STM_INCLUDE_PATHS += \
    $(PWD) \
    $(PWD)hal/CMSIS/Include

INCLUDE_PATHS += $(STM_INCLUDE_PATHS)

INCLUDES = $(STM_INCLUDE_PATHS:%=-I%)

ifeq ($(STM_COMPILE), 1)
  include $(PWD)compile.mk
endif
