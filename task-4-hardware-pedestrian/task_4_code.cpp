const int redTlight = 2;
const int yellowTlight = 3;
const int greenTlight = 4;
const int redPed = 5;
const int greenPed = 6;
const int buttonPin = 8;
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
  pinMode(redTlight, OUTPUT);
  pinMode(yellowTlight, OUTPUT);
  pinMode(greenTlight, OUTPUT);
  pinMode(redPed, OUTPUT);
  pinMode(greenPed, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  state = GREEN;
  digitalWrite(greenTlight, HIGH);
  digitalWrite(yellowTlight, LOW);
  digitalWrite(redTlight, LOW);
  digitalWrite(redPed, HIGH);
  digitalWrite(greenPed, LOW);
  stateStartTime = millis();
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    buttonPressed = true;
  }

  unsigned long currentTime = millis();

  switch (state) {
    case GREEN:
      digitalWrite(greenTlight, HIGH);
      digitalWrite(yellowTlight, LOW);
      digitalWrite(redTlight, LOW);
      digitalWrite(redPed, HIGH);
      digitalWrite(greenPed, LOW);
      if ((buttonPressed && currentTime - stateStartTime >= 2000) || 
          (currentTime - stateStartTime >= normalGreenDuration)) {
        state = YELLOW;
        stateStartTime = currentTime;
      }
      break;

    case YELLOW:
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
      digitalWrite(redPed, LOW);
      digitalWrite(greenPed, HIGH);
      if (currentTime - stateStartTime >= pedestrianGreenDuration) {
        state = RED_TO_GREEN;
        stateStartTime = currentTime;
        buttonPressed = false; 
      }
      break;

    case RED_TO_GREEN:
      digitalWrite(redTlight, LOW);
      digitalWrite(yellowTlight, HIGH);
      digitalWrite(redPed, HIGH);
      digitalWrite(greenPed, LOW);
      if (currentTime - stateStartTime >= redYellowDelay) {
        digitalWrite(yellowTlight, LOW);
        digitalWrite(greenTlight, HIGH);
        state = GREEN;
        stateStartTime = currentTime;
      }
      break;
  }
}
