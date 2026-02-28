#define BUT_DOWN_PIN 14

int cur_millis, wake_millis;
bool asleep=false;

void spavanje_setup() {
  pinMode(BUT_DOWN_PIN, INPUT_PULLUP);

  esp_sleep_enable_ext0_wakeup((gpio_num_t)BUT_DOWN_PIN, 0);
  gpio_pullup_en((gpio_num_t)BUT_DOWN_PIN);
  gpio_pulldown_dis((gpio_num_t)BUT_DOWN_PIN);
  
  wake_millis = millis();
  Serial.flush();
  esp_light_sleep_start();
}

void spavanje_loop() {
  Serial.print('a');
  Serial.println();
  cur_millis = millis();
  if (cur_millis - wake_millis >= 30*1000) {
    asleep = true;
    esp_light_sleep_start();
  }
}
