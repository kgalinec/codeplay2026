#ifndef BUZZER_PIN
#define BUZZER_PIN 42
#endif

#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392

int tempo = 200; 

int melody[] = {
  NOTE_E4,4,  NOTE_E4,4,  NOTE_F4,4,  NOTE_G4,4,
  NOTE_G4,4,  NOTE_F4,4,  NOTE_E4,4,  NOTE_D4,4,
  NOTE_C4,4,  NOTE_C4,4,  NOTE_D4,4,  NOTE_E4,4,
  NOTE_E4,-4, NOTE_D4,8,  NOTE_D4,2 
};

int notes = sizeof(melody)/sizeof(melody[0])/2; 

int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

void uvodna_pjesma_setup() {
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
    }

    tone(BUZZER_PIN, melody[thisNote], noteDuration*0.9);
    delay(noteDuration);
    noTone(BUZZER_PIN);
    led_loop();
  }
}

void uvodna_pjesma_loop() {
  
}