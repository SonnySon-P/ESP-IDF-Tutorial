#include <stdio.h>  // 引入標準輸入輸出函式庫
#include "freertos/FreeRTOS.h"  // 引入FreeRTOS核心函式庫
#include "freertos/task.h"  // 引入FreeRTOS任務管理函式庫

void app_main() {
  printf("Hello, World!\n");  // 輸出訊息，顯示"Hello, World!"
  
  // 無窮迴圈
  while (true) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // 延遲1000毫秒，portTICK_PERIOD_M通常默認設置為1毫秒，用途在確保在不同硬體平台上保持時間單位一致性
  }
}