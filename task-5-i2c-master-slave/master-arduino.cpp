#include <Wire.h>
const int redTlight = 2;
const int yellowTlight = 3;
const int greenTlight = 4;
const int normalGreenDuration = 6000;
const int normalYellowDuration = 2000;
const int fastYellowDuration = 2000;
const int pedestrianGreenDuration = 4000;
const int redYellowDelay = 1000;
enum TrafficState {
  GREEN,
  YELLOW,
  RED,
  RED_TO_GREEN
};
TrafficState state = GREEN;
bool buttonPressed = false;
unsigned long stateStartTime = 0;
void setup() {
  Wire.begin(); // master
  pinMode(redTlight, OUTPUT);
  pinMode(yellowTlight, OUTPUT);
  pinMode(greenTlight, OUTPUT);
  state = GREEN;
  digitalWrite(greenTlight, HIGH);
  digitalWrite(yellowTlight, LOW);
  digitalWrite(redTlight, LOW);
  stateStartTime = millis();
}
void loop() {
  receiveButton(); 
  unsigned long currentTime = millis();
  switch (state) {
    case GREEN:
      sendPedestrianState(0); 
      digitalWrite(greenTlight, HIGH);
      digitalWrite(yellowTlight, LOW);
      digitalWrite(redTlight, LOW);

      if ((buttonPressed && currentTime - stateStartTime >= 2000) ||
          (currentTime - stateStartTime >= normalGreenDuration)) {
        state = YELLOW;
        stateStartTime = currentTime;
      }
      break;
    case YELLOW:
      sendPedestrianState(0);
      digitalWrite(greenTlight, LOW);
      digitalWrite(yellowTlight, HIGH);
      digitalWrite(redTlight, LOW);
      if (buttonPressed && currentTime - stateStartTime >= fastYellowDuration) {
        state = RED;
        stateStartTime = currentTime;
      }
      else if (!buttonPressed && currentTime - stateStartTime >= normalYellowDuration) {
        state = RED;
        stateStartTime = currentTime;
      }
      break;
    case RED:
      digitalWrite(yellowTlight, LOW);
      digitalWrite(redTlight, HIGH);
      sendPedestrianState(1);
      if (currentTime - stateStartTime >= pedestrianGreenDuration) {
        state = RED_TO_GREEN;
        stateStartTime = currentTime;
        buttonPressed = false;
      }
      break;
    case RED_TO_GREEN:
      sendPedestrianState(0);
      digitalWrite(redTlight, LOW);
      digitalWrite(yellowTlight, HIGH);
      if (currentTime - stateStartTime >= redYellowDelay) {
        digitalWrite(yellowTlight, LOW);
        digitalWrite(greenTlight, HIGH);
        state = GREEN;
        stateStartTime = currentTime;
      }
      break;
  }
}
void receiveButton() {
  Wire.requestFrom(8, 1); 
  if (Wire.available()) {
    byte val = Wire.read();
    buttonPressed = (val == 1);
  }
}
void sendPedestrianState(int state) {
  Wire.beginTransmission(8);
  Wire.write(state);
  Wire.endTransmission();
}
