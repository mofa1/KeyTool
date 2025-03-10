idf_component_register(SRCS "_74hc165_button.c" "device_spi.c"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_driver_gpio
                    REQUIRES esp_driver_spi)
