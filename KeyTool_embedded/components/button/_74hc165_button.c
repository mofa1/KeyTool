#include <stdio.h>
#include "_74hc165_button.h"

/*绑定设备驱动*/
struct device_spi_i device_spi = {
    .spi_init = (device_spi_init_fn_t)device_spi_init,
    .spi_config = (device_spi_config_fn_t)device_spi_config,
    .spi_get = (device_spi_read_fn_t)device_spi_read,
};
struct device_gpio_i device_gpio = {
    .gpio_init = (device_gpio_init_fn_t)device_gpio_init,
};

/*绑定外调接口*/
struct button_i interface = {
    .get_num   = (button_get_num_fn_t)_74hc165_button_get_num,
};

/*初始化*/
int _74hc165_button_init(struct _74hc165_button *self,struct _74hc165_config *cfg)
{
    self->spi_interface = &device_spi;
    self->spi_interface->spi_init();
    self->spi_interface->spi_config();
    self->gpio_interface = &device_gpio;
    self->gpio_interface->gpio_init();
    self->interface = &interface;
    self->but_num = 0;
    self->last_butnum = 0;
    self->trigger_mode = cfg->trigger_mode;
    return 0;
}

/*获取按钮的值*/
int _74hc165_button_get_num(struct _74hc165_button *self)
{
    if (self->trigger_mode && self->but_num != 0x00)  //立即触发
    {
        self->but_num = self->spi_interface->spi_get();
        if (self->but_num != 0)
        {
            return self->but_num;
        }
    }else if(!self->trigger_mode) // 松开按钮触发
    {
        self->but_num = self->spi_interface->spi_get();
        if (self->but_num!= 0)    // 按下
        {
            self->last_butnum = self->but_num;    // 记录按下的键值
        }
        if (self->but_num == 0 && self->last_butnum!= 0)  // 松开
        {
            self->but_num = self->last_butnum;
            printf("but_num: %d\n",self->but_num);
            self->last_butnum = 0;
            return self->but_num;
        }
    }  
    return 0;
}
