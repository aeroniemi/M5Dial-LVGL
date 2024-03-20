// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Copyright 2024 mzyy94

#ifndef LV_PORT_INDEV_H
#define LV_PORT_INDEV_H

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
    extern lv_indev_t *indev_touchpad;
    extern lv_indev_t *indev_encoder;
    void lv_port_indev_init(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LV_PORT_INDEV_H
