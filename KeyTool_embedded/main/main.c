#include <stdio.h>
#include <string.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "driver/uart.h"

#include "Device_fun.h"
#include "_74hc165_button.h"
#include "driver_ws2812.h"

#define EX_UART_NUM UART_NUM_0
#define PATTERN_CHR_NUM (6) /*!< Set the number of consecutive and identical characters received by receiver which defines a UART pattern*/

#define BUF_SIZE (1024)
#define RD_BUF_SIZE (BUF_SIZE)

static const char *TAG = "Main";

QueueHandle_t uart0_queue;   // 消息队列
SemaphoreHandle_t led_mutex; // 互斥锁

struct state_machine_data_i state_machine_data; // 状态机
struct _74hc165_button button;                  // 按钮
struct ws2812_data ws2812;                      // 灯
static void key_run_task(void *pvParameters);
static void uart_event_task(void *pvParameters);

// 按钮触发id
enum button_id
{
    BUTTON1_CLICK = (1 << 1),
    BUTTON2_CLICK = (1 << 2),
    BUTTON3_CLICK = (1 << 3),
    BUTTON_NONE = (1 << 4),
};

// 键盘或着鼠标状态
enum key_or_mouse_state
{
    KEY_CLICK = 0,
    KEY_HOLD,
    MOUSE_LEFT_CLICK,
    MOUSE_RIGHT_CLICK,
    MOUSE_LEFT_HOLD,
    MOUSE_RIGHT_HOLD,
    KEY_NONE
};

// 状态机的状态
enum state_machine
{
    STATE_INIT,    // 初始化
    STATE_KEY_SET, // 设置键盘
    STATE_START,   // 运行
    STATE_STOP,    // 停止运行
};

#define nvs_list_len 7 //
struct state_machine_data_i
{
    enum state_machine state;
    enum button_id but_id;
    enum key_or_mouse_state key_or_mouse;

    // nvs
    int32_t key_value[nvs_list_len];
    char *key_name[nvs_list_len];
    uint8_t led_test_data[3];
    // nvs end

    bool read_message_flag; // 是否接收到到串口指定消息
    bool key_pressed;       // 键盘按下
    bool mouse_pressed;     // 鼠标按下
    bool key_state;         // 按钮按下释放标志
    bool init_key_end;      // USBHID初始化完毕标志
};

int state_init(struct state_machine_data_i *self)
{
    ESP_ERROR_CHECK(device_uart_init(&uart0_queue, UART_NUM_0, BUF_SIZE, PATTERN_CHR_NUM));
    ESP_ERROR_CHECK(device_nvs_init());
    ESP_ERROR_CHECK(device_nvs_read(self->key_value, self->key_name, nvs_list_len)); // 读取存储的键值
    ESP_ERROR_CHECK(device_usb_hid_init());
    struct _74hc165_config cfg = {
        .trigger_mode = 0, // 1立即触发，0 松开触发
    };
    ESP_ERROR_CHECK(_74hc165_button_init(&button, &cfg));
    led_mutex = xSemaphoreCreateMutex();                    // 创建互斥锁
    if (xSemaphoreTake(led_mutex, portMAX_DELAY) == pdTRUE) // 获取锁
    {
        ws2812_extinguish(&ws2812);
        xSemaphoreGive(led_mutex); // 释放锁
    }
    xTaskCreate(key_run_task, "key_run_task", 4096, (void *)self, 10, NULL);       // 按键任务
    xTaskCreate(uart_event_task, "uart_event_task", 4096, (void *)self, 12, NULL); // 串口任务
    self->state = STATE_START;
    return 0;
}

// 设置按键功能
int state_key_set(struct state_machine_data_i *self)
{
    ESP_ERROR_CHECK(device_nvs_clean());                                              // 清除当前存储的设置
    ESP_ERROR_CHECK(device_nvs_init());                                               // 擦除后需要重新初始化
    ESP_ERROR_CHECK(device_nvs_write(self->key_value, self->key_name, nvs_list_len)); // 写入新数据
    ESP_ERROR_CHECK(device_nvs_read(self->key_value, self->key_name, nvs_list_len));  // 读取键值
    self->state = STATE_START;
    return 0;
}

