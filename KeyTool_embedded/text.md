#include <stdio.h>
#include <stdint.h>

int main() {
    static uint32_t key_list[] = {04, 00, 05, 00, 06, 00, 06};
    uint8_t my_key[] = {0x33, 0x33};
    size_t my_key_len = sizeof(my_key) / sizeof(my_key[0]);
    size_t key_list_len = sizeof(key_list) / sizeof(key_list[0]);

    // 创建一个新的数组来存储合并后的结果
    uint8_t combined_key[my_key_len + key_list_len];

    // 复制my_key的内容到combined_key
    for (size_t i = 0; i < my_key_len; ++i) {
        combined_key[i] = my_key[i];
    }

    // 将key_list的内容转换为uint8_t并复制到combined_key
    for (size_t i = 0; i < key_list_len; ++i) {
        combined_key[my_key_len + i] = (uint8_t)key_list[i];
    }

    // 打印合并后的数组
    printf("Combined key: ");
    for (size_t i = 0; i < my_key_len + key_list_len; ++i) {
        printf("0x%02X ", combined_key[i]);
    }
    printf("\n");

    return 0;
}