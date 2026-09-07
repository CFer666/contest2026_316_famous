/****************************************************************************
 * Contest 2026 team 316 - STM32F103ZET6 Board Bring-up
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

#include <stdio.h>
#include <syslog.h>
#include <errno.h>

#include <nuttx/board.h>
#include <arch/board/board.h>

#include <stm32.h>

#ifdef CONFIG_INPUT_BUTTONS
#  include <nuttx/input/buttons.h>
#endif

#ifdef CONFIG_USERLED
#  include <nuttx/leds/userled.h>
#endif

#ifdef CONFIG_STM32_SPI1
#  include <nuttx/spi/spi.h>
#endif

#ifdef CONFIG_I2C_DRIVER
#  include <nuttx/i2c/i2c_master.h>
#endif

#ifdef CONFIG_RTC_DRIVER
#  include <nuttx/timers/rtc.h>
#endif

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Board-specific peripheral setup, implemented in the sibling source files */

#ifdef CONFIG_ADC
extern int stm32_adc_setup(void);
#endif

#ifdef CONFIG_PWM
extern int stm32_pwm_setup(void);
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32_i2c_register
 *
 * Description:
 *   Register one I2C driver for the I2C tool.
 *
 ****************************************************************************/

#ifdef CONFIG_I2C_DRIVER
static void stm32_i2c_register(int bus)
{
  struct i2c_master_s *i2c;
  int ret;

  i2c = stm32_i2cbus_initialize(bus);
  if (i2c == NULL)
    {
      syslog(LOG_ERR, "ERROR: Failed to get I2C%d interface\n", bus);
    }
  else
    {
      ret = i2c_register(i2c, bus);
      if (ret < 0)
        {
          syslog(LOG_ERR, "ERROR: Failed to register I2C%d driver: %d\n",
                 bus, ret);
          stm32_i2cbus_uninitialize(i2c);
        }
    }
}
#endif

/****************************************************************************
 * Name: rtc_driver_initialize
 *
 * Description:
 *   Initialize and register the RTC driver.
 *
 ****************************************************************************/

#ifdef CONFIG_RTC_DRIVER
static int rtc_driver_initialize(void)
{
  struct rtc_lowerhalf_s *lower;
  int ret;

  /* Instantiate the STM32 lower-half RTC driver */

  lower = stm32_rtc_lowerhalf();
  if (lower == NULL)
    {
      syslog(LOG_ERR, "ERROR: Failed to instantiate the RTC lower-half\n");
      ret = -ENOMEM;
    }
  else
    {
      /* Bind the lower half driver and register the RTC driver as
       * /dev/rtc0
       */

      ret = rtc_initialize(0, lower);
      if (ret < 0)
        {
          syslog(LOG_ERR, "ERROR: Failed to register the RTC driver: %d\n",
                 ret);
        }
    }

  return ret;
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32_bringup
 *
 * Description:
 *   Perform architecture-specific initialization.  Called from
 *   board_app_initialize() (via the NSH boardctl path when
 *   CONFIG_NSH_ARCHINIT is selected).
 *
 ****************************************************************************/

int stm32_bringup(void)
{
  int ret = OK;

#ifdef CONFIG_STM32_SPI1
  /* Initialize the SPI1 bus.  The returned handle is used to bind the bus
   * to higher-level drivers; the bare bus does not appear as its own /dev
   * node.
   */

  {
    struct spi_dev_s *spi = stm32_spibus_initialize(1);

    if (spi == NULL)
      {
        syslog(LOG_ERR, "ERROR: Failed to initialize SPI1\n");
      }
  }
#endif

#ifdef CONFIG_I2C_DRIVER
  /* Register the I2C1 driver on behalf of the I2C tool */

#ifdef CONFIG_STM32_I2C1
  stm32_i2c_register(1);
#endif
#endif

#ifdef CONFIG_ADC
  /* Initialize ADC and register the ADC driver at /dev/adc0 */

  ret = stm32_adc_setup();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: stm32_adc_setup() failed: %d\n", ret);
    }
#endif

#ifdef CONFIG_PWM
  /* Initialize PWM and register the PWM device at /dev/pwm0 */

  ret = stm32_pwm_setup();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: stm32_pwm_setup() failed: %d\n", ret);
    }
#endif

#ifdef CONFIG_RTC_DRIVER
  /* Initialize and register the RTC driver at /dev/rtc0 */

  ret = rtc_driver_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: rtc_driver_initialize() failed: %d\n", ret);
    }
#endif

#ifdef CONFIG_STM32_IWDG
  /* Initialize the independent watchdog at /dev/watchdog0.  The LSI clock
   * is the IWDG clock source and runs at ~40kHz on the STM32F103.
   */

  stm32_iwdginitialize("/dev/watchdog0", STM32_LSI_FREQUENCY);
#endif

#ifdef CONFIG_INPUT_BUTTONS
  /* Register the button driver at /dev/buttons */

  ret = btn_lower_initialize("/dev/buttons");
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: btn_lower_initialize() failed: %d\n", ret);
    }
#endif

#ifdef CONFIG_USERLED
  /* Register the user LED driver at /dev/userleds */

  ret = userled_lower_initialize("/dev/userleds");
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: userled_lower_initialize() failed: %d\n", ret);
    }
#endif

  return ret;
}
