// Problem 4(c): external interrupt INT0 (Pin 2 / PD2) toggles 2 LEDs on PORTB
const int INT0_PIN = 2;    // PD2, INT0
const int LED1_PIN = 12;   // PB4  ("Pin1p" = Pin 12)
const int LED2_PIN = 11;   // PB3  ("Pin1r" = Pin 11)

void toggleLEDs() {
  PORTB ^= (1 << PORTB4);   // toggle LED1 (Pin 12)
  PORTB ^= (1 << PORTB3);   // toggle LED2 (Pin 11)
}

void setup() {
  pinMode(INT0_PIN, INPUT_PULLUP);   // push button to GND
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(INT0_PIN), toggleLEDs, FALLING);
}

void loop() {
  // idle - both LEDs are toggled entirely from the INT0 ISR (toggleLEDs)
}
