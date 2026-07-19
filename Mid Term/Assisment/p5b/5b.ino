// Problem 5(b): CORRECTED program (ID 24-56637-1 values)
// Bugs fixed from the question listing:
//   1. setup() and loop() bodies were swapped  -> pin config now in setup(), logic in loop()
//   2. missing ';' after red_on / red_off initialisers
//   3. SLEEP2S typo -> SLEEP_2S
//   4. library calls use the real Rocket Scream signatures:
//        idle(period, adc, timer2, timer1, timer0, spi, usart0, twi)
//        powerDown(period, adc, bod)
// RED_PIN = c = 6 ; red_on = rpace = 12567 ms ; red_off = qade = 4537 ms
#include "LowPower.h"
#define RED_PIN 6

int red_on  = 12567;   // LED ON  time = 12.567 s
int red_off = 4537;    // LED OFF time =  4.537 s

void setup() {
  pinMode(RED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(RED_PIN, HIGH);
  delay(red_on);                     // USB meter: 4.956 V, 0.7371 A  -> 3.6531 W
  digitalWrite(RED_PIN, LOW);
  delay(red_off);                    // USB meter: 5.0663 V, 0.1240 A -> 0.6282 W
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,
                SPI_OFF, USART0_OFF, TWI_OFF);   // 8 s idle:  5.56 V, 1.3 mA -> 7.23 mW
  LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF); // 2 s pwr-dn: 5.063 V, 5.7 mA -> 28.86 mW
}
// Sleeping (idle + power-down) saves ~98-99% versus staying active:
// ~21.3 J saved over the 10 s combined sleep window of each cycle.
