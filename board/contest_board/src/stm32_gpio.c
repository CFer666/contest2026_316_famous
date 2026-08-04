/****************************************************************************
 * Contest 2026 team 316 - STM32F103ZET6 GPIO Driver
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>
#include <nuttx/kmalloc.h>

#include <stm32.h>
#include <arch/board/board.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* LED Pin Definitions (using definitions from board.h) */
/* GPIO_LED1, GPIO_LED2, GPIO_LED3 are defined in board.h */

/* Button Pin Definition */
/* GPIO_BTN_USER is defined in board.h */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32_gpio_initialize
 *
 * Description:
 *   Initialize GPIO pins for LEDs and buttons.
 *
 ****************************************************************************/

int stm32_gpio_initialize(void)
{
  /* Configure LED pins as output */

  stm32_configgpio(GPIO_LED1);
  stm32_configgpio(GPIO_LED2);
  stm32_configgpio(GPIO_LED3);

  /* Configure button pin as input with pull-up */

  stm32_configgpio(GPIO_BTN_USER);

  return OK;
}

/****************************************************************************
 * Name: stm32_gpio_set_led
 *
 * Description:
 *   Set LED state.
 *
 ****************************************************************************/

int stm32_gpio_set_led(int led_num, bool state)
{
  uint32_t pin;

  switch (led_num)
    {
      case 0:
        pin = GPIO_LED1;
        break;
      case 1:
        pin = GPIO_LED2;
        break;
      case 2:
        pin = GPIO_LED3;
        break;
      default:
        return -EINVAL;
    }

  stm32_gpiowrite(pin, state);
  return OK;
}

/****************************************************************************
 * Name: stm32_gpio_read_button
 *
 * Description:
 *   Read button state.
 *
 ****************************************************************************/

int stm32_gpio_read_button(void)
{
  return stm32_gpioread(GPIO_BTN_USER) ? 1 : 0;
}
