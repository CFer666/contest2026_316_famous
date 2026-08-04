/****************************************************************************
 * Contest 2026 team 316 - System Info Demo Application
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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include <nuttx/version.h>

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: print_system_info
 *
 * Description:
 *   Print system information.
 *
 ****************************************************************************/

static void print_system_info(void)
{
  printf("\n");
  printf("============================================\n");
  printf("  openvela System Information\n");
  printf("  STM32F103ZET6 - Contest 2026 Team 316\n");
  printf("============================================\n");
  printf("\n");

  /* OS Information */

  printf("[OS Information]\n");
  printf("  OS:           openvela (based on NuttX)\n");
  printf("  Version:      %s\n", NX_VERSION);
  printf("  Build Date:   %s\n", __DATE__);
  printf("  Build Time:   %s\n", __TIME__);
  printf("\n");

  /* Hardware Information */

  printf("[Hardware Information]\n");
  printf("  MCU:          STM32F103ZET6\n");
  printf("  Core:         ARM Cortex-M3\n");
  printf("  Clock:        72 MHz\n");
  printf("  Flash:        512 KB\n");
  printf("  SRAM:         64 KB\n");
  printf("  GPIO:         80 pins\n");
  printf("\n");

  /* Peripheral Information */

  printf("[Available Peripherals]\n");
  printf("  USART1:       PA9(TX)/PA10(RX) - Console\n");
  printf("  USART2:       PA2(TX)/PA3(RX)\n");
  printf("  SPI1:         PA5(SCK)/PA6(MISO)/PA7(MOSI)\n");
  printf("  I2C1:         PB6(SCL)/PB7(SDA)\n");
  printf("  ADC1:         3 channels\n");
  printf("  PWM:          TIM1, TIM2\n");
  printf("  RTC:          Real-Time Clock\n");
  printf("  IWDG:         Independent Watchdog\n");
  printf("\n");

  /* LED Information */

  printf("[LED Information]\n");
  printf("  LED1:         PB0 (Green)\n");
  printf("  LED2:         PB1 (Yellow)\n");
  printf("  LED3:         PB5 (Red)\n");
  printf("\n");

  /* Button Information */

  printf("[Button Information]\n");
  printf("  USER:         PA0 (Active Low)\n");
  printf("\n");

  /* Memory Information */

  printf("[Memory Information]\n");
  printf("  RAM Start:    0x20000000\n");
  printf("  RAM Size:     65536 bytes (64 KB)\n");
  printf("  Flash Start:  0x08000000\n");
  printf("  Flash Size:   524288 bytes (512 KB)\n");
  printf("\n");
}

/****************************************************************************
 * Name: print_nsh_help
 *
 * Description:
 *   Print NSH command help.
 *
 ****************************************************************************/

static void print_nsh_help(void)
{
  printf("[NSH Commands]\n");
  printf("  help          - Show this help\n");
  printf("  uname -a      - Show system information\n");
  printf("  ps            - Show running processes\n");
  printf("  free          - Show memory usage\n");
  printf("  ls /dev       - List devices\n");
  printf("  led_blink     - Run LED blink demo\n");
  printf("  button_test   - Run button test demo\n");
  printf("  sysinfo       - Show this information\n");
  printf("\n");
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: sysinfo_main
 *
 * Description:
 *   Main entry point for system info demo.
 *
 ****************************************************************************/

int main(int argc, char *argv[])
{
  print_system_info();
  print_nsh_help();

  printf("============================================\n");
  printf("  System ready! Type 'help' for commands.\n");
  printf("============================================\n\n");

  return 0;
}
