// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Copyright 2024 mzyy94

#if defined(ESP_PLATFORM)
#ifdef ARDUINO
#include <driver/gpio.h>
#include <driver/pcnt.h>
class Encoder
{
public:
    void setup();
    int getCount(bool clear = false);
    void reset();
};
#else
#include <driver/gpio.h>
#include <driver/pulse_cnt.h>
class Encoder
{
private:
    gpio_num_t _pin_a;
    gpio_num_t _pin_b;

    pcnt_unit_handle_t _pcnt_unit;
    pcnt_channel_handle_t _pcnt_chan_a;
    pcnt_channel_handle_t _pcnt_chan_b;

public:
    Encoder();
    ~Encoder();
    void setup(gpio_num_t pin_a = GPIO_NUM_40, gpio_num_t pin_b = GPIO_NUM_41);
    int getCount(bool clear = false);
    void reset();
};
#endif
#else
class Encoder
{
public:
    inline void setup(){};
    inline int getCount(bool clear = false) { return 0; };
    inline void reset(){};
};
#endif
