/****************************************************************************
 * Contest 2026 team 316 - LED Blink Demo Application
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
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <nuttx/leds/userled.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define LED_DEVICE_PATH  "/dev/userleds"
#define BLINK_DELAY_MS   500

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: led_blink_main
 *
 * Description:
 *   Main entry point for LED blink demo.
 *
 ****************************************************************************/

int main(int argc, char *argv[])
{
  int fd;
  int ret;
  struct userled_s led;
  bool led_state = false;

  printf("LED Blink Demo - STM32F103ZET6\n");
  printf("==============================\n");

  /* Open LED device */

  fd = open(LED_DEVICE_PATH, O_WRONLY);
  if (fd < 0)
    {
      printf("ERROR: Failed to open %s: %d\n", LED_DEVICE_PATH, fd);
      return -1;
    }

  printf("LED device opened successfully\n");
  printf("Blinking LED1 (PB0) at %d ms interval\n", BLINK_DELAY_MS);

  /* Blink LED indefinitely */

  while (1)
    {
      /* Toggle LED state */

      led_state = !led_state;
      led.led_idx = 0;  /* LED1 */
      led.led_on = led_state;

      ret = ioctl(fd, ULEDIOC_SETLED, (unsigned long)&led);
      if (ret < 0)
        {
          printf("ERROR: Failed to set LED: %d\n", ret);
          break;
        }

      /* Delay */

      usleep(BLINK_DELAY_MS * 1000);
    }

  /* Close device */

  close(fd);
  return 0;
}
