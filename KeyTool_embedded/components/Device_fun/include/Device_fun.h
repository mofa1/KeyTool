#pragma once
/*
设备外设接口
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// UART
int device_uart_init(void *handle,int uart_num,int buf_size, int pattern_chr_num);
int device_uart_read();
int device_uart_write();


// SPI
int device_spi_init();
int device_spi_config();
int device_spi_read();


// GPIO
int device_gpio_init();


// NVS
int device_nvs_init();
int device_nvs_read(int32_t *key_value,char **key_name,uint8_t len);
int device_nvs_write(int32_t *key_value,char **key_name,uint8_t len);
int device_nvs_clean();


// USB HID
int device_usb_hid_init();
int device_usb_hid_keyboard_press(uint32_t keycode);
int device_usb_hid_keyboard_release();
int device_usb_hid_mouse_press(uint32_t mousecode);
int device_usb_hid_mouse_release();
