#pragma once

#include <stdio.h>

/*[1]抽象出ws2812的行为*/
typedef int(*ws2812_light_fn_t)(void *self,void *color_data); // 亮
typedef int(*ws2812_extinguish_fn_t)(void *self);             // 灭
struct driver_ws2812_i
{
    ws2812_light_fn_t ws2812_light;
    ws2812_extinguish_fn_t ws2812_extinguish;
};
/*[1]END*/

/*[2]WS2812所需要的数据*/
struct ws2812_data
{
    struct driver_ws2812_i *driver_ws2812;
    void *user;
};
/*[2]END*/

/*[3]对外调用函数*/
int ws2812_init(struct ws2812_data *self);
int ws2812_light(struct ws2812_data *self,void *color_data);
int ws2812_extinguish(struct ws2812_data *self);
/*[3]END*/