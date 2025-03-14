#include "WS2812Driver.h"
#include <Arduino.h>

#define WS2812_MAX_LEDS 20  // 支持的最大LED数量

static uint8_t led_data[WS2812_MAX_LEDS * 3];  // 预分配最大可能的空间
static uint8_t ws2812_pin;
static uint8_t num_leds = 0;  // 实际使用的LED数量

// 发送1码的时序
static inline void ws2812_send_bit_1(void) {
    digitalWrite(ws2812_pin, HIGH);
    delayMicroseconds(1);
    digitalWrite(ws2812_pin, LOW);
    delayMicroseconds(1);
}

// 发送0码的时序
static inline void ws2812_send_bit_0(void) {
    digitalWrite(ws2812_pin, HIGH);
    delayMicroseconds(0);
    digitalWrite(ws2812_pin, LOW);
    delayMicroseconds(1);
}

void ws2812_init(uint8_t pin, uint8_t led_count) {
    ws2812_pin = pin;
    
    // 确保LED数量不超过最大值
    num_leds = (led_count <= WS2812_MAX_LEDS) ? led_count : WS2812_MAX_LEDS;
    
    // 初始化所有LED数据为0（关闭状态）
    memset(led_data, 0, num_leds * 3);
    
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void ws2812_write_led(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
    if (index >= num_leds) return;
    
    uint16_t start = index * 3;
    led_data[start] = g;
    led_data[start + 1] = r;
    led_data[start + 2] = b;
}

void ws2812_update(void) {
    uint8_t i, j;
    
    noInterrupts();  // 禁用中断
    
    for (i = 0; i < num_leds * 3; i++) {
        uint8_t byte = led_data[i];
        
        for (j = 0; j < 8; j++) {
            if (byte & 0x80) {
                // 1 码
                ws2812_send_bit_1();
            } else {
                // 0 码
                ws2812_send_bit_0();
            }
            byte <<= 1;
        }
    }
    
    interrupts();  // 重新启用中断
}
