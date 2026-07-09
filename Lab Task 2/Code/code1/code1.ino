#define RED_PIN 8    // manual wrote "#define YELLOW_PIN 10" but the code uses RED_PIN

int red_on = 2000;   // 2 s on, 2 s off

int delay_timer(int milliseconds) {
  int count = 0;
  while (1) {
    if (TCNT0 >= 15) {        // one Timer0 tick ≈ 64 µs, so 15 ticks ≈ 1 ms
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
  TCCR0A = 0b00000000;
  TCCR0B = 0b00000101;        // prescaler = 1024
  TCNT0 = 0;
}

void loop() {
  digitalWrite(RED_PIN, HIGH);
  delay_timer(red_on);
  digitalWrite(RED_PIN, LOW);
  delay_timer(red_on);
}
