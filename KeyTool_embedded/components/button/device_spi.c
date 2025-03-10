#include "_74hc165_button.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"

#define PL  39
#define CLK 38
#define CE  21
#define OUT_PUT_SEL ((1ULL<<CE)|(1ULL<<PL))
#define MISO_Q7 40
#define REG_HOST SPI2_HOST
#define CLK_FREQ         (4000)           // SPI_CLK频率

spi_device_handle_t spi;

static void cs_high(spi_transaction_t* t);
static void cs_low(spi_transaction_t* t);
/*初始化GPIO*/
int device_gpio_init(void)
{
    gpio_config_t io_conf = {};
    //PL CLK 输出
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = OUT_PUT_SEL;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    return 0;
}

/*初始化SPI*/
int device_spi_init(void)
{
    spi_bus_config_t buscfg = {
        .miso_io_num = MISO_Q7,
        // .mosi_io_num = -1,
        .sclk_io_num = CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 32,
    };
    //Initialize the SPI bus
    spi_bus_initialize(REG_HOST, &buscfg, SPI_DMA_CH_AUTO);
    return 0;
}

/*配置SPI*/
int device_spi_config(void)
{
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = CLK_FREQ,
        .mode = 0,          
        .spics_io_num = -1,
        .queue_size = 7,
        .pre_cb = cs_high,
        .post_cb = cs_low,
    };
    //Attach the EEPROM to the SPI bus
    spi_bus_add_device(REG_HOST, &devcfg, &spi);
    return 0;
}

/*SPI读取*/
int device_spi_read(void)
{
    uint8_t tx_dummy[7] = {0}; // 分配7个字节的虚拟数据作为发送缓冲区  
    uint8_t rx_buffer[7]; // 分配7个字节的内存来存储接收到的数据    
    spi_transaction_t t = {    
        .tx_buffer = tx_dummy, // 使用虚拟数据作为发送缓冲区  
        .rx_buffer = rx_buffer, // 设置rx_buffer以指向分配的内存    
        .rxlength = 8,    
        .length = 8, // 确保发送和接收长度匹配（在某些实现中可能需要）  
    };    
    spi_device_polling_transmit(spi, &t);
    // printf("rx_data: %02x\n", rx_buffer[0]); // 从rx_buffer中打印数据 
    return rx_buffer[0];   
}

static void cs_high(spi_transaction_t* t)
{
    gpio_set_level(CE, 0);
    gpio_set_level(PL, 1);
}

static void cs_low(spi_transaction_t* t)
{
    gpio_set_level(CE, 1);
    gpio_set_level(PL, 0);
}