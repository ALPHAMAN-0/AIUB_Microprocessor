// Problem 3: biohazard lab door light interlock
// GREEN = safe to enter, RED = hazardous materials in use - never both on
const int GREEN_PIN  = 8;
const int RED_PIN    = 9;
const int SWITCH_PIN = 2;   // already hardware-debounced per problem statement

bool labSafe = true;        // true = GREEN on (safe), false = RED on (hazard)
int lastSwitchState = HIGH; // assume active-low switch (pressed = LOW)

void applyLights() {
  digitalWrite(GREEN_PIN, labSafe ? HIGH : LOW);
  digitalWrite(RED_PIN,   labSafe ? LOW  : HIGH);   // mutually exclusive by construction
}

void setup() {
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  applyLights();               // GREEN ON, RED OFF at power-up
}

void loop() {
  int switchState = digitalRead(SWITCH_PIN);

  if (switchState == LOW && lastSwitchState == HIGH) {   // falling edge = new press
    labSafe = !labSafe;        // toggle the single state variable
    applyLights();             // GREEN/RED updated together, atomically
  }
  lastSwitchState = switchState;
}
