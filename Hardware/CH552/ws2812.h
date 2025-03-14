#ifndef __WS2812_H__
#define __WS2812_H__
#include <Arduino.h>

// 定义WS2812 RGB颜色结构体
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} ws2812_rgb_color;

// 函数声明
ws2812_rgb_color ws2812_rgb_config_random(void);

#endif /* __WS2812_H__ */ 