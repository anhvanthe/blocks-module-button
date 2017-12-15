C_FLAGS += -mcpu=cortex-m4 -march=armv7e-m -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -DSTM32L476xx

PWD = $(STM_DIR)

STM_SRC_FILES = \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc_ex.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc_ex.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim.c \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim_ex.c \
    $(PWD)/system_stm32l4xx.c \
    $(PWD)/stm32l4xx_hal_msp.c \
    $(PWD)/stm32l4xx_it.c

STM_GCC_FILES = \
    $(PWD)/startup_stm32l476xx.s

STM_INCLUDE_PATHS = \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Inc \
    $(PWD)/hal/STM32L4xx_HAL_Driver/Inc/Legacy \
    $(PWD)/hal/CMSIS/Device/ST/STM32L4xx/Include

# Ideally this directory would hold a "default" linker script for the 
# platform in case one is not provided. 

# LD_LINKER_FILE = X.ld
