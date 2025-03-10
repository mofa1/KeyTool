#include "Device_fun.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_log.h"

#define KEY_NAMESPACE "key"

static char* TAG = "NVS";

int device_nvs_init()
{
    // 初始化NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );
    ESP_LOGI(TAG,"NVS INIT OK!");
    return ESP_OK;
}

int device_nvs_read(int32_t *key_value,char **key_name, uint8_t len)
{
    nvs_handle_t my_handle;
    esp_err_t err;

    // 打开NVS
    err = nvs_open(KEY_NAMESPACE,NVS_READWRITE,&my_handle);
    if (err != ESP_OK) return err;

    for (size_t i = 0; i < len; i++)
    {                                    
        err = nvs_get_i32(my_handle,key_name[i],&key_value[i]);  // 写入
        
        if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND) return err;
    }
    return ESP_OK;
}

// 写入
int device_nvs_write(int32_t *key_value,char **key_name,uint8_t len)
{
    nvs_handle_t my_handle;
    esp_err_t err;
    // printf("nvs data is %ld\n",key_value[1]);
    // 打开NVS
    err = nvs_open(KEY_NAMESPACE,NVS_READWRITE,&my_handle);
    if (err != ESP_OK) 
    {
        printf("open error\n");
        return err;
    }
    for (size_t i = 0; i < len; i++)
    {                                    
        err = nvs_get_i32(my_handle,key_name[i],&key_value[i]);  // 读取
        // if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND) return err;
    }

    for (size_t i = 0; i < len; i++)
    {                             
        printf("nvs data is %ld\n",key_value[i]);
        err = nvs_set_i32(my_handle,key_name[i],key_value[i]);  // 写入
        if (err != ESP_OK) return err;
    }
    err = nvs_commit(my_handle);                           // 提交写入数值
    if (err != ESP_OK) return err;

    // 关闭NVS
    nvs_close(my_handle);
    return ESP_OK;
}

int device_nvs_clean()
{
    ESP_ERROR_CHECK(nvs_flash_erase()); // 擦除
    return ESP_OK;
}