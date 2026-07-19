// Problem 4(a): 563 ms LED blink via Timer0 CTC interrupt, prescaler 1024
// LED on Pin 1 (RX) - for a real build prefer a spare pin; kept as Pin 1 per spec.
const int LED_PIN = 1;          // Pin r = 1
volatile unsigned int isrCount = 0;
const unsigned int TARGET_COUNT = 463;   // 463 x 1.216 ms = 563.008 ms

void setup() {
  pinMode(LED_PIN, OUTPUT);
  noInterrupts();
  TCCR0A = (1 << WGM01);          // CTC mode
  TCCR0B = (1 << CS02) | (1 << CS00);  // prescaler = 1024 (CS02:01:00 = 101)
  OCR0A  = 18;                    // 19 ticks/interrupt -> 1.216 ms
  TIMSK0 |= (1 << OCIE0A);
  interrupts();
}

ISR(TIMER0_COMPA_vect) {
  isrCount++;
  if (isrCount >= TARGET_COUNT) {
    isrCount = 0;
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));   // toggle every 563 ms
  }
}

void loop() {
  // LED blinking is entirely interrupt-driven; loop() is free for other tasks
}
