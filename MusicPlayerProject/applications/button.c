/*
 * Copyright (c) 2021, Eureka1024 <eureka1024@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-11-17     Eureka1024    the first version
 */
#include <multi_button.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "common.h"

#define UP_BUTTON_PIN     rt_pin_get("PA.2") //按键 S4
#define MIDDLE_BUTTON_PIN rt_pin_get("PF.0") //按键 S3
#define DOWN_BUTTON_PIN   rt_pin_get("PF.1") //按键 S2

static struct button btn_up;
static struct button btn_middle;
static struct button btn_down;


static uint8_t button_read_pin_0(void)
{
    return rt_pin_read(UP_BUTTON_PIN);
}

static uint8_t button_read_pin_1(void)
{
    return rt_pin_read(MIDDLE_BUTTON_PIN);
}

static uint8_t button_read_pin_2(void)
{
    return rt_pin_read(DOWN_BUTTON_PIN);
}

static void button_0_callback(void *btn)
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct button *)btn);

    switch(btn_event_val)
    {
        case SINGLE_CLICK:
            rt_event_send(&control_event, UP_FLAG); //向上选择
            break;

        default:
            break;
    }
}

static void button_1_callback(void *btn)//entry
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct button *)btn);

    switch(btn_event_val)
    {
        case SINGLE_CLICK:
            rt_event_send(&control_event, ENTRY_FLAG); //确定
            break;

        case DOUBLE_CLICK:
            rt_event_send(&control_event, RETURN_FLAG);//返回
            break;

        default:
            break;
    }
}


static void button_2_callback(void *btn)//next
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct button *)btn);

    switch(btn_event_val)
    {
        case SINGLE_CLICK:
            rt_event_send(&control_event, DOWN_FLAG);//向下
            break;

        default:
            break;
    }
}

static void btn_thread_entry(void* p)
{
    while(1)
    {
        /* 5ms */
        rt_thread_delay(RT_TICK_PER_SECOND/200);
        button_ticks();
    }
}

static int multi_button_ctrl(void)
{
    rt_thread_t thread = RT_NULL;

    /* Create background ticks thread */
    thread = rt_thread_create("btn_check", btn_thread_entry, RT_NULL, 512, 20, 10);
    if(thread == RT_NULL)
    {
        return RT_ERROR;
    }
    rt_thread_startup(thread);

    //up 按键配置：单击检测
    rt_pin_mode  (UP_BUTTON_PIN, PIN_MODE_INPUT_PULLUP);
    button_init  (&btn_up, button_read_pin_0, PIN_LOW);
    button_attach(&btn_up, SINGLE_CLICK, button_0_callback);
    button_start (&btn_up);

    //middle 按键配置：单击检测和双击检测
    rt_pin_mode  (MIDDLE_BUTTON_PIN, PIN_MODE_INPUT_PULLUP);
    button_init  (&btn_middle, button_read_pin_1, PIN_LOW);
    button_attach(&btn_middle, SINGLE_CLICK, button_1_callback);
    button_attach(&btn_middle, DOUBLE_CLICK, button_1_callback);
    button_start (&btn_middle);

    //down 按键配置：单击检测
    rt_pin_mode  (DOWN_BUTTON_PIN, PIN_MODE_INPUT_PULLUP);
    button_init  (&btn_down, button_read_pin_2, PIN_LOW);
    button_attach(&btn_down, SINGLE_CLICK, button_2_callback);
    button_attach(&btn_down, DOUBLE_CLICK, button_2_callback);
    button_start (&btn_down);

    return RT_EOK;
}
INIT_APP_EXPORT(multi_button_ctrl);
