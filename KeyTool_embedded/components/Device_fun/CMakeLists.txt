idf_component_register(SRCS "device_uart.c" 
                            "device_nvs.c"
                            "device_usb_hid.c"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_driver_uart
                    REQUIRES nvs_flash
                    REQUIRES esp_tinyusb)