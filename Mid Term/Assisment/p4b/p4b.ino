// Problem 4(b): PCINT on PD6 & PD7 (push buttons) toggle LEDs on PD2 & PD3
volatile byte lastPINDstate = 0;

void setup() {
  DDRD &= ~((1 << DDD6) | (1 << DDD7));   // Pin6, Pin7 = inputs
  PORTD |= (1 << PORTD6) | (1 << PORTD7); // enable internal pull-ups
  DDRD  |= (1 << DDD2) | (1 << DDD3);     // Pin2, Pin3 = outputs (LEDs)

  lastPINDstate = PIND;
  PCICR  |= (1 << PCIE2);                 // enable PCINT[23:16] group (PORTD)
  PCMSK2 |= (1 << PCINT22) | (1 << PCINT23); // unmask PD6 (PCINT22), PD7 (PCINT23)
  sei();
}

ISR(PCINT2_vect) {
  byte now = PIND;
  byte changed = now ^ lastPINDstate;   // bits that flipped since last time

  if (changed & (1 << PORTD6)) {         // PD6 (Pin 6) changed
    PORTD ^= (1 << PORTD2);              // toggle LED on Pin 2
  }
  if (changed & (1 << PORTD7)) {         // PD7 (Pin 7) changed
    PORTD ^= (1 << PORTD3);              // toggle LED on Pin 3
  }
  lastPINDstate = now;
}

void loop() {
  // idle - everything is handled in the PCINT2 ISR
}
