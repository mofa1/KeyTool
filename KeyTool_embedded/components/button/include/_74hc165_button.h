#pragma once

#include "base_button.h"
#include "stdbool.h"

/*设备接口*/
typedef int (*device_spi_init_fn_t)(void);
typedef int (*device_spi_config_fn_t)(void);
typedef int (*device_spi_read_fn_t)(void);
struct device_spi_i
{
	device_spi_init_fn_t 	spi_init;
    device_spi_config_fn_t  spi_config;
	device_spi_read_fn_t 	spi_get;
};
int device_spi_init(void);
int device_spi_config(void);
int device_spi_read(void);

typedef int (*device_gpio_init_fn_t)(void);
struct device_gpio_i
{
	device_gpio_init_fn_t gpio_init;
};
int device_gpio_init(void);


/*外调接口*/
struct _74hc165_config{
    bool trigger_mode;   //1立即触发，0 松开触发
};

struct _74hc165_button
{
    struct button_i *interface;
    struct device_spi_i *spi_interface;    
    struct device_gpio_i *gpio_interface;                  
    int but_num;
    bool trigger_mode;
    int last_butnum;
};
int _74hc165_button_init(struct _74hc165_button *self,struct _74hc165_config *cfg);       // 初始化
int _74hc165_button_get_num(struct _74hc165_button *self);    // 获取触发钮编号
