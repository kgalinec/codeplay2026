#include <FastLED.h>

#ifndef VIBRATE_PIN
#define VIBRATE_PIN 21
#endif
#ifndef BUZZER_PIN
#define BUZZER_PIN 42
#endif

extern CRGB led[];
extern bool igra_gotova; 

void feedback() {
  if (Serial.available() > 0) {
    uint8_t incoming_byte = Serial.read();

    switch (incoming_byte) {
      case 0x01: 
        led[0] = CRGB::Yellow;
        FastLED.show();
        analogWrite(VIBRATE_PIN, 150);
        tone(BUZZER_PIN, 1200, 30);
        delay(30);
        tone(BUZZER_PIN, 1800, 50);
        delay(50);
        analogWrite(VIBRATE_PIN, 0); 
        noTone(BUZZER_PIN);
        break;

      case 0x02: 
        led[0] = CRGB::Green;
        FastLED.show();
        tone(BUZZER_PIN, 800);
        delay(100);
        tone(BUZZER_PIN, 1200);
        delay(150);
        noTone(BUZZER_PIN);
        break;

      case 0x03: 
        led[0] = CRGB::Blue;
        FastLED.show();
        analogWrite(VIBRATE_PIN, 255);
        tone(BUZZER_PIN, 250);
        delay(100);
        analogWrite(VIBRATE_PIN, 0); 
        noTone(BUZZER_PIN);
        break;

      case 0x04: 
        led[0] = CRGB::Red;
        FastLED.show();
        analogWrite(VIBRATE_PIN, 180);
        tone(BUZZER_PIN, 150);
        delay(100);
        noTone(BUZZER_PIN);
        delay(50);
        tone(BUZZER_PIN, 150);
        delay(100);
        analogWrite(VIBRATE_PIN, 0);
        noTone(BUZZER_PIN);
        break;

      case 0x05: 
        igra_gotova = true; 
        
        analogWrite(VIBRATE_PIN, 255);
        tone(BUZZER_PIN, 400);
        delay(300);
        
        analogWrite(VIBRATE_PIN, 128);
        tone(BUZZER_PIN, 300);
        delay(300);
        
        analogWrite(VIBRATE_PIN, 60);
        tone(BUZZER_PIN, 200);
        delay(400);
        
        analogWrite(VIBRATE_PIN, 0);
        noTone(BUZZER_PIN);
        break;

      case 0x00: 
        igra_gotova = false;
        led[0] = CRGB::Black;
        FastLED.show();
        break;

      default:
        break;
    }
  }
}