// Problem 2(b): read a debounced switch on Pin 2, mirror its state on LED Pin 11
// Debounce interval = 40 ms, generated from Timer0 (millis()-based non-blocking wait)
const int SWITCH_PIN = 2;   // Pin p = 2
const int LED_PIN    = 11;  // Pin 1r = 11
const unsigned long DEBOUNCE_MS = 40;  // Pin change occurs on q0 ms = 40 ms bounce window

int lastRaw = HIGH;
int debouncedState = HIGH;
unsigned long lastChangeTime = 0;

void setup() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);   // switch to GND when pressed
  pinMode(LED_PIN, OUTPUT);
  // Timer0 already runs millis()/micros() by default on the Uno -
  // it is used here as the debounce reference clock instead of delay().
}

void loop() {
  int raw = digitalRead(SWITCH_PIN);

  if (raw != lastRaw) {
    lastChangeTime = millis();   // restart the debounce window (Timer0 tick)
    lastRaw = raw;
  }

  if ((millis() - lastChangeTime) > DEBOUNCE_MS) {
    if (raw != debouncedState) {
      debouncedState = raw;
      // active-low switch: pressed (LOW) -> LED ON, released (HIGH) -> LED OFF
      digitalWrite(LED_PIN, debouncedState == LOW ? HIGH : LOW);
    }
  }
}
