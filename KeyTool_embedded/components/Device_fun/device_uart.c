#include "Device_fun.h"
#include "driver/uart.h"


int device_uart_init(void *handle,int uart_num,int buf_size, int pattern_chr_num)
{
    
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    uart_driver_install(uart_num,buf_size*2,buf_size*2,20,handle,0); // 安装Uart驱动
    if (handle == NULL)
    {
        printf("handle error\n");
        return 1;
    }
    
    uart_param_config(uart_num,&uart_config);

    uart_set_pin(uart_num,UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE); // 设置串口引脚

    uart_enable_pattern_det_baud_intr(uart_num,'+',pattern_chr_num,9,0,0); // 设置串口检测方法
    uart_pattern_queue_reset(uart_num,20); // 串口发送队列

    printf("uart init ok!\n");
    return 0;
}