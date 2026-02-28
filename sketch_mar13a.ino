#define POSX_PIN 11
#define POSY_PIN 12
#define SWITCH_PIN 10

#define BUT_UP_PIN 41
#define BUT_LEFT_PIN 39
#define BUT_RIGHT_PIN 40
#define BUT_DOWN_PIN 14

#define BUZZER_PIN 42


int16_t but_up, but_left, but_right, but_down;


typedef struct {
  int16_t buttons;
  int16_t joy_x;
  int16_t joy_y;
  int16_t tilt_x;
  int16_t tilt_y;
  int16_t tilt_z;
} joystick_packet_t;

void setup() {
  // put your setup code here, to run once:
  pinMode(POSY_PIN, INPUT_PULLUP);
  pinMode(BUT_UP_PIN, INPUT_PULLUP);
  pinMode(BUT_LEFT_PIN, INPUT_PULLUP);
  pinMode(BUT_RIGHT_PIN, INPUT_PULLUP);
  pinMode(BUT_DOWN_PIN, INPUT_PULLUP);

  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600); 
}

void loop() {
  but_up = digitalRead(BUT_UP_PIN));
  but_left = digitalRead(BUT_LEFT_PIN));
  but_right = digitalRead(BUT_RIGHT_PIN));
  but_down = digitalRead(BUT_DOWN_PIN));



  delay(1000);
}
