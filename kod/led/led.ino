#include <FastLED.h>

#define LED_PIN 2

CRGB led[1];
uint8_t hue = 0;

void setup() {
  Serial.begin(115200);

  FastLED.addLeds<WS2812, LED_PIN>(led, 1);
  FastLED.setBrightness(255);
}

void loop() {
  led[0] = CHSV(hue, 255, 255);
  hue = (hue+1) % 256;
  FastLED.show();
  delay(20);
}
