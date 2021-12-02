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
    while (1)
    {
        rt_thread_mdelay(500);
        rt_thread_mdelay(500);
    }

}
