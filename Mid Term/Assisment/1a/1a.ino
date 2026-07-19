// Biscuit counter - Part (a): exact 10 ms tick using Timer1 CTC mode
// Assumed system clock = 14 MHz (per problem statement), prescaler = 8
// ID 24-56637-1: r0 ms = 10 ms, clock 1q MHz = 14 MHz
volatile unsigned long packetCount_a = 0;

void setupTimer1_10ms() {
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A  = 17499;            // N-1 for exact 10 ms @ 14 MHz / prescaler 8
  TCCR1B |= (1 << WGM12);    // CTC mode (WGM13:0 = 0100)
  TCCR1B |= (1 << CS11);     // prescaler = 8  (CS12:11:10 = 010)
  TIMSK1 |= (1 << OCIE1A);   // enable Timer1 Compare-A interrupt
  interrupts();
}

ISR(TIMER1_COMPA_vect) {
  packetCount_a++;            // one biscuit packet counted every 10 ms
  PORTB ^= (1 << PORTB0);     // toggle D8 - scope shows the 10 ms interval
}

void setup() {
  pinMode(8, OUTPUT);        // D8 = PB0, toggled for the oscilloscope
  Serial.begin(9600);
  UCSR0A &= ~(1 << U2X0);    // normal-speed UART (Serial.begin left U2X on)
  UBRR0 = 90;                // baud fix @ 14 MHz: 14e6/(16x9600)-1 = 90
  setupTimer1_10ms();
}

void loop() {
  Serial.print("Packets (10 ms interval): ");
  Serial.println(packetCount_a);
  delay(1000);
}
