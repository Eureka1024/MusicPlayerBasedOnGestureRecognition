/*
 * Copyright (c) 2021, Eureka1024 <eureka1024@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-11-21     Eureka1024    the first version
 */

#include <rtthread.h>
#include "board.h"
#include "common.h"

int main(void)
{
    uint8_t pin = rt_pin_get("PE.1");

    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_kprintf("Hello, world\n");

    while (1)
    {
        rt_pin_write(pin, PIN_LOW);
        rt_thread_mdelay(500);
        rt_pin_write(pin, PIN_HIGH);
        rt_thread_mdelay(500);
    }
}
