#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// 設定LED燈泡連接的GPIO引腳
#define LED1_PIN 9  // LED1使用GPIO 9
#define LED2_PIN 16  // LED2使用GPIO 16

// 初始化 GPIO 引腳配置
void gpio_init()
{
    gpio_config_t io_conf;
    
    // 設定LED1引腳
    io_conf.pin_bit_mask = (1ULL << LED1_PIN);  // 設置GPIO 2為輸出
    io_conf.mode = GPIO_MODE_OUTPUT;  // 設置為輸出模式
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;  // 禁用上拉電阻
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;  // 禁用下拉電阻
    gpio_config(&io_conf);  // 設定GPIO 9配置

    // 設定LED2引腳
    io_conf.pin_bit_mask = (1ULL << LED2_PIN);  // 設置GPIO 4為輸出
    io_conf.mode = GPIO_MODE_OUTPUT;  // 設置為輸出模式
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;  // 禁用上拉電阻
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;  // 禁用下拉電阻
    gpio_config(&io_conf);  // 設定GPIO 16配置
}

// LED 閃爍控制函數，交替控制兩個燈泡
void led_blink_task(void *arg)
{
    while (true) {
        // 開啟LED1，關閉LED2
        gpio_set_level(LED1_PIN, 1);  // 打開LED1
        gpio_set_level(LED2_PIN, 0);  // 關閉LED2
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // 延遲1000毫秒

        // 開啟LED2，關閉LED1
        gpio_set_level(LED1_PIN, 0);  // 關閉LED1
        gpio_set_level(LED2_PIN, 1);  // 打開LED2
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 延遲1000毫秒
    }
}

// 主函數
void app_main()
{
    // 初始化GPIO引腳
    gpio_init();

    // 創建一個 LED 閃爍任務
    xTaskCreate(led_blink_task, "LED_blink_task", 2048, NULL, 5, NULL);
}
