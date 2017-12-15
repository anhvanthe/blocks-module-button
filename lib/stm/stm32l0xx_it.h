/*
 * Blocks Module Firmware
 *
 * Copyright (C) 2016 BayLibre, SAS - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Author(s) :
 * Neil Armstrong <narmstrong@baylibre.com>
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L0xx_IT_H
#define __STM32L0xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Exported functions ------------------------------------------------------- */

void SysTick_Handler(void);
void I2C1_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32L0xx_IT_H */
