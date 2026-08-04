/****************************************************************************
 * Contest 2026 team 316 - Button Test Demo Application
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
#include <poll.h>
#include <nuttx/irq.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define BUTTON_DEVICE_PATH  "/dev/buttons"
#define POLL_TIMEOUT_MS     10000

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: button_test_main
 *
 * Description:
 *   Main entry point for button test demo.
 *
 ****************************************************************************/

int main(int argc, char *argv[])
{
  int fd;
  int ret;
  struct pollfd fds[1];
  char button_state;
  ssize_t nbytes;

  printf("Button Test Demo - STM32F103ZET6\n");
  printf("=================================\n");
  printf("Press USER button (PA0) to test...\n");
  printf("Timeout: %d ms\n\n", POLL_TIMEOUT_MS);

  /* Open button device */

  fd = open(BUTTON_DEVICE_PATH, O_RDONLY);
  if (fd < 0)
    {
      printf("ERROR: Failed to open %s: %d\n", BUTTON_DEVICE_PATH, fd);
      printf("Make sure CONFIG_ARCH_BUTTONS is enabled\n");
      return -1;
    }

  printf("Button device opened successfully\n");

  /* Setup poll */

  fds[0].fd = fd;
  fds[0].events = POLLIN;
  fds[0].revents = 0;

  /* Wait for button press */

  printf("Waiting for button press...\n");

  while (1)
    {
      ret = poll(fds, 1, POLL_TIMEOUT_MS);
      if (ret < 0)
        {
          printf("ERROR: poll failed: %d\n", ret);
          break;
        }
      else if (ret == 0)
        {
          printf("Timeout - no button press detected\n");
          printf("Check button connection on PA0\n");
          break;
        }
      else
        {
          /* Read button state */

          nbytes = read(fd, &button_state, 1);
          if (nbytes > 0)
            {
              printf("Button pressed! State: %d\n", button_state);
              printf("Button test PASSED!\n");
              break;
            }
        }
    }

  /* Close device */

  close(fd);
  return 0;
}
