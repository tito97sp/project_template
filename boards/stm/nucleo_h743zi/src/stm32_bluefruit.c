/****************************************************************************
 * boards/arm/stm32h7/nucleo-h743zi/src/stm32_bluefruit.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <debug.h>
#include <errno.h>

#include <nuttx/spi/spi.h>
#include <nuttx/wireless/bluefruit.h>
#include <arch/board/board.h>

#include "arm_arch.h"
#include "chip.h"
#include "stm32.h"
#include "nucleo-h743zi.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define BLUEFRUIT_SPI 1  // Bluefruit spi bus number

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/
static int bluefruit_irq_attach(xcpt_t isr, FAR void *arg);
static void bluefruit_chip_enable(bool enable);

/****************************************************************************
 * Private Data
 ****************************************************************************/

static struct bluefruit_config_s blue_cfg =
{
  .irqattach = bluefruit_irq_attach,
  .chipenable = bluefruit_chip_enable,
};

static xcpt_t g_isr;
static FAR void *g_arg;

/****************************************************************************
 * Private Functions
 ****************************************************************************/
static int bluefruit_irq_attach(xcpt_t isr, FAR void *arg)
{
  wlinfo("Attach IRQ\n");
  g_isr = isr;
  g_arg = arg;
  stm32_gpiosetevent(GPIO_BLUEFRUIT_IRQ, false, true, false, g_isr, g_arg);
  return OK;
}

static void bluefruit_chip_enable(bool enable)
{
  wlinfo("CE:%d\n", enable);
  stm32_gpiowrite(GPIO_BLUEFRUIT_CE, enable);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/
int stm32_blfrinitialize(void)
{
  FAR struct spi_dev_s *spidev;
  int ret = OK;

  syslog(LOG_INFO, "Register the bluefruit module\n");

  /* Setup CE & IRQ line IOs */

  stm32_configgpio(GPIO_BLUEFRUIT_CE);
  stm32_configgpio(GPIO_BLUEFRUIT_IRQ);

  /* Init SPI bus */

  spidev = stm32_spibus_initialize(BLUEFRUIT_SPI);
  if (!spidev)
    {
      wlerr("ERROR: Failed to initialize SPI %d bus\n", BLUEFRUIT_SPI);
      ret = -ENODEV;
      goto errout;
    }

  ret = bluefruit_register(spidev, &blue_cfg);
  if (ret != OK)
    {
      wlerr("ERROR: Failed to register bluefruit device\n");
      goto errout;
    }

errout:
  return ret;
}