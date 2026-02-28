#include <FastLED.h>

#define LED_PIN 2

CRGB led[1];
uint8_t hue = 0;

void led_setup() {
  FastLED.addLeds<WS2812, LED_PIN>(led, 1);
  FastLED.setBrightness(200);
}

void led_loop() {
  led[0] = CHSV(hue, 255, 255);
  hue = (hue + 1) % 256;
  FastLED.show();
}
