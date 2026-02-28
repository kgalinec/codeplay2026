#define BUZZER_PIN 42
#define VIBRATE_PIN 21

void buzzer_vib_setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(VIBRATE_PIN, OUTPUT);

  tone(BUZZER_PIN, 1000);
  delay(300);      
  noTone(BUZZER_PIN);
  delay(300);
  
  for (int vibrateTime = 255; vibrateTime > 0; vibrateTime = vibrateTime - 1) {
    analogWrite(VIBRATE_PIN, vibrateTime);
    delay(20);
  }
  
  analogWrite(VIBRATE_PIN, 0); 
}

void buzzer_vib_loop(int16_t but_left) {
  analogWrite(VIBRATE_PIN, but_left * 255);
}
