/****************************************************************************
 * Contest 2026 team 316 - STM32F103ZET6 SPI Driver
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
#include <nuttx/spi/spi.h>

#include <stm32.h>
#include <arch/board/board.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SPI1 Pin Definitions (using definitions from board.h) */
/* GPIO_SPI1_SCK, GPIO_SPI1_MISO, GPIO_SPI1_MOSI, GPIO_SPI1_NSS */
/* are defined in board.h */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32_spi1_initialize
 *
 * Description:
 *   Initialize SPI1 peripheral and configure GPIO pins.
 *
 ****************************************************************************/

int stm32_spi1_initialize(void)
{
  /* Configure SPI1 GPIO pins */

  stm32_configgpio(GPIO_SPI1_SCK);
  stm32_configgpio(GPIO_SPI1_MISO);
  stm32_configgpio(GPIO_SPI1_MOSI);
  stm32_configgpio(GPIO_SPI1_NSS);

  /* SPI1 is initialized by the STM32 SPI driver automatically */
  /* when CONFIG_STM32_SPI1 is enabled in defconfig */

  return OK;
}

/****************************************************************************
 * Name: stm32_spi1_select
 *
 * Description:
 *   Select SPI1 device (assert NSS/CS).
 *
 ****************************************************************************/

void stm32_spi1_select(struct spi_dev_s *dev, uint32_t devid, bool selected)
{
  /* Assert/deassert chip select */

  stm32_gpiowrite(GPIO_SPI1_NSS, !selected);
}

/****************************************************************************
 * Name: stm32_spi1_setfrequency
 *
 * Description:
 *   Set SPI1 clock frequency.
 *
 ****************************************************************************/

uint32_t stm32_spi1_setfrequency(struct spi_dev_s *dev, uint32_t frequency)
{
  /* The actual frequency setting is handled by the STM32 SPI driver */

  return frequency;
}

/****************************************************************************
 * Name: stm32_spi1_setmode
 *
 * Description:
 *   Set SPI1 mode (CPOL/CPHA).
 *
 ****************************************************************************/

void stm32_spi1_setmode(struct spi_dev_s *dev, enum spi_mode_e mode)
{
  /* The actual mode setting is handled by the STM32 SPI driver */
}

/****************************************************************************
 * Name: stm32_spi1_setbits
 *
 * Description:
 *   Set SPI1 word size (8 or 16 bits).
 *
 ****************************************************************************/

void stm32_spi1_setbits(struct spi_dev_s *dev, int nbits)
{
  /* The actual bits setting is handled by the STM32 SPI driver */
}
