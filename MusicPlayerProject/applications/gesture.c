/*
 * Copyright (c) 2021, Eureka1024 <eureka1024@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-11-23     Eureka1024    the first version
 */
#include "common.h"

static paj7620_device_t paj7620_dev = RT_NULL;
char *gesture_string1[] =
{
    "up",
    "down",
    "left",
    "right",
    "forward",
    "backward",
    "clockwise", //顺时针
    "anticlockwise", //逆时针
    "wave", //挥手
};

/**
 * @brief paj7620 gesture detection thread
 *
 * @param parameter input parameters
 */
static void paj7620_entry(void *parameter)
{

    paj7620_gesture_t gesture;
    paj7620_gesture_t last_gesture = PAJ7620_GESTURE_NONE;
    rt_thread_mdelay(5000);
    while (1)
    {
        if (paj7620_get_gesture(paj7620_dev, &gesture) == RT_EOK)
        {
            if (gesture < PAJ7620_GESTURE_NONE)
            {
                rt_kprintf("Detected gesture: %s\r\n", gesture_string1[gesture]);
                switch (gesture)
                {
                case PAJ7620_GESTURE_RIGHT:
                    rt_event_send(&control_event, ENTRY_FLAG);
                    break;

                case PAJ7620_GESTURE_LEFT:
                    rt_event_send(&control_event, RETURN_FLAG);
                    break;

                case PAJ7620_GESTURE_UP:
                    rt_event_send(&control_event, UP_FLAG);
                    rt_thread_mdelay(1000);
                    break;

                case PAJ7620_GESTURE_DOWN:

                    rt_event_send(&control_event, DOWN_FLAG);
                    rt_thread_mdelay(1000);
                    break;

                case PAJ7620_GESTURE_FORWARD:
                    last_gesture = PAJ7620_GESTURE_FORWARD;
                    rt_thread_mdelay(1000);
                    break;

                case PAJ7620_GESTURE_BACKWARD:
                    break;

                case PAJ7620_GESTURE_CLOCKWISE:
                    break;

                case PAJ7620_GESTURE_ANTICLOCKWISE:
                    break;
                }
            }
        }

        rt_thread_mdelay(100);
    }
}

static int my_paj7620_init(void)
{
    rt_thread_t thread = RT_NULL;

    paj7620_dev = paj7620_init("i2c1"); //挂载在 i2c1 总线上

    thread = rt_thread_create("paj7620", paj7620_entry, RT_NULL, 1024, 10, 1);

    if(thread == RT_NULL)
    {
        return RT_ERROR;
    }
    rt_thread_startup(thread);

    return RT_EOK;
}

INIT_APP_EXPORT(my_paj7620_init);
