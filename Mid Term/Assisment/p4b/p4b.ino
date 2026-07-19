#include <avr/io.h>
#include <avr/interrupt.h>

volatile bool timerLed  = false;   // LED on D3 (Timer1)
volatile bool buttonLed = false;   // LEDs on D10 + D11 (INT0)

void setup() {
  pinMode(3, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(2, INPUT_PULLUP);

  cli();

  // Timer1: CTC, prescaler 1024, toggle every 542 ms
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A  = 8468;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);

  // INT0: falling edge on D2
  EICRA |=  (1 << ISC01);
  EICRA &= ~(1 << ISC00);
  EIMSK |=  (1 << INT0);

  sei();
}

ISR(TIMER1_COMPA_vect) {
  timerLed = !timerLed;
  digitalWrite(3, timerLed);
}

ISR(INT0_vect) {
  buttonLed = !buttonLed;
  digitalWrite(10, buttonLed);
  digitalWrite(11, buttonLed);
}

void loop() {
}
