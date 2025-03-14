#include <Arduino.h>
#include "ws2812.h"
#include "WS2812Driver.h"

// RGB渐变变暗函数
ws2812_rgb_color ws2812_rgb_config_random() {
    static uint8_t r = 0, g = 0, b = 0;
    
    // 生成随机颜色 (仅在开始时)
    if (r == 0 && g == 0 && b == 0) {
        r = random(50);  // 随机生成RGB值
        g = random(50);
        b = random(50);
    }
    
    ws2812_rgb_color color = {r, g, b};
    return color;
}
