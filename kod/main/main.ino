#include <FastLED.h>
#include <LSM6DS3-SOLDERED.h>

#define POSX_PIN 11
#define POSY_PIN 12
#define SWITCH_PIN 10
#define BUT_UP_PIN 41
#define BUT_LEFT_PIN 39
#define BUT_RIGHT_PIN 40
#define BUT_DOWN_PIN 14
#define BUZZER_PIN 42

int16_t but_up, but_left, but_right, but_down, but_switch, pos_y, pos_x;

typedef struct {
  int16_t buttons;
  int16_t joy_x;
  int16_t joy_y;
  int16_t tilt_x;
  int16_t tilt_y;
  int16_t tilt_z;
} joystick_packet_t;

joystick_packet_t joystick = {0};

void led_setup();
void led_loop();
void akcelerometar_setup();
void akcelerometar_loop();

extern int16_t global_tilt_x;
extern int16_t global_tilt_y;
extern int16_t global_tilt_z;

int fix_stick(int data) {
  int val = (data * 200 / 4095) - 100;
  if (abs(val) < 4) return 0;
  return val;
}

void setup() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(BUT_UP_PIN, INPUT_PULLUP);
  pinMode(BUT_LEFT_PIN, INPUT_PULLUP);
  pinMode(BUT_RIGHT_PIN, INPUT_PULLUP);
  pinMode(BUT_DOWN_PIN, INPUT_PULLUP);

  pinMode(POSX_PIN, INPUT);
  pinMode(POSY_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(115200); 
  delay(2000);

  led_setup();
  akcelerometar_setup();
}

void loop() {
  but_up = 1-digitalRead(BUT_UP_PIN);
  but_left = 1-digitalRead(BUT_LEFT_PIN);
  but_right = 1-digitalRead(BUT_RIGHT_PIN);
  but_down = 1-digitalRead(BUT_DOWN_PIN);
  but_switch = 1-digitalRead(SWITCH_PIN);

  pos_x = fix_stick(analogRead(POSX_PIN));
  pos_y = fix_stick(analogRead(POSY_PIN));

  joystick.buttons = 0;
  joystick.buttons |= (but_up ? 1 : 0) << 0;
  joystick.buttons |= (but_right ? 1 : 0) << 1;
  joystick.buttons |= (but_left ? 1 : 0) << 2;
  joystick.buttons |= (but_down ? 1 : 0) << 3;
  joystick.buttons |= (but_switch ? 1 : 0) << 4;

  joystick.joy_x = pos_x;
  joystick.joy_y = pos_y;

  led_loop();
  akcelerometar_loop();

  joystick.tilt_x = global_tilt_x;
  joystick.tilt_y = global_tilt_y;
  joystick.tilt_z = global_tilt_z;

  Serial.write((uint8_t*)&joystick, sizeof(joystick));

  delay(20);
}
