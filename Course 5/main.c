#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// 設定繼電器連接的GPIO引腳
#define RELAY_PIN 14  // 繼電器使用GPIO 14

// 初始化GPIO引腳配置
void gpio_init()
{
  gpio_config_t io_conf;
  
  // 設定繼電器連引腳
  io_conf.pin_bit_mask = (1ULL << RELAY_PIN);  // 設置GPIO 14為輸出
  io_conf.mode = GPIO_MODE_OUTPUT;  // 設置為輸出模式
  io_conf.pull_up_en = GPIO_PULLUP_DISABLE;  // 禁用上拉電阻
  io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;  // 禁用下拉電阻
  gpio_config(&io_conf);  // 設定GPIO 9配置
}

void app_main() {
  // 初始化GPIO引腳
  gpio_init();

  while (true) {
    // 開啟RELAY
    gpio_set_level(RELAY_PIN, 1);  // 打開RELAY
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // 延遲1000毫秒

    // 關閉RELAY
    gpio_set_level(RELAY_PIN, 0);  // 關閉RELAY
    vTaskDelay(1000 / portTICK_PERIOD_MS); // 延遲1000毫秒
  }
}
