C_FLAGS += -mfloat-abi=soft -mcpu=cortex-m0plus -march=armv6-m -DSTM32L052xx

PWD = $(STM_DIR)

STM_SRC_FILES = \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_pwr_ex.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_pwr.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rtc.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash_ex.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_dma.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rtc_ex.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_gpio.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rcc_ex.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_uart_ex.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_crc.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_crc_ex.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_i2c.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_i2c_ex.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash_ramfunc.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rcc.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_cortex.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_uart.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_tim.c \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_tim_ex.c \
    $(PWD)/system_stm32l0xx.c \
    $(PWD)/stm32l0xx_hal_msp.c \
    $(PWD)/stm32l0xx_it.c

STM_GCC_FILES = \
    $(PWD)/startup_stm32l052xx.s 

STM_INCLUDE_PATHS += \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Inc \
    $(PWD)/hal/STM32L0xx_HAL_Driver/Inc/Legacy \
    $(PWD)/hal/CMSIS/Device/ST/STM32L0xx/Include

# Ideally this directory would hold a "default" linker script for the 
# platform in case one is not provided. 

# LD_LINKER_FILE = X.ld
