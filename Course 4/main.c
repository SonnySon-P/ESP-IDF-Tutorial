#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// 定義按鈕和LED引腳
#define BUTTON_PIN 16  // 按鈕接在GPIO 16
#define LED_PIN 9  // LED 燈泡接在GPIO 9

// 初始化GPIO
void gpio_init()
{
  gpio_config_t io_conf = {};

  // 設定LED引腳
  io_conf.pin_bit_mask = (1ULL << LED_PIN);  // 設定GPIO 16為輸出
  io_conf.mode = GPIO_MODE_OUTPUT;  // 設定為輸出模式
  gpio_config(&io_conf);  // 設定GPIO配置

  // 設定BUTTON引腳
  io_conf.pin_bit_mask = (1ULL << BUTTON_PIN);  // 設定GPIO 9為輸入
  io_conf.mode = GPIO_MODE_INPUT;  // 設定為輸入模式
  io_conf.pull_up_en = GPIO_PULLUP_ENABLE;  // 啟用內建上拉電阻，按鈕未按下時為高電平
  gpio_config(&io_conf);  // 設定GPIO配置
}

// 主程式
void app_main()
{
  // 初始化GPIO設定
  gpio_init();

  // 上一次的按鈕狀態，初始化為false(假設按鈕沒被按下)
  bool last_button_state = false;

  while (true) {
    // 讀取當前按鈕狀態
    bool current_button_state = gpio_get_level(BUTTON_PIN);

    // 檢查按鈕是否被按下(因使用了內建上拉電阻，當按鈕未被按下時，GPIO引腳會保持為高電位(true)；當按鈕被按下時，GPIO引腳會被拉低至低電位(false))
    if (current_button_state == false) {
      if (last_button_state == false) {
        // 打開LED
        gpio_set_level(LED_PIN, 1);
        last_button_state = true;
        printf("按鈕被按下，LED被打開\n");
      } else {
        // 關閉LED
        gpio_set_level(LED_PIN, 0);
        last_button_state = false;
        printf("按鈕被按下，LED被關閉\n");
      }

      // 防止重複觸發，等待按鈕釋放
      while (!gpio_get_level(BUTTON_PIN)) {
        vTaskDelay(10 / portTICK_PERIOD_MS);
      }
    }

    // 防止過度佔用CPU
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
