/****************************************************************************
 * Contest 2026 team 316 - STM32F103ZET6 Board Header
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to you under the Apache License, Version
 * 2.0 (the "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied.  See the License for the specific language governing
 * permissions and limitations under the License.
 *
 ****************************************************************************/

#ifndef __BOARDS_ARM_STM32_CONTEST2026_316_BOARD_INCLUDE_BOARD_H
#define __BOARDS_ARM_STM32_CONTEST2026_316_BOARD_INCLUDE_BOARD_H

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Clock Configuration ******************************************************/

/* On-board crystal frequency is 8MHz (HSE) */
#define STM32_BOARD_XTAL        8000000UL

/* PLL source is HSE/1, PLL multiplier is 9:
 *      PLL frequency is 8MHz (XTAL) x 9 = 72MHz
 */
#define STM32_CFGR_PLLSRC       RCC_CFGR_PLLSRC
#define STM32_CFGR_PLLXTPRE     0
#define STM32_CFGR_PLLMUL       RCC_CFGR_PLLMUL_CLKx9
#define STM32_PLL_FREQUENCY     (9 * STM32_BOARD_XTAL)

/* Use the PLL and set the SYSCLK source to be the PLL */
#define STM32_SYSCLK_SW         RCC_CFGR_SW_PLL
#define STM32_SYSCLK_SWS        RCC_CFGR_SWS_PLL
#define STM32_SYSCLK_FREQUENCY  STM32_PLL_FREQUENCY

/* AHB clock (HCLK) is SYSCLK (72MHz) */
#define STM32_RCC_CFGR_HPRE     RCC_CFGR_HPRE_SYSCLK
#define STM32_HCLK_FREQUENCY    STM32_PLL_FREQUENCY

/* APB2 clock (PCLK2) is HCLK (72MHz) */
#define STM32_RCC_CFGR_PPRE2    RCC_CFGR_PPRE2_HCLK
#define STM32_PCLK2_FREQUENCY   STM32_HCLK_FREQUENCY
#define STM32_APB2_CLKIN        (STM32_PCLK2_FREQUENCY)

/* APB1 clock (PCLK1) is HCLK/2 (36MHz, max 36 MHz) */
#define STM32_RCC_CFGR_PPRE1    RCC_CFGR_PPRE1_HCLKd2
#define STM32_PCLK1_FREQUENCY   (STM32_HCLK_FREQUENCY / 2)

/* APB1 timers 2-7 will be twice PCLK1 */
#define STM32_APB1_TIM2_CLKIN   (2 * STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM3_CLKIN   (2 * STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM4_CLKIN   (2 * STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM5_CLKIN   (2 * STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM6_CLKIN   (2 * STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM7_CLKIN   (2 * STM32_PCLK1_FREQUENCY)

/* APB2 timers 1 and 8 will receive PCLK2 */
#define STM32_APB2_TIM1_CLKIN   (STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM8_CLKIN   (STM32_PCLK2_FREQUENCY)

/* Timer Frequencies, if APBx is set to 1, frequency is same to APBx
 * otherwise frequency is 2xAPBx.  Note: TIM1,8 are on APB2, others on APB1
 */
#define BOARD_TIM1_FREQUENCY    STM32_HCLK_FREQUENCY
#define BOARD_TIM2_FREQUENCY    STM32_HCLK_FREQUENCY
#define BOARD_TIM3_FREQUENCY    STM32_HCLK_FREQUENCY
#define BOARD_TIM4_FREQUENCY    STM32_HCLK_FREQUENCY

/* LSI (Low-Speed Internal) oscillator is ~40kHz on the STM32F103.  It is
 * used as the clock source for the independent watchdog (IWDG).
 */
#define STM32_LSI_FREQUENCY     40000

/* Peripheral Pin Mapping **************************************************/
/* NOTE: The USART/SPI/I2C/ADC/TIM peripheral pins (GPIO_USART1_*, GPIO_SPI1_*,
 * GPIO_I2C1_*, GPIO_ADC1_IN*, GPIO_TIM1_CH*OUT, ...) are provided by the chip
 * pinmap (hardware/stm32f103z_pinmap_legacy.h) and are intentionally NOT
 * redefined here.  Only board-specific pins are defined below.
 */

/* LED Configuration ********************************************************/

/* LEDs on PB0, PB1, PB5 */
#define GPIO_LED1       (GPIO_OUTPUT | GPIO_CNF_OUTPP | GPIO_MODE_50MHz | \
                         GPIO_OUTPUT_CLEAR | GPIO_PORTB | GPIO_PIN0)
#define GPIO_LED2       (GPIO_OUTPUT | GPIO_CNF_OUTPP | GPIO_MODE_50MHz | \
                         GPIO_OUTPUT_CLEAR | GPIO_PORTB | GPIO_PIN1)
#define GPIO_LED3       (GPIO_OUTPUT | GPIO_CNF_OUTPP | GPIO_MODE_50MHz | \
                         GPIO_OUTPUT_CLEAR | GPIO_PORTB | GPIO_PIN5)

/* Button Configuration ****************************************************/

/* USER button on PA0, active-low (internal pull-up) */
#define GPIO_BTN_USER   (GPIO_INPUT | GPIO_CNF_INPULLUP | GPIO_MODE_INPUT | \
                         GPIO_PORTA | GPIO_PIN0)

/* SPI1 Chip Select ********************************************************/

/* Software-controlled SPI1 chip select on PA4 (active-low) */
#define GPIO_SPI1_CS    (GPIO_OUTPUT | GPIO_CNF_OUTPP | GPIO_MODE_50MHz | \
                         GPIO_OUTPUT_SET | GPIO_PORTA | GPIO_PIN4)

/* JTAG/SWD Configuration **************************************************/

/* Enable SWD (PA13=SWDIO, PA14=SWCLK), disable JTAG to free PB3/PB4 */
#define GPIO_SWDIO      (GPIO_ALT | GPIO_CNF_AFPP | GPIO_MODE_50MHz | \
                         GPIO_PORTA | GPIO_PIN13)
#define GPIO_SWCLK      (GPIO_ALT | GPIO_CNF_AFPP | GPIO_MODE_50MHz | \
                         GPIO_PORTA | GPIO_PIN14)

#endif /* __BOARDS_ARM_STM32_CONTEST2026_316_BOARD_INCLUDE_BOARD_H */
