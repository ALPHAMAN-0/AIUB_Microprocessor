#define RED_PIN 8
#define YELLOW_PIN 10
#define GREEN_PIN 12

int red_on = 6000;        // 6 s   (manual's "3 s" comment is wrong — 6000 ms is 6 s)
int green_on = 3000;      // 3 s
int yellow_blink = 500;   // 0.5 s

int delay_timer(int milliseconds) {
  int count = 0;
  while (1) {
    if (TCNT0 >= 15) {
      TCNT0 = 0;
      count++;
      if (count == milliseconds) {
        count = 0;
        break;
      }
    }
  }
  return 0;
}

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  TCCR0A = 0b00000000;
  TCCR0B = 0b00000101;
  TCNT0 = 0;
}

void loop() {
  digitalWrite(GREEN_PIN, HIGH);
  delay_timer(green_on);
  digitalWrite(GREEN_PIN, LOW);

  for (int i = 0; i < 4; i++) {   // yellow blinks 4 times
    digitalWrite(YELLOW_PIN, HIGH);
    delay_timer(yellow_blink);
    digitalWrite(YELLOW_PIN, LOW);
    delay_timer(yellow_blink);
  }

  digitalWrite(RED_PIN, HIGH);
  delay_timer(red_on);
  digitalWrite(RED_PIN, LOW);
}
