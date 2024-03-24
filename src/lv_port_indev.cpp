// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Copyright 2024 mzyy94

#include "lv_port_indev.h"
#include <M5Unified.hpp>
#include "encoder.hpp"

static void touchpad_init(void);
static void touchpad_read(lv_indev_t *indev, lv_indev_data_t *data);
static bool touchpad_is_pressed(void);
static void touchpad_get_xy(int32_t *x, int32_t *y);

static void encoder_init(void);
static void encoder_read(lv_indev_t *indev, lv_indev_data_t *data);
static void encoder_read_4th(lv_indev_t *indev, lv_indev_data_t *data);

lv_indev_t *indev_touchpad;
lv_indev_t *indev_encoder;
lv_indev_t *indev_encoder_4th;

Encoder encoder;

void lv_port_indev_init(void)
{
    touchpad_init();

    indev_touchpad = lv_indev_create();
    lv_indev_set_type(indev_touchpad, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev_touchpad, touchpad_read);

    encoder_init();

    indev_encoder = lv_indev_create();
    lv_indev_set_type(indev_encoder, LV_INDEV_TYPE_ENCODER);
    lv_indev_set_read_cb(indev_encoder, encoder_read);

    indev_encoder_4th = lv_indev_create();
    lv_indev_set_type(indev_encoder_4th, LV_INDEV_TYPE_ENCODER);
    lv_indev_set_read_cb(indev_encoder_4th, encoder_read_4th);
}

static void touchpad_init(void)
{
}

static void touchpad_read(lv_indev_t *indev_drv, lv_indev_data_t *data)
{
    static int32_t last_x = 0;
    static int32_t last_y = 0;

    if (touchpad_is_pressed())
    {
        touchpad_get_xy(&last_x, &last_y);
        data->state = LV_INDEV_STATE_PR;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }

    data->point.x = last_x;
    data->point.y = last_y;
}

static bool touchpad_is_pressed(void)
{
    return M5.Touch.getCount() > 0;
}

static void touchpad_get_xy(int32_t *x, int32_t *y)
{
    auto detail = M5.Touch.getDetail();

    (*x) = detail.x;
    (*y) = detail.y;
}

static void encoder_init(void)
{
    encoder.setup();
}
int single_enc_old = 0;
static void encoder_read(lv_indev_t *indev_drv, lv_indev_data_t *data)
{
    data->enc_diff = encoder.getCount(false) - single_enc_old;
    data->state = M5.BtnA.isPressed() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
    data->key = LV_KEY_ENTER;
    single_enc_old = encoder.getCount(false);
}
int fourth_enc_old = 0;
static void encoder_read_4th(lv_indev_t *indev_drv, lv_indev_data_t *data)
{
    int enc_pos = encoder.getCount(false)/4;
    data->enc_diff = (enc_pos-fourth_enc_old);
    data->state = M5.BtnA.isPressed() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
    data->key = LV_KEY_ENTER;
    fourth_enc_old = enc_pos;
}

