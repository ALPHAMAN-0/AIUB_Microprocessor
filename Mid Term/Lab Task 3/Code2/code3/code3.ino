#include <LowPower.h>
#define LED_RED 8

void setup() {
  Serial.begin(9600);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, LOW);
}

void loop() {
  digitalWrite(LED_RED, HIGH);
  delay(4000);
  digitalWrite(LED_RED, LOW);
  delay(4000);
  Serial.println("Arduino:- I am going for a Nap");
LowPower.idle(SLEEP_4S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,
              SPI_OFF, USART0_OFF, TWI_OFF);
  Serial.println("Arduino:- Hey I just Woke up");
}
