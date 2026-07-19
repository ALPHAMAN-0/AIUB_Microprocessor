// Biscuit counter - Part (b): EXACT 566 ms using Timer1 CTC + interrupt counting
// System clock = 14 MHz, prescaler = 8 -> 2.000 ms hardware tick, 283 ticks = 566 ms
// ID 24-56637-1: abc ms = 566 ms, clock 1q MHz = 14 MHz
volatile unsigned int  subCount      = 0;   // counts 2 ms sub-periods
volatile unsigned long packetCount_b = 0;   // one packet per full 566 ms window
const unsigned int SUB_TARGET = 283;        // 283 x 2.000 ms = 566.000 ms EXACT

void setupTimer1_566ms() {
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A  = 3499;             // (3500 - 1) -> 3500 x 8 / 14 MHz = 2.000 ms exactly
  TCCR1B |= (1 << WGM12);    // CTC mode
  TCCR1B |= (1 << CS11);     // prescaler = 8  (CS12:11:10 = 010)
  TIMSK1 |= (1 << OCIE1A);   // enable Timer1 Compare-A interrupt
  interrupts();
}

ISR(TIMER1_COMPA_vect) {
  subCount++;
  if (subCount >= SUB_TARGET) {      // every 283rd interrupt = exactly 566 ms
    subCount = 0;
    packetCount_b++;                 // one biscuit packet counted every 566 ms
    PORTB ^= (1 << PORTB0);          // toggle D8 - scope shows the 566 ms interval
  }
}

void setup() {
  pinMode(8, OUTPUT);        // D8 = PB0, toggled for the oscilloscope
  Serial.begin(9600);
  UCSR0A &= ~(1 << U2X0);    // normal-speed UART (Serial.begin left U2X on)  <-- ADD THIS
  UBRR0 = 90;                // baud fix @ 14 MHz: 14e6/(16x9600)-1 = 90
  setupTimer1_566ms();
}

void loop() {
  Serial.print("Packets (566 ms interval): ");
  Serial.println(packetCount_b);
  delay(2000);
}