// 运行状态
int state_start(struct state_machine_data_i *self)
{
    if (self->read_message_flag)
    {
        ESP_LOGI(TAG, "READ MESSAGE!");
        self->read_message_flag = false;
        self->state = STATE_KEY_SET; // 进入设置模式
    }
    if (self->init_key_end)
    {
        // [start]获取按钮点击
        switch (_74hc165_button_get_num(&button))
        {
        case BUTTON1_CLICK:
            if (self->key_state)
            {
                self->but_id = 0;
                self->key_state = false;
                self->led_test_data[0] = 255;
                self->led_test_data[1] = 0;
                self->led_test_data[2] = 0;
                ws2812_light(&ws2812, self->led_test_data);
            }
            else
            {
                self->but_id = 5;
                self->key_state = true;
                ws2812_extinguish(&ws2812);
            }
            break;
        case BUTTON2_CLICK:
            if (self->key_state)
            {
                self->but_id = 2;
                self->key_state = false;
                self->led_test_data[0] = 0;
                self->led_test_data[1] = 255;
                self->led_test_data[2] = 0;
                ws2812_light(&ws2812, self->led_test_data);
            }
            else
            {
                self->but_id = 5;
                self->key_state = true;
                ws2812_extinguish(&ws2812);
            }
            break;
        case BUTTON3_CLICK:
            if (self->key_state)
            {
                self->but_id = 4;
                self->key_state = false;
                self->led_test_data[0] = 0;
                self->led_test_data[1] = 0;
                self->led_test_data[2] = 255;
                ws2812_light(&ws2812, self->led_test_data);
            }
            else
            {
                self->but_id = 5;
                self->key_state = true;
                ws2812_extinguish(&ws2812);
            }
            break;
        case BUTTON_NONE:
            /* code */
            break;
        }
        // [end]获取按钮点击
    }
    return 0;
}

int state_stop(struct state_machine_data_i *self)
{
    // self->state = STATE_INIT;
    return 0;
}

// 初始化状态机
int machine_init(struct state_machine_data_i *self)
{
    static char *key_name[] = {"key1", "key1_model", "key2", "key2_model", "key3", "key3_model", "key_none"};
    static uint32_t key_list[] = {04, 00, 05, 01, 02, 03, 06};
    for (size_t i = 0; i < nvs_list_len; i++)
    {
        self->key_name[i] = key_name[i];
        self->key_value[i] = key_list[i];
    }
    self->state = STATE_INIT;
    self->but_id = 5; // 多余的键值
    self->key_or_mouse = KEY_NONE;
    self->read_message_flag = false; // 初始未接收到消息
    self->key_pressed = false;
    self->mouse_pressed = false;
    self->key_state = true;
    self->init_key_end = false;
    ESP_LOGI(TAG, "machine init success");
    return 0;
}

// 状态机运行
int machine_step(struct state_machine_data_i *self)
{
    switch (self->state)
    {
    case STATE_INIT:
        return state_init(self);
    case STATE_KEY_SET:
        return state_key_set(self);
    case STATE_START:
        return state_start(self);
    case STATE_STOP:
        return state_stop(self);
    }
    return 0;
}

