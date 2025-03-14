#ifndef USER_USB_RAM
#error "This program needs to be compiled with a USER USB setting"
#endif

#include "WS2812Driver.h"
#include "USBHIDKeyboard.h"
#include "ws2812.h"

// Pin define
#define LED_PIN 11
#define WS2812_PIN 15

#define KEY0_PIN 33
#define KEY1_PIN 34
#define KEY2_PIN 31
#define KEY3_PIN 30
#define FUNC_PIN 32

//定义控制的RGB LED数量
#define NUMPIXELS 4

// 按键映射配置
const char MODE1_KEYS[] = { 'c', 'v', KEY_LEFT_CTRL, KEY_RETURN };  // CV模式按键映射
const char MODE2_KEYS[] = { '0', '1', KEY_LEFT_CTRL, KEY_RETURN };  // 数字模式按键映射
const char* currentKeys = MODE1_KEYS;                               // 当前使用的按键映射

ws2812_rgb_color KEY_COLORS[] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };

// 状态变量
bool key0PressPrev = false;
bool key1PressPrev = false;
bool key2PressPrev = false;
bool key3PressPrev = false;
bool funcModePrev = false;

// KEY_COLORS每个值减一
void key_color_decrement() {
  for (int i = 0; i < NUMPIXELS; i++) {
    if (KEY_COLORS[i].r > 0) {
      KEY_COLORS[i].r--;
    }
    if (KEY_COLORS[i].g > 0) {
      KEY_COLORS[i].g--;
    }
    if (KEY_COLORS[i].b > 0) {
      KEY_COLORS[i].b--;
    }
    ws2812_write_led(i, KEY_COLORS[i].r, KEY_COLORS[i].g, KEY_COLORS[i].b);
  }

  ws2812_update();
}

void random_color(uint8_t index) {
  KEY_COLORS[index] = ws2812_rgb_config_random();
}


void setup() {
  USBInit();
  pinMode(LED_PIN, OUTPUT);
  pinMode(KEY0_PIN, INPUT_PULLUP);
  pinMode(KEY1_PIN, INPUT_PULLUP);
  pinMode(KEY2_PIN, INPUT_PULLUP);
  pinMode(KEY3_PIN, INPUT_PULLUP);
  pinMode(FUNC_PIN, INPUT_PULLUP);
  // 初始化 WS2812
  ws2812_init(WS2812_PIN, NUMPIXELS);
  randomSeed(analogRead(0));
}

void loop() {
  // 检测功能键状态，按下时换模式
  bool funcMode = !digitalRead(FUNC_PIN);
  if (funcModePrev != funcMode) {
    funcModePrev = funcMode;
    if (funcMode) {
      digitalWrite(LED_PIN, LOW);
      currentKeys = (currentKeys == MODE1_KEYS) ? MODE2_KEYS : MODE1_KEYS;
    } else {
      digitalWrite(LED_PIN, HIGH);
    }
  }

  bool key0Press = !digitalRead(KEY0_PIN);
  if (key0PressPrev != key0Press) {
    key0PressPrev = key0Press;
    key0Press ? Keyboard_press(currentKeys[0]) : Keyboard_release(currentKeys[0]);
    random_color(0);
  }

  bool key1Press = !digitalRead(KEY1_PIN);
  if (key1PressPrev != key1Press) {
    key1PressPrev = key1Press;
    key1Press ? Keyboard_press(currentKeys[1]) : Keyboard_release(currentKeys[1]);
    random_color(1);
  }

  bool key2Press = !digitalRead(KEY2_PIN);
  if (key2PressPrev != key2Press) {
    key2PressPrev = key2Press;
    key2Press ? Keyboard_press(currentKeys[2]) : Keyboard_release(currentKeys[2]);
    random_color(2);
  }

  bool key3Press = !digitalRead(KEY3_PIN);
  if (key3PressPrev != key3Press) {
    key3PressPrev = key3Press;
    key3Press ? Keyboard_press(currentKeys[3]) : Keyboard_release(currentKeys[3]);
    random_color(3);
  }

  key_color_decrement();
}
