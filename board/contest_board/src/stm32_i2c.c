/****************************************************************************
 * Contest 2026 team 316 - STM32F103ZET6 I2C Driver
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
#include <nuttx/i2c/i2c_master.h>

#include <stm32.h>
#include <arch/board/board.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* I2C1 Pin Definitions (using definitions from board.h) */
/* GPIO_I2C1_SCL, GPIO_I2C1_SDA are defined in board.h */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32_i2c1_initialize
 *
 * Description:
 *   Initialize I2C1 peripheral and configure GPIO pins.
 *
 ****************************************************************************/

int stm32_i2c1_initialize(void)
{
  /* Configure I2C1 GPIO pins */

  stm32_configgpio(GPIO_I2C1_SCL);
  stm32_configgpio(GPIO_I2C1_SDA);

  /* I2C1 is initialized by the STM32 I2C driver automatically */
  /* when CONFIG_STM32_I2C1 is enabled in defconfig */

  return OK;
}

/****************************************************************************
 * Name: stm32_i2c1_get_device
 *
 * Description:
 *   Get I2C1 master device instance.
 *
 ****************************************************************************/

struct i2c_master_s *stm32_i2c1_get_device(void)
{
  return stm32_i2cbus_initialize(1);
}
