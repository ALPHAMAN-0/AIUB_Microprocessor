#include <LowPower.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}                              // ← add this closing bracket

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}
