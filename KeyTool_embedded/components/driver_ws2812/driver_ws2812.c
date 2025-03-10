#include <stdio.h>
#include "driver/rmt_tx.h"
#include "driver_ws2812.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define RGB_NUM 18
#define WS2812HZ 10 * 1000000 // 10MHZ 0.1um

rmt_encoder_handle_t simple_encoder = NULL;
// [1] 资源分配
rmt_channel_handle_t led_channel = NULL;
// [1] END
struct driver_ws2812_i driver_ws2812_interface = {
    .ws2812_light = (ws2812_light_fn_t)ws2812_light,
    .ws2812_extinguish = (ws2812_extinguish_fn_t)ws2812_extinguish
};

// 低数据
static const rmt_symbol_word_t ws2812_zero = {
    .level0 = 1,
    .duration0 = 0.3 * WS2812HZ / 1000000, // T0H=0.3us
    .level1 = 0,
    .duration1 = 0.9 * WS2812HZ / 1000000, // T0L=0.9us
};

// 高数据
static const rmt_symbol_word_t ws2812_one = {
    .level0 = 1,
    .duration0 = 0.9 * WS2812HZ / 1000000, // T1H=0.9us
    .level1 = 0,
    .duration1 = 0.3 * WS2812HZ / 1000000, // T1L=0.3us
};

//reset defaults to 50uS
static const rmt_symbol_word_t ws2812_reset = {
    .level0 = 1,
    .duration0 = WS2812HZ / 1000000 * 50 / 2,
    .level1 = 0,
    .duration1 = WS2812HZ / 1000000 * 50 / 2,
};

// 自定义的rmt规则
static size_t encoder_callback(const void *data, size_t data_size,
                               size_t symbols_written, size_t symbols_free,
                               rmt_symbol_word_t *symbols, bool *done, void *arg)
{
    // We need a minimum of 8 symbol spaces to encode a byte. We only
    // need one to encode a reset, but it's simpler to simply demand that
    // there are 8 symbol spaces free to write anything.
    if (symbols_free < 8)
    {
        return 0;
    }

    // We can calculate where in the data we are from the symbol pos.
    // Alternatively, we could use some counter referenced by the arg
    // parameter to keep track of this.
    size_t data_pos = symbols_written / 8;
    uint8_t *data_bytes = (uint8_t *)data;
    if (data_pos < data_size)
    {
        // Encode a byte
        size_t symbol_pos = 0;
        for (int bitmask = 0x80; bitmask != 0; bitmask >>= 1)
        {
            if (data_bytes[data_pos] & bitmask)
            {
                symbols[symbol_pos++] = ws2812_one;
            }
            else
            {
                symbols[symbol_pos++] = ws2812_zero;
            }
        }
        // We're done; we should have written 8 symbols.
        return symbol_pos;
    }
    else
    {
        // All bytes already are encoded.
        // Encode the reset, and we're done.
        symbols[0] = ws2812_reset;
        *done = 1; // Indicate end of the transaction.
        return 1;  // we only wrote one symbol
    }
}

int ws2812_init(struct ws2812_data *self)
{
    rmt_tx_channel_config_t tx_channel_cfg = {
        .clk_src = RMT_CLK_SRC_DEFAULT, // 选择时钟源
        .gpio_num = RGB_NUM,
        .mem_block_symbols = 64, // 内存块大小
        .resolution_hz = WS2812HZ,
        .trans_queue_depth = 4,
    };
    ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_channel_cfg, &led_channel));

    const rmt_simple_encoder_config_t simple_encoder_cfg = {
        .callback = encoder_callback};
    ESP_ERROR_CHECK(rmt_new_simple_encoder(&simple_encoder_cfg, &simple_encoder));

    ESP_ERROR_CHECK(rmt_enable(led_channel));
    rmt_transmit_config_t tx_cfg = {
        .loop_count = 0,
    };
    self->user = &tx_cfg;
    self->driver_ws2812 = &driver_ws2812_interface;
    return 0;
}

int ws2812_light(struct ws2812_data *self,void *color_data)
{
    ESP_ERROR_CHECK(rmt_transmit(led_channel,simple_encoder,color_data,3,self->user));
    ESP_ERROR_CHECK(rmt_tx_wait_all_done(led_channel,portMAX_DELAY));//portMAX_DELAY
    return 0;
}

int ws2812_extinguish(struct ws2812_data *self)
{
    static uint8_t led_test_data[3];
    for (size_t i = 0; i < 3; i++)
    {
        led_test_data[i] = 0;
    }
    ESP_ERROR_CHECK(rmt_transmit(led_channel,simple_encoder,led_test_data,sizeof(led_test_data),self->user));
    ESP_ERROR_CHECK(rmt_tx_wait_all_done(led_channel,0xffffffffUL));
    return 0;
}