void app_main(void)
{
    ws2812_init(&ws2812);
    machine_init(&state_machine_data);
    while (1)
    {
        machine_step(&state_machine_data);
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}

/*按键任务*/
static void key_run_task(void *pvParameters)
{
    struct state_machine_data_i *self = (struct state_machine_data_i *)pvParameters;
    vTaskDelay(200 / portTICK_PERIOD_MS);
    self->init_key_end = true;
    while (1)
    {
        // printf("but_id+1 = %d\n", self->but_id+1);
        switch (self->key_value[self->but_id + 1])
        {
        case KEY_CLICK:
            device_usb_hid_keyboard_press(self->key_value[self->but_id]);
            vTaskDelay(50 / portTICK_PERIOD_MS);
            device_usb_hid_keyboard_release();
            // self->but_id = BUTTON_NONE;  // 增加状态重置 ← 关键修复
            break;
        case KEY_HOLD:
            if (self->key_pressed == false)
            {
                device_usb_hid_keyboard_press(self->key_value[self->but_id]);
                self->key_pressed = true;
            }
            break;
        case MOUSE_LEFT_CLICK:
            device_usb_hid_mouse_press(self->key_value[self->but_id]);
            vTaskDelay(10 / portTICK_PERIOD_MS);
            device_usb_hid_mouse_release();
            break;
        case MOUSE_RIGHT_CLICK:
            device_usb_hid_mouse_press(self->key_value[self->but_id]);
            vTaskDelay(100 / portTICK_PERIOD_MS);
            device_usb_hid_mouse_release();
            printf("right click\n");
            break;
        case MOUSE_LEFT_HOLD:
            if (self->mouse_pressed == false)
            {
                device_usb_hid_mouse_press(self->key_value[self->but_id]);
                self->mouse_pressed = true;
            }
            break;
        case MOUSE_RIGHT_HOLD:
            if (self->mouse_pressed == false)
            {
                device_usb_hid_mouse_press(self->key_value[self->but_id]);
                self->mouse_pressed = true;
            }
            break;
        case KEY_NONE:
            if (self->key_pressed)
            {
                device_usb_hid_keyboard_release();
                self->key_pressed = false;
            }
            if (self->mouse_pressed)
            {
                device_usb_hid_mouse_release();
                self->mouse_pressed = false;
            }
            break;
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

/*串口任务*/
static void uart_event_task(void *pvParameters)
{
    struct state_machine_data_i *self = (struct state_machine_data_i *)pvParameters;

    uart_event_t event;
    size_t buffered_size;
    uint8_t *dtmp = (uint8_t *)malloc(RD_BUF_SIZE);
    uint8_t connect_ok[] = {0x26, 0x26};
    uint8_t read_data_ok[] = {0x27, 0x27};
    uint8_t clean_ok[] = {0x28, 0x28};

    for (;;)
    {
        // Waiting for UART event.
        if (xQueueReceive(uart0_queue, (void *)&event, (TickType_t)portMAX_DELAY))
        {
            bzero(dtmp, RD_BUF_SIZE);
            switch (event.type)
            {
            case UART_DATA:
                uart_read_bytes(EX_UART_NUM, dtmp, event.size, portMAX_DELAY);
                if (dtmp[0] == 0x08 && dtmp[1] == 0x27)
                {
                    uart_write_bytes(EX_UART_NUM, (const char *)&connect_ok, sizeof(connect_ok));
                }
                else if (dtmp[0] == 0x25 && dtmp[1] == 0x25)
                {
                    // ESP_LOGI(TAG, "read is 0x25");
                    for (size_t i = 2; i < event.size; i++)
                    {
                        self->key_value[i - 2] = dtmp[i]; // 存入键值以及模式
                    }
                    self->read_message_flag = true; // 收到了消息
                    uart_write_bytes(EX_UART_NUM, (const char *)&read_data_ok, sizeof(read_data_ok));
                }
                else if (dtmp[0] == 0x33 && dtmp[1] == 0x33)  // 返回键值
                {
                    /*合并数组*/
                    uint8_t my_key[] = {0x33, 0x33};
                    size_t my_key_len = sizeof(my_key) / sizeof(my_key[0]);
                    size_t key_list_len = sizeof(self->key_value) / sizeof(self->key_value[0]);
                    uint8_t combined_key[key_list_len + my_key_len]; // 储存合并后结果
                    for (size_t i = 0; i < my_key_len; ++i)          // 将返回的头添加
                    {
                        combined_key[i] = my_key[i];
                    }
                    for (size_t i = 0; i < key_list_len; ++i) // 将键值添加
                    {
                        combined_key[my_key_len + i] = (uint8_t)self->key_value[i];
                    }
                    /*END*/
                    uart_write_bytes(EX_UART_NUM, (const char *)&combined_key, sizeof(combined_key));
                }
                else if (dtmp[0] == 0x29 && dtmp[1] == 0x29) // 清除nvs
                {
                    ESP_ERROR_CHECK(device_nvs_clean());
                    uart_write_bytes(EX_UART_NUM, (const char *)&clean_ok, sizeof(clean_ok));
                }
                break;
            // Event of HW FIFO overflow detected
            case UART_FIFO_OVF:
                ESP_LOGI(TAG, "hw fifo overflow");
                // If fifo overflow happened, you should consider adding flow control for your application.
                // The ISR has already reset the rx FIFO,
                // As an example, we directly flush the rx buffer here in order to read more data.
                uart_flush_input(EX_UART_NUM);
                xQueueReset(uart0_queue);
                break;
            // Event of UART ring buffer full
            case UART_BUFFER_FULL:
                ESP_LOGI(TAG, "ring buffer full");
                // If buffer full happened, you should consider increasing your buffer size
                // As an example, we directly flush the rx buffer here in order to read more data.
                uart_flush_input(EX_UART_NUM);
                xQueueReset(uart0_queue);
                break;
            // Event of UART RX break detected
            case UART_BREAK:
                ESP_LOGI(TAG, "uart rx break");
                break;
            // Event of UART parity check error
            case UART_PARITY_ERR:
                ESP_LOGI(TAG, "uart parity error");
                break;
            // Event of UART frame error
            case UART_FRAME_ERR:
                ESP_LOGI(TAG, "uart frame error");
                break;
            // UART_PATTERN_DET
            case UART_PATTERN_DET:
                uart_get_buffered_data_len(EX_UART_NUM, &buffered_size);
                int pos = uart_pattern_pop_pos(EX_UART_NUM);
                ESP_LOGI(TAG, "[UART PATTERN DETECTED] pos: %d, buffered size: %d", pos, buffered_size);
                if (pos == -1)
                {
                    // There used to be a UART_PATTERN_DET event, but the pattern position queue is full so that it can not
                    // record the position. We should set a larger queue size.
                    // As an example, we directly flush the rx buffer here.
                    uart_flush_input(EX_UART_NUM);
                }
                else
                {
                    uart_read_bytes(EX_UART_NUM, dtmp, pos, 100 / portTICK_PERIOD_MS);
                    uint8_t pat[PATTERN_CHR_NUM + 1];
                    memset(pat, 0, sizeof(pat));
                    uart_read_bytes(EX_UART_NUM, pat, PATTERN_CHR_NUM, 100 / portTICK_PERIOD_MS);
                    ESP_LOGI(TAG, "read data: %s", dtmp);
                    ESP_LOGI(TAG, "read pat : %s", pat);
                }
                break;
            // Others
            default:
                ESP_LOGI(TAG, "uart event type: %d", event.type);
                break;
            }
        }
    }
    free(dtmp);
    dtmp = NULL;
    vTaskDelete(NULL);
}