const int SwitchPin = 8;
unsigned long PreviousTime = 0;
int SwitchState = 0;
int PrevSwitchState = 0;
int led = 2;
unsigned long interval = 1000; // 1 second per LED step

void setup() {
  for (int x = 2; x < 8; x++) {
    pinMode(x, OUTPUT);
  }
  pinMode(SwitchPin, INPUT);
}

void loop() {
  unsigned long CurrentTime = millis();

  if (CurrentTime - PreviousTime > interval) {
    PreviousTime = CurrentTime;
    if (led <= 7) {
      digitalWrite(led, HIGH);
      led++;
    }
  }

  SwitchState = digitalRead(SwitchPin);
  if (SwitchState != PrevSwitchState) {
    for (int x = 2; x < 8; x++) {
      digitalWrite(x, LOW);   // turn everything off
    }
    led = 2;                  // restart the chase
    PreviousTime = CurrentTime;
  }
  PrevSwitchState = SwitchState;
}
