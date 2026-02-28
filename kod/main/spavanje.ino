#include <FastLED.h>
#include <esp_sleep.h>
#include <driver/gpio.h>

extern CRGB led[];

#ifndef BUZZER_PIN
#define BUZZER_PIN 42
#endif

#ifndef BUT_DOWN_PIN
#define BUT_DOWN_PIN 14
#endif


void led_setup();
void led_loop();

unsigned long zadnja_aktivnost_millis = 0;

void spavanje_setup() {
  pinMode(BUT_DOWN_PIN, INPUT_PULLUP);

  gpio_wakeup_enable((gpio_num_t)BUT_DOWN_PIN, GPIO_INTR_LOW_LEVEL);
  esp_sleep_enable_gpio_wakeup();

  zadnja_aktivnost_millis = millis();
}

void spavanje_loop(int16_t b_up, int16_t b_left, int16_t b_right, int16_t b_down, int16_t b_switch, int j_x, int j_y) {
  
  if (b_up || b_left || b_right || b_down || b_switch || abs(j_x) > 5 || abs(j_y) > 5) {
    zadnja_aktivnost_millis = millis();
  }

  if (millis() - zadnja_aktivnost_millis >= 30000) {
    led[0] = CRGB::Black;
    FastLED.show();

    // Zvuk: gašenje
    tone(BUZZER_PIN, 400, 200);
    delay(250);
    tone(BUZZER_PIN, 300, 250);
    delay(300);
    tone(BUZZER_PIN, 200, 400);
    delay(450);
    noTone(BUZZER_PIN);

    esp_light_sleep_start();

    zadnja_aktivnost_millis = millis();

    Serial.end();
    delay(10);
    Serial.begin(115200);
    Wire.begin(); 

    // Zvuk: paljenje
    tone(BUZZER_PIN, 800, 100);
    delay(150);
    tone(BUZZER_PIN, 1200, 100);
    delay(150);
    tone(BUZZER_PIN, 1600, 200);
    delay(200);
    noTone(BUZZER_PIN);

    led_loop();
  }
}
