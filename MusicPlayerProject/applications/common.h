/*
 * Copyright (c) 2021, Eureka1024 <eureka1024@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-11-17     Eureka1024    the first version
 */
#ifndef APPLICATIONS_COMMON_H_
#define APPLICATIONS_COMMON_H_

#include "oled12864.h"
#include "oled12864_font.h"

/* 外部控制事件标志 */
#define UP_FLAG     (1 << 0)    //向上
#define ENTRY_FLAG  (1 << 1)    //确定
#define RETURN_FLAG (1 << 2)    //返回
#define DOWN_FLAG   (1 << 3)    //向下

extern struct rt_event control_event; //功能控制事件

int music_num_get(void);

#endif /* APPLICATIONS_COMMON_H_ */
