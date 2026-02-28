#define BUT_DOWN_PIN 14

int cur_millis, wake_millis;
bool asleep=false;

void spavanje_setup() {
  pinMode(BUT_DOWN_PIN, INPUT_PULLUP);

  wake_millis = millis();
}

void spavanje_loop() {
  if (!asleep) {
    cur_millis = millis();
    if (cur_millis - wake_millis >= 30*1000) {
      asleep = true;
    }
  }
  else {
    if (!digitalRead(BUT_DOWN_PIN)) {
      asleep = false;
      wake_millis = millis();
    }
  }
}
