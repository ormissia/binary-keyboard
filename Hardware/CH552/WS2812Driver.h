#ifndef __WS2812DRIVER_H__
#define __WS2812DRIVER_H__

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

void ws2812_init(uint8_t pin, uint8_t led_count);
void ws2812_write_led(uint8_t index, uint8_t r, uint8_t g, uint8_t b);
void ws2812_update(void);

#ifdef __cplusplus
}
#endif

#endif 