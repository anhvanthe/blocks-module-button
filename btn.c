/* btn.c - (c) 2017 Blocks Wearables Ltd. */
#include "btn.h"
#include "cy8cmbr3108.h"
#include <stm32l0xx.h>
#include <stm32l0xx_hal_gpio.h>
#include <stm32l0xx_hal_dma.h>
#include <stm32l0xx_hal_i2c.h>
#include <stm32l0xx_hal_rcc_ex.h>

static I2C_HandleTypeDef i2c_2;

bool cy8cmbr3_i2c_read(uint8_t i2cAddress, uint8_t* buffer, uint16_t size) {
	uint8_t tries = 0;

	while (tries++ != 5 &&
		HAL_I2C_Master_Receive(&i2c_2, (i2cAddress << 1) | 0x01, buffer, size, 10) != HAL_OK) { }
	return tries <= 5;
}

bool cy8cmbr3_i2c_write(uint8_t i2cAddress, const uint8_t* data, uint16_t size) {
	uint8_t tries = 0;

	while (tries++ != 5 &&
		HAL_I2C_Master_Transmit(&i2c_2, i2cAddress << 1, data, size, 10) != HAL_OK) { }

	return tries <= 5;
}

void EXTI0_1_IRQHandler(void) {
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_0) {
		button_handle_press();
	}
}

bool button_init(void) {
	// Configure GPIO as I2C
	GPIO_InitTypeDef GPIO_InitStruct = {
		.Pin = GPIO_PIN_11 | GPIO_PIN_10,
		.Mode = GPIO_MODE_AF_OD,
		.Pull = GPIO_PULLUP,
		.Speed = GPIO_SPEED_HIGH,
		.Alternate = GPIO_AF6_I2C2,
	};
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	__I2C2_CLK_ENABLE();

	// I2C setup
	i2c_2 = (I2C_HandleTypeDef){
		.Instance = I2C2,
		.Init.Timing = 0x2000090E,
		.Init.OwnAddress1 = 0,
		.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT,
		.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED,
		.Init.OwnAddress2 = 0,
		.Init.OwnAddress2Masks = I2C_OA2_NOMASK,
		.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED,
		.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED
	};
	if (HAL_I2C_Init(&i2c_2) != HAL_OK) return false;

	if (HAL_I2CEx_AnalogFilter_Config(&i2c_2, I2C_ANALOGFILTER_ENABLED)
		!= HAL_OK) return false;

	// Set up pin PB0 for touch interrupt
	GPIO_InitTypeDef pinCfg = {
		.Pin  = GPIO_PIN_0,
		.Mode = GPIO_MODE_IT_FALLING,
		.Pull = GPIO_PULLUP,
	};
	HAL_GPIO_Init(GPIOB, &pinCfg);

	// Enable interrupt
	HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

	return cy8cmbr3_write_config(CY8CMBR3_IC2_ADDR_DEFAULT);
}
